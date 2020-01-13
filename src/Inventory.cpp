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
    return clientsBooks;
}

map<string, string> Inventory::getBorrowedFromMap()
{
    return borrowedMap;
}

vector<string> Inventory::getListOfClientsBooks(string genre){
    return clientsBooks.at(genre);
}

string Inventory::getBorrowedFrom (string userName)
{
    borrowedMap.at(userName);
}


bool Inventory::isWishToBorrow(string bookName) {
    map<string, string>::iterator it = wishToBorrow.find(bookName);
    if(it != wishToBorrow.end())
    {
        return true;
    }
    return false;
}


void Inventory::insertWishToBorrow(string bookName, string user) {
    wishToBorrow[bookName] = user;
}



//// delete
bool Inventory::deleteFromInventory(string book){
    bool deleted = false;
    for(map<string,vector<string>>::iterator it = clientsBooks.begin(); it != clientsBooks.end() && !deleted; ++it)
    {
        for(vector<string>::iterator it1 = (*it).second.begin() ; it1 != (*it).second.end() && !deleted; ++it1)
        {
            if((string)(*it1) == book){
                clientsBooks.erase((*it1));
                deleted = true;
            }
        }
    }
    return deleted;
}

bool Inventory::deleteBorrowedBook(string bookName){ // todo: add try ..
    borrowedMap.erase(bookName);
    return true;

}


//// add
bool Inventory::addBookToInventory(string bookName, string genre) {
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
    borrowedMap[bookName] = userName;
    return true;
}

string Inventory::getFromBorrowedMap(string bookName)
{
    string res = borrowedMap[bookName];
    borrowedMap.erase(bookName);
    return res;
}



bool Inventory::isExistInClientBooks(string book)
{
    bool isExist = false;
    for(map<string,vector<string>>::iterator it = clientsBooks.begin(); it != clientsBooks.end(); ++it)
    {
        for(vector<string>::iterator it1 = (*it).second.begin() ; it1 != (*it).second.end(); ++it1)
        {
           if((*it1) == book){
               isExist = true;
           }
        }
    }
    return isExist;
}

string Inventory::toString(){
    string bookList = "";

    for(map<string,vector<string>>::iterator it = clientsBooks.begin(); it != clientsBooks.end(); ++it)
    {
        for(vector<string>::iterator it1 = (*it).second.begin() ; it1 != (*it).second.end(); ++it1)
        {
            bookList = bookList + "," + *it1;
        }
    }

    return bookList.substr(1,bookList.length());
}


