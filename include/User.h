
#ifndef BOOST_ECHO_CLIENT_USER_H
#define BOOST_ECHO_CLIENT_USER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../include/Inventory.h"
#include "MessageType.h"
#include <mutex>


using namespace std;


class User {
public:
    User();
    User(string userName, string passcode);
    void addSubscriptionIdToGenre(string genre, int subscriptionId);
    int getSubscriptionIdFromGenre(string genre);
    MessageType getMessageTypeByReceiptId(int receiptId);
    void addToReceiptIdMap(int receiptId, MessageType * messageType);
    string containsSubscriptionId(int subscriptionId); // for status

    int getSubscriptionId();
    string getName();
    Inventory* getUserInventory();

private:
    //Inventory* inventory;
    string userName;
    string passcode;
    int subscriptionId;
    map<string, int> subscriptionIdMap; // genre to subscription id
    map<int, MessageType*> receiptToMessageType;
    bool loggedIn;

    vector<std::string> books;

    map<string, int> subscribeIdToGenreMap;
    int reciptId;
    std::mutex receiptToMessageTypeMutex;
    std::mutex subscriptionIdMapMutex;

};


#endif //BOOST_ECHO_CLIENT_USER_H
