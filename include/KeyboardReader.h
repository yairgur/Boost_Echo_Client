#ifndef BOOST_ECHO_CLIENT_KEYBOARDREADER_H
#define BOOST_ECHO_CLIENT_KEYBOARDREADER_H
#include "connectionHandler.h"
#include "User.h"
#include "ReceiptId.h"

using namespace std;

class KeyboardReader {
public:
    KeyboardReader(ConnectionHandler * connectionHandler, User * user/*, ReceiptId * receiptId*/);
//    KeyboardReader(ConnectionHandler* c, bool* lO, bool* t); // do we need it?
//    void operator()();
    void operator()();
    void increaseReceiptId();
    // void run();
    vector<string> split(string str, string delimiter);
    void increaseSubscriptionId();
private:
    ConnectionHandler * connectionHandler;
    User *user;
    int subscriptionId = 1;
    //ReceiptId * receiptId;
    int receiptId = 1;



};


#endif //BOOST_ECHO_CLIENT_KEYBOARDREADER_H
