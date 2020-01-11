//
// Created by yairgur@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include <string>

using namespace std;


#ifndef BOOST_ECHO_CLIENT_MESSAGETYPE_H
#define BOOST_ECHO_CLIENT_MESSAGETYPE_H


class MessageType {
public:
    //get
    MessageType(string messageType,string genre, int receiptId);
    string getMessageType();
    string getGenere();
    int getReceiptId();

private:
    string messageType;
    string genre;
    int receiptId;
};

#endif //BOOST_ECHO_CLIENT_MESSAGETYPE_H
