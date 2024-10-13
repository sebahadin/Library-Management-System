//============================================================================
// Name         : book.h
// Author       : Sebahadin Aman Denur 
// Version      : 
// Date Created : 0/5/04/2024
// Date Modified:
// Description  : 
//============================================================================
#ifndef _BOOK_H
#define _BOOK_H
#include<string>
#include "myvector.h"
class Borrower;
class Book
{
	private:
		std::string title;
		std::string author;
		std::string isbn;
		int publication_year;
		int total_copies;
		int available_copies;
		MyVector<Borrower*> currentBorrowers;		//current borrowers of the book
		MyVector<Borrower*> allBorrowers;   //history of all borrowers of the book

	public:
		Book(std::string title, std::string author, std::string isbn, int publication_year,int total_copies, int available_copies);
		void display(); // display details of a book (see output of command findbook)

	public:
		friend class Tree;
		friend class Node;
		friend class LCMS;
		friend class Borrower;
};
#endif