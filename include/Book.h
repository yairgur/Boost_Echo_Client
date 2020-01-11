//
// Created by yairgur@wincs.cs.bgu.ac.il on 11/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H


class Book {
public:
    string getBookName();
    string getBookGenre();

private:
    string bookName;
    string bookGenre;


};


#endif //BOOST_ECHO_CLIENT_BOOK_H
