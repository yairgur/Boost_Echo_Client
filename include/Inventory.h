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
    map<string, vector<string>> clientsBooks;
    map<string, string> borrowedMap;
    vector<string> wishToBorrow;
public:
    map<string, vector<string>> getClientsBooks();
    map<string, string> getBorrowedFromMap();
    vector<string> getListOfClientsBooks(string genre);
    string getBorrowedFrom(string userName);
    bool deleteBook(string name, string genre);
    bool deleteBorrowedBook(string bookName);
    bool contains(string genre, string book);
    bool addBookToInventory(string bookName, string genre);
    bool addBorrowedBook(string bookName, string userName);
    bool isWishToBorrow(string bookName);
    void insertWishToBorrow(string bookName);
    Inventory();
};


#endif //BOOST_ECHO_CLIENT_INVENTORY_H
