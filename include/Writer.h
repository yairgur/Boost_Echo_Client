#ifndef BOOST_ECHO_CLIENT_WRITER_H
#define BOOST_ECHO_CLIENT_WRITER_H
#include "connectionHandler.h"
#include "User.h"

using namespace std;

class Writer {
public:
    Writer(ConnectionHandler & connectionHandler);
    Writer(ConnectionHandler* c, bool* lO, bool* t); // do we need it?
    void run();
    void shortToBytes(short num, char* bytesArr);
//    void increaseReceiptId();
private:
    string name;
    string passcode;
    string genre;
    string bookName;
    bool *logOut;
    ConnectionHandler * connectionHandler;
    User *user;
    bool* terminate;
    int receiptId = 1;


};


#endif //BOOST_ECHO_CLIENT_WRITER_H
