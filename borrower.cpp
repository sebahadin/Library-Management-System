//============================================================================
// Name         : borrower.cpp
// Author       : Sebahadin Aman Denur 
// Version      : 
// Date Created : 0/5/04/2024
// Date Modified:
// Description  : 
//============================================================================
#include "borrower.h" // Include the header file for the Borrower class

// Constructor for the Borrower class with initialization list
Borrower :: Borrower(string name, string id)
{
	this->name = name; // Initialize the name of the borrower
	this->id = id; // Initialize the ID of the borrower
}

// Method to list the books borrowed by the borrower
void Borrower :: listBooks()
{
	cout << "Books borrowed by " << name << " (" << id << "): " << endl; // Print the borrower's name and ID
	for(int i = 0; i < books_borrowed.size(); i++) // Iterate through the list of borrowed books
	{
		cout << i + 1 << ": " << books_borrowed[i]->title << endl; // Print each book's title with its number in the list
	}
}
