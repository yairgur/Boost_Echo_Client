#ifndef BOOST_ECHO_CLIENT_FROMSERVERREADER_H
#define BOOST_ECHO_CLIENT_FROMSERVERREADER_H
#include "connectionHandler.h"
#include "User.h"
#include "ReceiptId.h"

class FromServerReader {
public:
    FromServerReader(ConnectionHandler * connectionHandler, User * user, bool *terminate/*, ReceiptId * receiptId*/);
//    FromServerReader(ConnectionHandler* c, bool* lO, bool* t); // do we need it?
    void operator()();
    vector<string> split(string str, string delimiter);
    bool contains(vector<string> vec, string toCompare);
    string getFullBookName(string str);
    //void run();
private:
    ConnectionHandler * connectionHandler;
    User * user;

};


#endif


