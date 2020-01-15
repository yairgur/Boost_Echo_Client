#include "include/FromServerReader.h"
#include "include/KeyboardReader.h"
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <include/User.h>

vector<string> FromServerReader::split(string s, string delimiter)
{
    vector<string> wordsVector;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
//        std::cout << token << std::endl;
        s.erase(0, pos + delimiter.length());
        wordsVector.push_back(token);
    }
    wordsVector.push_back(s);

    return wordsVector;
}

string FromServerReader::getFullBookName(string str)
{
    string bookName = "";
    if(str.find("the book")!=string::npos)
    {
        bookName = str.substr(str.find("the book") + 9);
    }
    else if(str.find("to borrow")!=string::npos)
    {
        bookName = str.substr((str.find("to borrow") + 10));
    }
    else if(str.find("Taking")!=string::npos)
    {
        bookName = str.substr(str.find("Taking") + 7, str.find(" from ")-7);
    }
    else if(str.find("Returning")!=string::npos)
    {
        bookName = str.substr(str.find("Returning") + 10, str.find(" to ") - 10);
    }
    else if(str.find("added") == string::npos && str.find("has")!=string::npos)
    {
        bookName = str.substr(str.find("has") + 4);
    }
    return bookName;
}

bool FromServerReader::contains(vector<string> vec, string toCompare)
{
    for(string s:vec)
    {
        if(s == toCompare)
            return true;
    }
    return false;
}

FromServerReader::FromServerReader(ConnectionHandler * connectionHandler, User * user, Inventory * inventory): connectionHandler(connectionHandler), user(user), inventory(inventory) {}

void FromServerReader::operator()(){
    while (connectionHandler->LoggedIn()) {
        string answer;
        vector<string> socketFrame;
        connectionHandler->getFrameAscii(answer, '\0');
        cout << "answer from the server is:\n" << answer << endl;

        boost::split(socketFrame, answer, boost::is_any_of("\n"));

            if (socketFrame[0]=="CONNECTED") {
                cout << "Login successful." << endl;
                connectionHandler->logIn();
            } else if (socketFrame[0] == "RECEIPT") {
                MessageType *messageTypePtr = (user->getMessageTypeByReceiptId(stoi(socketFrame[1].substr(socketFrame[1].find(':') + 1))));
                cout << "This is message type: " << messageTypePtr->getMessageType() << endl;
                if(messageTypePtr->getMessageType() == "SUBSCRIBE")
                {
                    cout << "Joined club " << messageTypePtr->getGenere() << endl;
                }
                else if(messageTypePtr->getMessageType() == "UNSUBSCRIBE")
                {
                    cout << "Exited club " << messageTypePtr->getGenere() << endl;
                }
                else if(messageTypePtr->getMessageType() == "DISCONNECT"){
                    connectionHandler->logOff(); // TODO activate only if disconnected and it will end the program!!
                    delete user;
                    delete inventory;
                    delete connectionHandler;
                    delete messageTypePtr;
                    break;
                }
                delete messageTypePtr;
            } else if (socketFrame[0] == "MESSAGE") {
                vector<string> body = split(socketFrame[5], " ");
                if(contains(body, "has") && !contains(body, "added")){///private case of borrow
                    string subscriptionId = socketFrame[1].substr(socketFrame[1].find(':')+1);
                    string genre = user->containsSubscriptionId(stoi(subscriptionId));
                    string bookName = getFullBookName(socketFrame[5]);
                    cout << "===Book name is: " << bookName << endl;
                    if(user->getName() == body[0])
                    {
                        inventory->deleteFromInventory(bookName, genre);
                    }
                    else{
                        bool isExist = inventory->isWishToBorrow(bookName);
                        if(isExist){
                            string borrowedUser = body[0];
                            string frame = "SEND\ndestination:" + genre + "\n\n" + "Taking " + bookName + " from " + borrowedUser + "\n" + '\0';
                            inventory->addBorrowedBook(bookName, body[0]); //fixme - delete
                            cout << "ZZZ "<< genre << endl;
                            inventory->addBookToInventory(bookName, genre);
                            inventory->deleteFromWishList(bookName);
                            connectionHandler->sendLine(frame);
                        }
                    }

                }
                if(contains(body, "added") && (user->getName() == body[0]))
                {
//                    Inventory* userInventory = user->getUserInventory();
//                    string book = socketFrame[5].substr(socketFrame[5].find("the book") + 9);
//                    string genre = socketFrame[3].substr(socketFrame[3].find(':')+1);
//                    //inventory->addBookToInventory(book, genre);
//                    (*userInventory).addBookToInventory(book, genre);
//                    cout << book << endl;
                }
                else if(contains(body, "borrow"))
                {
                    string bookName = getFullBookName(socketFrame[5]);
                    if(user->getName() == body[0])
                    {
//                        userInventory->addBorrowedBook(bookName, user->getName());
                    }
                    else{
                        bool isExist = inventory->isExistInClientBooks(bookName);
                        if(isExist){
                            string subscriptionId = socketFrame[1].substr(socketFrame[1].find(':')+1);
                            string genre = user->containsSubscriptionId(stoi(subscriptionId));
                            string frame = "SEND\ndestination:" + genre + "\n\n" + user->getName() + " has " + bookName + "\n" + '\0';
                            connectionHandler->sendLine(frame);
                        }


                    }
                }
                else if(contains(body, "Returning"))
                {
                    string book = getFullBookName(socketFrame[5]);
                    cout << "===Book name is: " << book << endl;
                    string userName = socketFrame[5].substr(socketFrame[5].find_last_of(' ')+1);
                    string genre = socketFrame[3].substr(socketFrame[3].find(':')+1);
                    if(user->getName() == userName)
                    {
                        cout << "XXX "<< genre << endl;
                        inventory->addBookToInventory(book, genre); // todo: book name 1!!
                    }
                }
                else if(contains(body, "status"))
                {
                    string subscriptionId = socketFrame[1].substr(socketFrame[1].find(':')+1);
                    string genre = user->containsSubscriptionId(stoi(subscriptionId));
                    if(genre != "")
                    { //there is a gener with this subscriptionId
                        string booksList = inventory->toString();
                        cout<< booksList << endl;
                        string frame = "SEND\ndestination:" + genre + "\n\n" + user->getName() + ":" + booksList + "\n" + '\0';
                        connectionHandler->sendLine(frame);
                    }
                }

            } else if (socketFrame[0] == "ERROR") {
                connectionHandler->logOff();
                break;

            }
    }
}


