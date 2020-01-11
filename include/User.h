
#ifndef BOOST_ECHO_CLIENT_USER_H
#define BOOST_ECHO_CLIENT_USER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../include/Inventory.h"

using namespace std;


class User {
public:
    User();
    User(string userName, string password);
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
    bool loggedIn;
    //string gener;
    vector<std::string> books;
    //vector<std::string> subscribedGenres;
    //map<int, string> receiptMap; //
    int reciptId;
    //DB *instance; // to get the singleton DB
    //static User *instance;

};


#endif //BOOST_ECHO_CLIENT_USER_H
