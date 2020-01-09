#include "../include/User.h"
#include <vector>

using namespace std;

User::User()
{

}

User::User(string userName, string password) {
    this->userName = std::move(userName);
    this->password = password;
    this->reciptId = 1;
    this->subscriptionId = 1;
}

User* User::instance = 0;
User* User::getInstance(){
    if(User::instance == 0){
        instance = new User();
    }
    return instance;
};

string User::getName()
{
    return userName;
}

int User::getSubscriptionId(){
    return 1;
}

bool User::isLoggedIn(){
    return loggedIn;
}

void User::logIn(){
    loggedIn = true;
}

void User::disconnect() {
    loggedIn = false;
}

void User::insertReceipt(string message){
    receiptMap[reciptId] = message;
    reciptId++;
}

string User::findReceipt(int receiptId){
    return receiptMap[receiptId];
}

Inventory User::getUserInventory() {
    return inventory;
}









