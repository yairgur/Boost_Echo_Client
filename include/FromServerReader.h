#ifndef BOOST_ECHO_CLIENT_FROMSERVERREADER_H
#define BOOST_ECHO_CLIENT_FROMSERVERREADER_H
#include "connectionHandler.h"
#include "User.h"
#include "ReceiptId.h"

class FromServerReader {
public:
    FromServerReader(ConnectionHandler * connectionHandler, User * user/*, ReceiptId * receiptId*/);
//    FromServerReader(ConnectionHandler* c, bool* lO, bool* t); // do we need it?
    void operator()();
    vector<string> split(string str, string seperator);
    //void run();
private:
    ConnectionHandler * connectionHandler;
    User * user;
};


#endif


