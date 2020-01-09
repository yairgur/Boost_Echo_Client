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

Reader::Reader(ConnectionHandler* c, bool* lO, bool* t): connectionHandler(c), logOut(lO), terminate(t)  {}

void Reader::run(){

//    *logOut=false;
//    *terminate=false;
//    User * user = User::getInstance();
    //while (!(*terminate)) {
//        string frame = "";
//        int i =1;
//        bool outPut = connectionHandler->getFrameAscii(frame , '\0');
//        vector<string> socketFrame;
    vector<string> socketFrame;
    const short bufsize = 1024;
    char buf[bufsize];
    std::string answer;
    connectionHandler->getLine(answer);
    string line(buf);
    int len = line.length();

//        boost::split(socketFrame, line, boost::is_any_of("\n"));
//        //User user = User.getInstance();
//        std::cout << frame << "\n";

        while(1){
            // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
            // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
            if (!connectionHandler->getLine(answer)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;

                break;
            }
            std::cout <<  << std::endl;
            int len=line.length();
            len=answer.length();

            answer.resize(len-1);
            std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
            if (answer == "bye") {
                std::cout << "Exiting...\n" << std::endl;
                break;
            }



            if (socketFrame[0].compare("CONNECTED")){
                cout << "Login successful." << endl;
                //add to map of connected users?
            }
            else if(socketFrame[0].compare("RECEIPT")){

            }
            else if (socketFrame[0].compare("MESSAGE")){

            }
            else if (socketFrame[0].compare("ERROR")){
            }
            else{
                //throw exception
            }

        }

}
