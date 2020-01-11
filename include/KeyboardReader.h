#ifndef BOOST_ECHO_CLIENT_KEYBOARDREADER_H
#define BOOST_ECHO_CLIENT_KEYBOARDREADER_H
#include "connectionHandler.h"
#include "User.h"

using namespace std;

class KeyboardReader {
public:
    KeyboardReader(ConnectionHandler * connectionHandler, User user);
//    KeyboardReader(ConnectionHandler* c, bool* lO, bool* t); // do we need it?
//    void operator()();
    void operator()();
    // void run();
    vector<string> split(string str, string seperator);
//    void increaseReceiptId();
private:
    ConnectionHandler * connectionHandler;
    User user;
    int receiptId = 1;


};


#endif //BOOST_ECHO_CLIENT_KEYBOARDREADER_H
