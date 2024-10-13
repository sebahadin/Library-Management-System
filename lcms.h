//============================================================================
// Name         : lcmc.h
// Author       : Sebahadin Aman Denur 
// Version      : 
// Date Created : 0/5/04/2024
// Date Modified:
// Description  : 
//============================================================================
#ifndef _LCMS_H
#define _LCMS_H
#include<string>
#include "tree.h"
#include "myvector.h"
#include "borrower.h"
//#include "book.h"

class LCMS
{
	private:
		Tree *libTree;	//Tree of Categories and books
		MyVector<Borrower*> borrowers; //list of borrowers that have ever borrowed a book	
	public:
		LCMS(string name);
		~LCMS();

		int import(string path); //import books from a csv file
		void exportData(string path); //export all books to a given file
		void findAll(string category); //display all books of a category
		void findBook(string bookTitle); //Find a given book and display its details
		void addBook();	//add a book to the catalog
		void editBook(string bookTitle); //edit a book
		void borrowBook(string bookTitle); //borrow a book
		void returnBook(string bookTitle); //return a book 
		void listCurrentBorrowers(string bookTitle); //list current borrowers of a book
		void listAllBorrowers(string bookTitle); // list all borrowers that have ever borrowed a book
		void listBooks(string borrower_name_id); // display books a borrower has ever borrowed
		void removeBook(string bookTitle);//remove a book from the catalog
		void addCategory(string category); //add a category in the catalog
		void findCategory(string category); //find a category in the catalog
		void removeCategory(string category); //remove a category from the catalog
		void editCategory(string category); //edit a category from the catalog
		void list();			   //display the catalog in tree format by calling the print method of the libTree
		Book* find_book_helper(Node* node, Tree* tree, const string& title);
		bool removeBookHelper(Node* node, const string& bookTitle) ;
		int export_helper(Node* node, ofstream& file);
		
};
#endif