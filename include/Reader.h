#ifndef BOOST_ECHO_CLIENT_READER_H
#define BOOST_ECHO_CLIENT_READER_H
#include "connectionHandler.h"
#include "User.h"

class Reader {
public:
    Reader(ConnectionHandler & connectionHandler);
    Reader(ConnectionHandler* c, bool* lO, bool* t); // do we need it?
    void run();
    short bytesToShort(char* bytesArr);
private: ConnectionHandler * connectionHandler;
    bool* logOut;
    bool* terminate;


};


#endif


