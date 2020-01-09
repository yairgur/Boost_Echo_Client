#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <include/User.h>
#include <boost/lexical_cast.hpp>
#include <../include/connectionHandler.h>
#include "include/Reader.h"
#include "include/Writer.h"




using namespace std;

int main(){

    bool terminate=false;
    while (!(terminate)) {
        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
        string line(buf);

        int len = line.length();
        vector<string> words;
        boost::split(words, line, boost::is_any_of(" "));

        if (words[0] == "login") {
            string host = words[1].substr(0, words[1].find(':'));
            string portS = words[1].substr(words[1].find(':') + 1);
            short port = boost::lexical_cast<short>(portS);
            string name = words[2];
            string passcode = words[3];
            User *user = new User(words[2], words[3]);
            vector<string> output;
            ConnectionHandler connectionHandler(host, port);
            connectionHandler.connect();
//            string frame = "CONNECTED accept-version:1.2 host:" + host + " port:" + to_string(port) + " login:" + words[2] + " passcode:" + passcode + "\n\n" + "\0"; // we should init the first frame
            string frame = "CONNECT accept-version:1.2 host:stomp.cs.bgu.ac.il login:" + words[2] + " passcode:" + passcode + "\n\n" + "\0";
            connectionHandler.sendLine(frame);

            bool *t = new bool;
            bool *r = new bool;
            boost::split(output, frame, boost::is_any_of(" "));
//            user->setSubscriptionId(0); // first subscriptionId is 0
//            Writer keyBoardThread(connectionHandler);
//            Reader serverSocketThread(connectionHandler);

            Writer keyBoardThread(&connectionHandler, r, t);
            Reader serverSocketThread(&connectionHandler, r, t);
            thread serverInput(&Reader::run, &serverSocketThread);
            thread keyBoardInput(&Writer::run, &keyBoardThread);
            serverInput.join();
            keyBoardInput.join();

//            thread t1(ref(keyBoardThread));
//            thread t2(ref(serverSocketThread));
//            t2.join();
//            t1.join();

        }
    }




//while(1){
//
//    if(words[0] == "login"){
//        string host = words[1].substr(0, words[1].find(':')-1);
//        string portS = words[1].substr(words[1].find(':')+1);
//        short port = boost::lexical_cast<short>(portS);
//        string name = words[2];
//        string passcode = words[3];
//        User *user = new User(words[2], words[3]);
//        vector<string> output;
////        string frame = "CONNECTED accept-version:1.2 host:stomp.cs.bgu.ac.il login:" + words[2] + " passcode:" + passcode + "\n\n" + "\0";
//        ConnectionHandler connectionHandler(host, port);
//        connectionHandler.connect();
//        string frame = ""; // we should init the first frame
//        connectionHandler.sendLine(frame);
//
//        bool *t = new bool;
//        bool *r = new bool;
//        boost::split(output, frame, boost::is_any_of(" "));
//
//        user->setSubscriptionId(0); // first subscriptionId is 0
//
//        Writer keyBoardThread(&connectionHandler, r, t);
//        Reader serverSocketThread(&connectionHandler, r, t);
//
//        thread serverInput(&Reader::run, &serverSocketThread);
//        thread keyBoardInput(&Writer::run, &keyBoardThread);
//
//        serverInput.join();
//        keyBoardInput.join();
//
//    }
//}

    //ConnectionHandler(host, port);
    //ConnectionHandler connectionHandler(host, port);
//    ConnectionHandler connectionHandler("tpc", 7777);
    //ConnectionHandler connectionHandler(argv[1], argv[0]);
//    connectionHandler.connect();
    //User * user = new User()
    string frame = ""; // we should init the first frame
//    connectionHandler.sendLine(frame);


//    Writer writeThread(connectionHandler);
//    Reader readThread(connectionHandler);
//    thread activeWriteThread((thread(writeThread)));
//    thread activeReadThread((thread(readThread)));
//    activeReadThread.join();
//    activeWriteThread.join();

    return 0;
}

