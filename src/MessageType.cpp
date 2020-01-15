#include "MessageType.h"

MessageType::~MessageType() {}

MessageType::MessageType(string messageType, string genre, int receiptId): messageType(messageType), genre(genre), receiptId(receiptId){}

string MessageType::getGenere() {
    return genre;
}

string MessageType::getMessageType() {
    return messageType;
}

int MessageType::getReceiptId() {
    return receiptId;
}


