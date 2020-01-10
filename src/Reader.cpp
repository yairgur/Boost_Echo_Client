#include "include/Reader.h"
#include "include/Writer.h"
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <include/User.h>



Reader::Reader(ConnectionHandler & connectionHandler)
{
    this->connectionHandler = & connectionHandler;
}

Reader::Reader(ConnectionHandler* c, bool* lO, bool* t): connectionHandler(c), logOut(lO), terminate(t)  {cout << "terminate value is " << *terminate << endl;}

void Reader::run(){
    cout << "We are on the reader loop" << endl;
    *terminate = false;

//    *logOut=false;
//    *terminate=false;
//    User * user = User::getInstance();
    while (!(*terminate)) {
//        string frame = "";
//        int i =1;
//        bool outPut = connectionHandler->getFrameAscii(frame , '\0');
//        vector<string> socketFrame;
        vector<string> socketFrame;
        const short bufsize = 1024;
        char buf[bufsize];
        std::string answer;
        connectionHandler->getFrameAscii(answer, '\0');
        //connectionHandler->getLine(answer);
        cout << "answer from the server is: " << answer << endl;
        string line(buf);
        int len = line.length();

        boost::split(socketFrame, answer, boost::is_any_of("\n"));
//        //User user = User.getInstance();
//        std::cout << frame << "\n";

       // while (true) {
//            cout << "enrered true while in Reader" << endl;
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
            if (answer == "bye") {
                std::cout << "Exiting...\n" << std::endl;
                //break;
            }

            cout << "now we will enter to frame process : " << socketFrame[0] << " with version" << socketFrame[1] << endl;
            if (socketFrame[0]=="CONNECTED") {
                cout << "Login successful." << endl;
                connectionHandler->logIn();
                //add to map of connected users?
            } else if (socketFrame[0] == "RECEIPT") {
                cout << "\nreceipt recieved successfully" << endl;
                //if it disconnect message, we should change terminate to true;
            } else if (socketFrame[0] == "MESSAGE") {

            } else if (socketFrame[0] == "ERROR") {
                //*terminate = true;
            }
            else {
                cout << "Am i in the else?????" << endl;
                //throw exception
            }
        //cin.getline(buf, bufsize); // FIXME - should find the right place for it
      //  }
    }
}
