#include "include/KeyboardReader.h"
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <include/User.h>
#include <boost/lexical_cast.hpp>
#include <../include/connectionHandler.h>
#include "include/FromServerReader.h"
#include <thread>


using namespace std;

vector<string> KeyboardReader::split(string s, string delimiter)
{
    vector<string> wordsVector;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        std::cout << token << std::endl;
        s.erase(0, pos + delimiter.length());
        wordsVector.push_back(token);
    }
    wordsVector.push_back(s);

    return wordsVector;
}

KeyboardReader::KeyboardReader(ConnectionHandler * connectionHandler, User * user, bool *terminate/*, ReceiptId * receiptId*/): connectionHandler(connectionHandler), user(user)/*, receiptId(receiptId)*/ {}

//KeyboardReader::KeyboardReader(ConnectionHandler* c, bool *lO, bool *t) : connectionHandler(c), logOut(lO), terminate(t)  {cout << "terminate value is " << *terminate << endl;}


void KeyboardReader::operator()() {
        while (connectionHandler->LoggedIn()) {
            const short bufsize = 1024;
            char buf[bufsize];
            cin.getline(buf, bufsize);
            string line(buf);
            vector<string> commands;
            vector<string> output;
            //commands = split(line, " ");
            boost::split(commands, line, boost::is_any_of(" "));
            if(line == "bye")
            {
                connectionHandler->logOff();
                break;
            }
            if(commands.size()>3) //if book name is more than one word
            {
                for(int i=3; i<commands.size(); i++) {
                    commands[2] += " " + commands[i];
                }
                //commands[2] = commands[2].substr(0, commands[2].size()-1);
            }
            if (commands[0] == "login" && connectionHandler->LoggedIn()) {
                cout << "This Thread is already occupied by a user that logged in"
                     << endl; //TODO what do we do with it?
                string frame = "DISCONNECT\nreceipt:" + to_string(receiptId) + "\n\n" + '\0';
                increaseReceiptId();
                connectionHandler->sendLine(frame);
                break;
            } else if (commands[0] == "login") {
                //user = new User(words[2], words[3]); // TODO in what map do we put it???
                string frame =
                        "CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:" + commands[2] + "\npasscode:" +
                        commands[3] + "\n\n" + '\0';
                //output = split(frame, "\n");
                boost::split(output, frame, boost::is_any_of("\n"));
                connectionHandler->sendLine(frame);
                cout << "frame is \n" << frame << endl;
//          user->setSubscriptionId(0); // first subscriptionId is 0
            } else if (commands[0] == "join") {
                string frame =
                        "SUBSCRIBE\ndestination:" + commands[1] + "\nid:" + to_string(subscriptionId) + "\nreceipt:" +
                        to_string(receiptId) + "\n\n" + '\0';
                user->addSubscriptionIdToGenre(commands[1], subscriptionId);
                increaseSubscriptionId();
                MessageType *messageType = new MessageType("SUBSCRIBE", commands[1], receiptId);
                user->addToReceiptIdMap(receiptId, messageType);
                increaseReceiptId();

                boost::split(output, frame, boost::is_any_of("\n"));
                connectionHandler->sendLine(frame);
                cout << "Subscription Frame is:\n" << frame << endl;
            } else if (commands[0] == "exit") {
                int matchSubscriptionId = user->getSubscriptionIdFromGenre(commands[1]);
                string frame =
                        "UNSUBSCRIBE\nid:" + to_string(matchSubscriptionId) + "\nreceipt:" + to_string(receiptId) +
                        "\n\n" + '\0';
                MessageType *messageType = new MessageType("UNSUBSCRIBE", commands[1], receiptId);
                user->addToReceiptIdMap(receiptId, messageType);
                increaseReceiptId();
                connectionHandler->sendLine(frame);
            } else if (commands[0] == "add") {

                Inventory* userInventory = user->getUserInventory();
                string book = commands[2]; // todo :func that extract full book name
                string genre = commands[1];

                cout << "YYY "<< genre << endl;
                (*userInventory).addBookToInventory(book, genre);

                string frame = "SEND\ndestination:" + commands[1] + "\n\n" + user->getName() + " has added the book " +
                               commands[2] + "\n" + '\0';
                vector<string> output;
                //output = split(frame, "\n");
                boost::split(output, frame, boost::is_any_of("\n"));
                connectionHandler->sendLine(frame);
            } else if (commands[0] == "borrow") {
                string frame = "SEND\ndestination:" + commands[1] + "\n\n" + user->getName() + " wish to borrow " +
                               commands[2] + "\n" + '\0';
                vector<string> output;
                //output = split(frame, "\n");
                boost::split(output, frame, boost::is_any_of("\n"));
                user->getUserInventory()->insertWishToBorrow(commands[2]);
                connectionHandler->sendLine(frame);
            } else if (commands[0] == "return") {
                string frame = "SEND\ndestination:" + commands[1] + "\n\n" + "Returning " + commands[2] + " to " +
                               user->getUserInventory()->getFromBorrowedMap(commands[2]) + "\n" + '\0';
                user->getUserInventory()->deleteBorrowedBook(commands[2]);
                user->getUserInventory()->deleteFromInventory(commands[2], commands[1]);
                vector<string> output;
                //output = split(frame, "\n");
                boost::split(output, frame, boost::is_any_of("\n"));
                connectionHandler->sendLine(frame);
            } else if (commands[0] == "status") {
                string frame = "SEND\ndestination:" + commands[1] + "\n\n" + "Book status" + "\n" + '\0';
                vector<string> output;
                //output = split(frame, "\n");
                boost::split(output, frame, boost::is_any_of("\n"));
                connectionHandler->sendLine(frame);
            } else if (commands[0] == "logout") {
                string frame = "DISCONNECT\nreceipt:" + to_string(receiptId) + "\n\n" + '\0';
                MessageType *messageType = new MessageType("DISCONNECT", "", receiptId);
                user->addToReceiptIdMap(receiptId, messageType);
                increaseReceiptId();
                vector<string> output;
                //output = split(frame, "\n");
                boost::split(output, frame, boost::is_any_of("\n"));
                connectionHandler->sendLine(frame);
                break;
            }
        }

}


void KeyboardReader::increaseSubscriptionId() {
    subscriptionId = subscriptionId + 1;
}

void KeyboardReader::increaseReceiptId()
{
    receiptId = receiptId + 1;
}


