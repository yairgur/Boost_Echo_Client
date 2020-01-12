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

bool FromServerReader::contains(vector<string> vec, string toCompare)
{
    for(string s:vec)
    {
        if(s == toCompare)
            return true;
    }
    return false;
}

FromServerReader::FromServerReader(ConnectionHandler * connectionHandler, User * user/*, ReceiptId * receiptId*/): connectionHandler(connectionHandler), user(user)/*, receiptId(receiptId)*/ {}

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
                MessageType messageTypePtr = (user->getMessageTypeByReceiptId(stoi(socketFrame[1].substr(socketFrame[1].find(':') + 1))));
                cout << "This is message type: " << messageTypePtr.getMessageType() << endl;
                if(messageTypePtr.getMessageType() == "SUBSCRIBE")
                {
                    cout << "Joined club " << messageTypePtr.getGenere() << endl;

                }
                else if(messageTypePtr.getMessageType() == "UNSUBSCRIBE")
                {
                    cout << "Exited club " << messageTypePtr.getGenere() << endl;
                }
                else if(messageTypePtr.getMessageType() == "DISCONNECT"){
                    connectionHandler->logOff(); // TODO activate only if disconnected and it will end the program!!
                    break;
                }
            } else if (socketFrame[0] == "MESSAGE") {
                vector<string> body = split(socketFrame[5], " ");
                if(contains(body, "added"))
                {
                    //inventory = user->getUserInventory();
                    Inventory* userInventory = user->getUserInventory();
                    string book = socketFrame[5].substr(socketFrame[5].find("the book") + 9);
                    string genre = socketFrame[3].substr(socketFrame[3].find(':')+1);
                    //inventory->addBookToInventory(book, genre);
                    (*userInventory).addBookToInventory(book, genre);
                    cout << book << endl;
                }
                else if(contains(body, "borrow"))
                {
                    Inventory* userInventory = user->getUserInventory();
                    if(user->getName() == body[0])
                    {
                        userInventory->insertWishToBorrow(socketFrame[5].substr(socketFrame[5].find("has")+4));
                    }
                    else{
                        bool isExist = userInventory->isWishToBorrow(socketFrame[5].substr(socketFrame[5].find("has")+4));
                        if(isExist){
                            string subscriptionId = socketFrame[1].substr(socketFrame[1].find(':')+1);
                            string genre = user->containsSubscriptionId(stoi(subscriptionId));
                            string frame = "SEND\ndestination:" + genre + "\n\n" + user->getName() + " has " + body[0] + "\n" + '\0';
                            connectionHandler->sendLine(frame);
                        }
                    }
                }
                else if(contains(body, "Returning"))
                {
                    string book = socketFrame[5].substr(socketFrame[5].find(' ')+1, socketFrame[5].find("to")-11);
                    string userName = socketFrame[5].substr(socketFrame[5].find_last_of(' ')+1);
                    //inventory = user->getUserInventory();
                    Inventory* userInventory = user->getUserInventory();
                    string genre = socketFrame[3].substr(socketFrame[5].find(':')+1);
                    userInventory->deleteFromInventory(book, genre);
                    //userInventory->deleteFromInventory(book, genre);
                    cout << "we just deleted " << book << " from the inventory of user: " << user->getName() << endl;
                    if(user->getName() == userName)
                    {
                        //inventory->addBookToInventory(book, genre);
                        userInventory->addBookToInventory(book, genre);
                        cout << "we just added " << book << " ========TO======= the inventory of user: " << user->getName() << endl;
                    }
                    cout << book << " " << userName << endl;
                }
                else if(contains(body, "status"))
                {
                    string subscriptionId = socketFrame[1].substr(socketFrame[1].find(':')+1);
                    string genre = user->containsSubscriptionId(stoi(subscriptionId));
                    if(genre != "")
                    { //there is a gener with this subscriptionId
                        //inventory = user->getUserInventory();
                        Inventory* userInventory = user->getUserInventory();
                        //string booksList = inventory->toString();
                        string booksList = userInventory->toString();
                        cout<< booksList << endl;
                        string frame = "SEND\ndestination:" + genre + "\n\n" + user->getName() + ":" + booksList + "\n" + '\0';
                        connectionHandler->sendLine(frame);
                    }
                }

            } else if (socketFrame[0] == "ERROR") {
                //*terminate = true;
            }
    }
}


