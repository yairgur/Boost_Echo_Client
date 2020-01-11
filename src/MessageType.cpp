#include "MessageType.h"

MessageType::MessageType(string messageType, string genre, int receiptId){
this->messageType = messageType;
this->genre = genre;
this->receiptId = receiptId;
}

string MessageType::getGenere() {
    return genre;
}

string MessageType::getMessageType() {
    return messageType;
}

int MessageType::getReceiptId() {
    return receiptId;
}


