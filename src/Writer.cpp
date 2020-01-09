#include "include/Writer.h"
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <include/User.h>
#include <boost/lexical_cast.hpp>
#include <../include/connectionHandler.h>
#include "include/Reader.h"
#include <thread>


using namespace std;


Writer::Writer(ConnectionHandler & connectionHandler)
{
    this->connectionHandler = & connectionHandler;
}

Writer::Writer(ConnectionHandler* c, bool *lO, bool *t) : connectionHandler(c), logOut(lO), terminate(t)  {}



void Writer::run() {

    while (!(*terminate)) {
        bool out = false;
        *logOut=false;

        while (*logOut==true){
            //if(*terminate==true){
                out =true;
                break;
            //}
        }
        if(out==true)
            break;

        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
        string line(buf);


        int len = line.length();
        vector<string> words;

        boost::split(words, line, boost::is_any_of(" "));


        if(words[0] == "login"){
            user = new User(words[2], words[3]);
            string host = words[1].substr(0, words[1].find(':')-1);
            string portS = words[1].substr(words[1].find(':')+1);
            short port = boost::lexical_cast<short>(portS);
            ConnectionHandler(host, port);

//            std::thread keyBoardReader std::ref()
            //std::thread threadObj( (Reader()) );

            this->name = words[2];
            this->passcode = words[3];
            string frame = "CONNECT accept-version:1.2 host:stomp.cs.bgu.ac.il login:" + words[2] + " passcode:" + passcode + "\n\n" + "\0";
            vector<string> output;
            boost::split(output, frame, boost::is_any_of(" "));
            for(int i=0; i<output.size(); ++i)
            {
                connectionHandler->sendLine(output[i]);
            }
//            user->setSubscriptionId(0); // first subscriptionId is 0

        }
        else if(words[0] == "join"){
            this->genre = words[1];
            int subscriptionId = user->getSubscriptionId(); // TODO how do we get the right subscriptionId?
            string frame = "SUBSCRIBE\ndestination:" + this->genre + "\nid:" + to_string(subscriptionId) + "\nrecipt:" + to_string(receiptId) + "\n\n" + "\0";
            //increaseReceiptId(); // todo: return func
        }
        else if(words[0] == "exit"){
            this->genre = words[1];
            int subscriptionId = user->getSubscriptionId(); // TODO how do we get the right subscriptionId?
            string frame = "UNSUBSCRIBE\nid:" + to_string(subscriptionId) + "\n\n" + "\0";
        }
        else if (words[0] == "add"){
            this->genre = words[1];
            this->bookName = words[2];

            string frame = "SEND\ndestination:" + this->genre +"\n\n" + user->getName() + " has added the book " + this->bookName + "\n" + "\0";
            vector<string> output;
            boost::split(output, frame, boost::is_any_of("\n"));
            for(int i=0; i<output.size(); ++i)
            {
                connectionHandler->sendLine(output[i]);
            }
        }
        else if (words[0] == "borrow"){
            this->genre = words[1];
            this->bookName = words[2];
            string frame = "SEND\ndestination:" + this->genre +"\n\n" + user->getName() + " wish to borrow " +this->bookName + "\n" + "\0";
            vector<string> output;
            boost::split(output, frame, boost::is_any_of("\n"));
            for(int i=0; i<output.size(); ++i)
            {
                connectionHandler->sendLine(output[i]);
            }
        }
        else if (words[0] == "return"){
            this->genre = words[1];
            this->bookName = words[2];
            string frame = "SEND\ndestination:" + this->genre +"\n\nReturning " + this->bookName +" to " + user->getName() + "\n" + "\0";
            vector<string> output;
            boost::split(output, frame, boost::is_any_of("\n"));
            for(int i=0; i<output.size(); ++i)
            {
                connectionHandler->sendLine(output[i]);
            }
        }
        else if (words[0] == "status"){
            this->genre = words[1];
            string frame = "SEND\ndestination:" + this->genre +"\n\nbook status\n" + "\0";
            vector<string> output;
            boost::split(output, frame, boost::is_any_of("\n"));
            for(int i=0; i<output.size(); ++i)
            {
                connectionHandler->sendLine(output[i]);
            }
        }
        else if (words[0] == "logout"){
            this->genre = words[1];
            string frame = "DISCONNECT\nreceipt:" + to_string(receiptId) +"\n\n" + "\0";
            //increaseReceiptId(); // todo return func
            vector<string> output;
            boost::split(output, frame, boost::is_any_of("\n"));
            for(int i=0; i<output.size(); ++i)
            {
                connectionHandler->sendLine(output[i]);
            }
        }
    }
}

//
//void Writer::increaseReceiptId() {
//    receiptId = receiptId + 1;
//}
