
#ifndef BOOST_ECHO_CLIENT_USER_H
#define BOOST_ECHO_CLIENT_USER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../include/Inventory.h"
#include "DB.h"

using namespace std;


class User {
public:
    User();
    static User* getInstance();
    ~User();
    void addBook(const string& book);
    void setSubscriptionId(string id);
    int getSubscriptionId();
    string getName();
    bool isLoggedIn();
    void logIn();
    void disconnect();
    void insertReceipt(string message);
    string findReceipt(int reciptId);
    User(string userName, string password);
    Inventory getUserInventory();

private:
    map<string, int> subscriptionIdMap; // genre to subscription id
    static User *instance;
    string userName;
    bool loggedIn;
    string password;
    string gener;
    vector<std::string> books;
    vector<std::string> subscribedGenres;
    int subscriptionId;
    map<int, string> receiptMap; // 
    Inventory inventory;
    int reciptId;
    //DB *instance; // to get the singleton DB
};


#endif //BOOST_ECHO_CLIENT_USER_H
