#ifndef BOOST_ECHO_CLIENT_KEYBOARDREADER_H
#define BOOST_ECHO_CLIENT_KEYBOARDREADER_H
#include "ConnectionHandler.h"
#include "User.h"


using namespace std;

class KeyboardReader {
public:
    KeyboardReader(ConnectionHandler * connectionHandler, User * user, Inventory * inventory);
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
    Inventory * inventory;
    int subscriptionId = 1;
    //ReceiptId * receiptId;
    int receiptId = 1;



};


#endif //BOOST_ECHO_CLIENT_KEYBOARDREADER_H
