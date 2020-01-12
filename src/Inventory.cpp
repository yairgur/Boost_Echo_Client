#include "Inventory.h"
#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

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
    bool flag = false;
    for(vector<string>::iterator it = wishToBorrow.begin(); it != wishToBorrow.end(); ++it)
    {
        if(it->compare(bookName))
            flag = true;
    }
        return flag;
}

void Inventory::insertWishToBorrow(string bookName) {
    wishToBorrow.push_back(bookName);
}



//// delete
bool Inventory::deleteFromInventory(string book, string genre){
    vector<string> clientsBooksInGenre = clientsBooks[genre];
    for(vector<string>::iterator it = clientsBooksInGenre.begin(); it != clientsBooksInGenre.end(); ++it)
    {
        if(*it == book) {
            clientsBooks[genre].erase(it);
            return true;
        }

    }
    return false;
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


bool Inventory::contains(string genre, string book)
{
    vector<string> clientsBooksInGenre = clientsBooks.at(genre);
    for(vector<string>::iterator it = clientsBooksInGenre.begin(); it != clientsBooksInGenre.end(); ++it)
    {
        if(it->compare(book))
            return true;
    }
    return false;
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


