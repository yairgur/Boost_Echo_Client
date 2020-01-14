#include "../include/User.h"
#include "../include/MessageType.h"
#include <vector>

using namespace std;

//User::~User(){}

User::User()
{

}

User::User(string userName, string passcode) {
    this->userName = userName;
    this->passcode = passcode;
    this->reciptId = 1;
    this->subscriptionId = 1;
    this->inventory = new Inventory();
}

//User* User::instance = 0;
//User* User::getInstance(){
//    if(User::instance == 0){
//        instance = new User();
//    }
//    return instance;
//};

string User::getName()
{
    return userName;
}

int User::getSubscriptionId(){
    return 1;
}

//bool User::isLoggedIn(){
//    return loggedIn;
//}
//
//void User::logIn(){
//    loggedIn = true;
//}
//
//void User::disconnect() {
//    loggedIn = false;
//}
//
//void User::insertReceipt(string message){
//    receiptMap[reciptId] = message;
//    reciptId++;
//}
//
//string User::findReceipt(int receiptId){
//    return receiptMap[receiptId];
//}
//
Inventory* User::getUserInventory() {
    return inventory;
}

void User::addSubscriptionIdToGenre(string genre, int subscriptionId) {
    subscribeIdToGenreMap.insert(pair<string, int>(genre, subscriptionId));
}

int User::getSubscriptionIdFromGenre(string genre) {
    return subscribeIdToGenreMap[genre];
}

void User::addToReceiptIdMap(int receiptId, MessageType *messageType)
{
    std::lock_guard<std::mutex> lock(receiptToMessageTypeMutex);
    receiptToMessageType.insert(pair<int, MessageType*>(receiptId, messageType));
}

MessageType User::getMessageTypeByReceiptId(int receiptId) {
    std::lock_guard<std::mutex> lock(receiptToMessageTypeMutex);
    return *receiptToMessageType[receiptId];

}

string User::containsSubscriptionId(int subscriptionId)
{
    for(map<string, int>::iterator it = subscribeIdToGenreMap.begin(); it != subscribeIdToGenreMap.end(); ++it)
    {
        if(it->second == subscriptionId) {
            return it->first;
        }

    }
    return "";
}





