
#ifndef BOOST_ECHO_CLIENT_USER_H
#define BOOST_ECHO_CLIENT_USER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../include/Inventory.h"
#include "MessageType.h"

using namespace std;


class User {
public:
    User();
    User(string userName, string passcode);
    void addSubscriptionIdToGenre(string genre, int subscriptionId);
    int getSubscriptionIdFromGenre(string genre);
    MessageType getMessageTypeByReceiptId(int receiptId);
    void addToReceiptIdMap(int receiptId, MessageType * messageType);

    //~User();
    //bool isLoggedIn();
    //void logIn();
    //void disconnect();
    //void insertReceipt(string message);
    //string findReceipt(int reciptId);
    //static User* getInstance();
    //void addBook(const string& book);
    //void setSubscriptionId(string id);
    int getSubscriptionId();
    string getName();
    //Inventory getUserInventory();

private:
    Inventory inventory;
    string userName;
    string passcode;
    int subscriptionId;
    map<string, int> subscriptionIdMap; // genre to subscription id
    map<int, MessageType*> receiptToMessageType;
    bool loggedIn;
    //string gener;
    vector<std::string> books;
    //vector<std::string> subscribedGenres;
    map<string, int> subscribeIdToGenreMap;
    int reciptId;

    //DB *instance; // to get the singleton DB
    //static User *instance;

};


#endif //BOOST_ECHO_CLIENT_USER_H
