#include "include/FromServerReader.h"
#include "include/KeyboardReader.h"
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <include/User.h>

vector<string> FromServerReader::split(string str, string seperator)
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

FromServerReader::FromServerReader(ConnectionHandler * connectionHandler, User * user/*, ReceiptId * receiptId*/): connectionHandler(connectionHandler), user(user)/*, receiptId(receiptId)*/ {}

//FromServerReader::FromServerReader(ConnectionHandler* c, bool* lO, bool* t): connectionHandler(c), logOut(lO), terminate(t)  {cout << "terminate value is " << *terminate << endl;}

void FromServerReader::operator()(){
    while (connectionHandler->LoggedIn()) {
        string answer;
        vector<string> socketFrame;
        connectionHandler->getFrameAscii(answer, '\0');
        cout << "answer from the server is:\n" << answer << endl;

        //socketFrame = split(answer, "\n");
        boost::split(socketFrame, answer, boost::is_any_of("\n"));
//        //User user = User.getInstance();
//        std::cout << frame << "\n";

       // while (true) {
//            cout << "enrered true while in FromServerReader" << endl;
            // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
            // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
//            if (!connectionHandler->getLine(answer)) {
//                std::cout << "Disconnected. Exiting...\n" << std::endl;
//
//                break;
//            }
// FIXME this code
            //std::cout <<  << std::endl;
//            int len = line.length();
//            len = answer.length();

//            answer.resize(len - 1);
//            std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
            //cout << "now we will enter to frame process : " << socketFrame[0] << " with version" << socketFrame[1] << endl;
            if (socketFrame[0]=="CONNECTED") {
                cout << "Login successful." << endl;
                connectionHandler->logIn();
                //add to map of connected users?
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

            } else if (socketFrame[0] == "ERROR") {
                //*terminate = true;
            }
    }
}


