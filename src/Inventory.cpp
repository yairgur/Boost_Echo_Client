#include "Inventory.h"
#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <include/User.h>


using namespace std;

Inventory::Inventory(){

}

map<string, vector<string>> Inventory::getClientsBooks(){
    std::lock_guard<std::mutex> lock(clientsBooksMutex);
    return clientsBooks;
}

map<string, string> Inventory::getBorrowedFromMap()
{
    std::lock_guard<std::mutex> lock(borrowedMapMutex);
    return borrowedMap;
}

vector<string> Inventory::getListOfClientsBooks(string genre){
    std::lock_guard<std::mutex> lock(clientsBooksMutex);
    return clientsBooks.at(genre);
}

string Inventory::getBorrowedFrom (string userName)
{
    std::lock_guard<std::mutex> lock(borrowedMapMutex);
    borrowedMap.at(userName);
}


bool Inventory::isWishToBorrow(string bookName) {
    for(vector<string>::iterator it = wishToBorrow.begin(); it != wishToBorrow.end(); it++){
        if((*it) == bookName)
        {
            return true;
        }
    }
    return false;
}


void Inventory::insertWishToBorrow(string bookName) {

    std::lock_guard<std::mutex> lock(wishToBorrowMutex);
    wishToBorrow.push_back(bookName);
}



//// delete
bool Inventory::deleteFromInventory(string bookName, string genre){

    std::lock_guard<std::mutex> lock(clientsBooksMutex);
    bool deleted = false;
    for(vector<string>::iterator it = clientsBooks[genre].begin(); it != clientsBooks[genre].end() && !deleted; it++)
    {
        if((string)(*it) == bookName)
        {
            cout << "================= We just deleted " << bookName << " from this user Inventory====================" << endl;
            clientsBooks[genre].erase(it);
            deleted = true;
        }
    }
//    for(map<string,vector<string>>::iterator it = clientsBooks.begin(); it != clientsBooks.end() && !deleted; ++it)
//    {
//        for(vector<string>::iterator it1 = (*it).second.begin() ; it1 != (*it).second.end() && !deleted; ++it1)
//        {
//            if((string)(*it1) == book){
//                clientsBooks.erase((*it1));
//                deleted = true;
//            }
//        }
//    }
    return deleted;
}

bool Inventory::deleteBorrowedBook(string bookName){ // todo: add try ..

    std::lock_guard<std::mutex> lock(borrowedMapMutex);
    borrowedMap.erase(bookName);
    return true;

}


//// add
bool Inventory::addBookToInventory(string bookName, string genre) {

    std::lock_guard<std::mutex> lock(clientsBooksMutex);
    if(clientsBooks.find(genre) == clientsBooks.end()){
        vector<string> vect;
        vect.push_back(bookName);
        clientsBooks[genre] = vect;
    }
    else{
        clientsBooks[genre].push_back(bookName);
    }
    return true;
}


bool Inventory::addBorrowedBook(string bookName, string userName) {

    std::lock_guard<std::mutex> lock(borrowedMapMutex);
    borrowedMap[bookName] = userName;
    return true;
}

string Inventory::getFromBorrowedMap(string bookName)
{
    std::lock_guard<std::mutex> lock(borrowedMapMutex);
    string res = borrowedMap[bookName];
    borrowedMap.erase(bookName);
    return res;
}



bool Inventory::isExistInClientBooks(string book){
    std::lock_guard<std::mutex> lock(clientsBooksMutex);
    bool isExist = false;
    for(map<string,vector<string>>::iterator it = clientsBooks.begin(); it != clientsBooks.end(); ++it)
    {
        for(vector<string>::iterator it1 = (*it).second.begin() ; it1 != (*it).second.end(); ++it1)
        {
           if((string)(*it1) == book){
               isExist = true;
           }
        }
    }
    return isExist;
}

void Inventory::deleteFromWishList(string bookName)
{
    bool deleted = false;
    for(vector<string>::iterator it = wishToBorrow.begin(); it != wishToBorrow.end() && !deleted; it++){
        if((string)(*it) == bookName)
        {
            wishToBorrow.erase(it);
            deleted = true;
        }
    }
}


string Inventory::toString(){
    std::lock_guard<std::mutex> lock(clientsBooksMutex);
    string bookList = "";

    for(map<string,vector<string>>::iterator it = clientsBooks.begin(); it != clientsBooks.end(); ++it)
    {
        for(vector<string>::iterator it1 = (*it).second.begin() ; !(*it).second.empty() && it1 != (*it).second.end(); ++it1)
        {
            bookList = bookList + "," + *it1;
        }
    }
    if(bookList.size()>1)
        return bookList.substr(1,bookList.length());
    return bookList;
}


