#include <map>
#include <list>
#include <vector>
#include <queue>
#include "User.h"
#include <mutex>


#ifndef BOOST_ECHO_CLIENT_INVENTORY_H
#define BOOST_ECHO_CLIENT_INVENTORY_H
using namespace std;

class Inventory {
private:
    //map<string, string*> clientsBooks;
    map<string, vector<string>> clientsBooks; // gener// vector of books. client has.
    map<string, string> borrowedMap; //
    vector<string> wishToBorrow;
    std::mutex clientsBooksMutex;
    std::mutex wishToBorrowMutex;
    std::mutex borrowedMapMutex;
public:
    Inventory();
    map<string, vector<string>> getClientsBooks();
    map<string, string> getBorrowedFromMap();
    vector<string> getListOfClientsBooks(string genre);
    string getBorrowedFrom(string userName);
    bool deleteFromInventory(string bookName, string genre);
    bool deleteBorrowedBook(string bookName);
    bool isExistInClientBooks(string book);
    bool addBookToInventory(string bookName, string genre);
    string getFromBorrowedMap(string bookName);
    bool addBorrowedBook(string bookName, string userName);
    bool isWishToBorrow(string bookName);
    void insertWishToBorrow(string bookName);
    string toString();
    void deleteFromWishList(string bookName);
};


#endif //BOOST_ECHO_CLIENT_INVENTORY_H
