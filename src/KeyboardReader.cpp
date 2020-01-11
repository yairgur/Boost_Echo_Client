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

vector<string> KeyboardReader::split(string str, string seperator)
{
    vector<string> wordsVector;
    size_t pos = 0;
    string word;
    while((pos = str.find(seperator)) != string::npos)
    {
        word = str.substr(0, pos);
        wordsVector.push_back(word);
        str.erase((0, pos+seperator.length()));
    }
    wordsVector.push_back(str);
    return wordsVector;
}

KeyboardReader::KeyboardReader(ConnectionHandler * connectionHandler, User user): connectionHandler(connectionHandler), user(user) {}

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
        if(commands[0] == "login" && connectionHandler->LoggedIn())
        {
            cout << "This Thread is already occupied by a user that logged in" << endl; //TODO what do we do with it?
        }
        else if(commands[0] == "login"){
            //user = new User(words[2], words[3]); // TODO in what map do we put it???
            string frame = "CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:" + commands[2] + "\npasscode:" + commands[3] + "\n\n" + '\0';
            //output = split(frame, "\n");
            boost::split(output, frame, boost::is_any_of("\n"));
            connectionHandler->sendLine(frame);
            cout << "frame is \n" << frame << endl;
//          user->setSubscriptionId(0); // first subscriptionId is 0
        }
        else if(commands[0] == "join"){
            int subscriptionId = user.getSubscriptionId(); // TODO how do we get the right subscriptionId?
            string frame = "SUBSCRIBE\ndestination:" + commands[1] + "\nid:" + to_string(subscriptionId) + "\nreceipt:" + to_string(receiptId) + "\n\n" + '\0';
            //output = split(frame, "\n");
            boost::split(output, frame, boost::is_any_of("\n"));
            connectionHandler->sendLine(frame);
            //increaseReceiptId(); // todo: return func
            cout << "Subscription Frame is:\n" << frame << endl;
        }
        else if(commands[0] == "exit"){
            int subscriptionId = user.getSubscriptionId(); // TODO how do we get the right subscriptionId?
            string frame = "UNSUBSCRIBE\nid:" + to_string(subscriptionId) + "\n\n" + '\0';
            connectionHandler->sendLine(frame);
        }
        else if (commands[0] == "add"){
            string frame = "SEND\ndestination:" + commands[1] +"\n\n" + user.getName() + " has added the book " + commands[2] + "\n" + '\0';
            vector<string> output;
            //output = split(frame, "\n");
            boost::split(output, frame, boost::is_any_of("\n"));
            connectionHandler->sendLine(frame);
        }
        else if (commands[0] == "borrow"){
            string frame = "SEND\ndestination:" + commands[1] +"\n\n" + user.getName() + " wish to borrow " + commands[2] + "\n" + '\0';
            vector<string> output;
            //output = split(frame, "\n");
            boost::split(output, frame, boost::is_any_of("\n"));
            connectionHandler->sendLine(frame);
        }
        else if (commands[0] == "return"){
            string frame = "SEND\ndestination:" + commands[1] +"\n\n" + "Returning " + commands[2] + " to " + user.getName() + "\n" + '\0';
            vector<string> output;
            //output = split(frame, "\n");
            boost::split(output, frame, boost::is_any_of("\n"));
            connectionHandler->sendLine(frame);
        }
        else if (commands[0] == "status"){
            string frame = "SEND\ndestination:" + commands[1] +"\n\n" + "book status" + "\n" + '\0';
            vector<string> output;
            //output = split(frame, "\n");
            boost::split(output, frame, boost::is_any_of("\n"));
            connectionHandler->sendLine(frame);
        }
        else if (commands[0] == "logout"){
            string frame = "DISCONNECT\nreceipt:" + to_string(receiptId) +"\n\n" + '\0';
            //increaseReceiptId(); // todo return func
            vector<string> output;
            //output = split(frame, "\n");
            boost::split(output, frame, boost::is_any_of("\n"));
            connectionHandler->sendLine(frame);
            //connectionHandler->close(); // kills the socket
        }
    }
}

//
//void KeyboardReader::increaseReceiptId() {
//    receiptId = receiptId + 1;
//}


