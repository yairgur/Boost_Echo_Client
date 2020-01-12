//
// Created by yairgur@wincs.cs.bgu.ac.il on 07/01/2020.
//
#include <map>
#include <list>
#include <vector>


#ifndef BOOST_ECHO_CLIENT_INVENTORY_H
#define BOOST_ECHO_CLIENT_INVENTORY_H
using namespace std;

class Inventory {
private:
    //map<string, string*> clientsBooks;
    map<string, vector<string>> clientsBooks;
    map<string, string> borrowedMap;
    vector<string> wishToBorrow;
public:
    Inventory();
    map<string, vector<string>> getClientsBooks();
    map<string, string> getBorrowedFromMap();
    vector<string> getListOfClientsBooks(string genre);
    string getBorrowedFrom(string userName);
    bool deleteFromInventory(string name);
    bool deleteBorrowedBook(string bookName);
    bool isExistInClientBooks(string book);
    bool addBookToInventory(string bookName, string genre);
    bool addBorrowedBook(string bookName, string userName);
    bool isWishToBorrow(string bookName);
    void insertWishToBorrow(string bookName);
    string toString();
};


#endif //BOOST_ECHO_CLIENT_INVENTORY_H
