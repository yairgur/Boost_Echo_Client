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

Writer::Writer(ConnectionHandler* c, bool *lO, bool *t) : connectionHandler(c), logOut(lO), terminate(t)  {cout << "terminate value is " << *terminate << endl;}



void Writer::run() {
    *terminate = false;
    while (!(*terminate)) {
        cout << "we are on the writer loop" << endl;
        bool out = false;
        *logOut=false;

//        while (*logOut==true){
//            //if(*terminate==true){
//                out =true;
//                break;
//            //}
//        }
//        if(out==true)
//            break;
        vector<string> words;

        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
        string line(buf);
        boost::split(words, line, boost::is_any_of(" "));
        cout << "this is our buf===============================\n\n\n" << line << endl;


        int len = line.length();

        cout << "we gonna excute command: " << words[0] << endl;
        vector<string> output;
        if(words[0] == "login" && connectionHandler->LoggedIn())
        {
            cout << "This Thread is already occupied by a user that logged in" << endl; //TODO what do we do with it?
        }
        else if(words[0] == "login"){
            user = new User(words[2], words[3]); // TODO in what map do we put it???
            this->name = words[2];
            this->passcode = words[3];
            string frame = "CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:" + words[2] + "\npasscode:" + passcode + "\n\n" + '\0';
            boost::split(output, frame, boost::is_any_of("\n"));
            for(int i=0; i<output.size(); ++i)
            {
                connectionHandler->sendLine(output[i]);
            }
            cout << "frame is \n" << frame << endl;
//          user->setSubscriptionId(0); // first subscriptionId is 0
        }
        else if(words[0] == "join"){
            this->genre = words[1];
            int subscriptionId = user->getSubscriptionId(); // TODO how do we get the right subscriptionId?
            string frame = "SUBSCRIBE\ndestination:" + this->genre + "\nid:" + to_string(subscriptionId) + "\nreceipt:" + to_string(receiptId) + "\n\n" + '\0';
            boost::split(output, frame, boost::is_any_of("\n"));
            for(int i=0; i<output.size(); ++i)
            {
                cout << "the line we send is: " << output[i] << endl;
                connectionHandler->sendLine(output[i]);
            }
            //increaseReceiptId(); // todo: return func
            cout << "Subscription Frame is:\n" << frame << endl;
        }
        else if(words[0] == "exit"){
            this->genre = words[1];
            int subscriptionId = user->getSubscriptionId(); // TODO how do we get the right subscriptionId?
            string frame = "UNSUBSCRIBE\nid:" + to_string(subscriptionId) + "\n\n" + '\0';
        }
        else if (words[0] == "add"){
            this->genre = words[1];
            this->bookName = words[2];

            string frame = "SEND\ndestination:" + this->genre +"\n\n" + user->getName() + " has added the book " + this->bookName + "\n" + '\0';
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
        //cin.getline(buf, bufsize); // FIXME - should find the right place for it
    }
}

//
//void Writer::increaseReceiptId() {
//    receiptId = receiptId + 1;
//}
