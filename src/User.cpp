#include "User.h"
#include "MessageType.h"
#include <vector>

using namespace std;

User::~User(){}


User::User(string userName, string passcode):userName(userName),passcode(passcode), reciptId(1), subscriptionId(1) {
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

MessageType* User::getMessageTypeByReceiptId(int receiptId) {
    std::lock_guard<std::mutex> lock(receiptToMessageTypeMutex);
    return receiptToMessageType[receiptId];

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





