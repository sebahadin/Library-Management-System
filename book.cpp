//============================================================================
// Name         : book.h
// Author       : Sebahadin Aman Denur 
// Version      : 
// Date Created : 0/5/04/2024
// Date Modified:
// Description  : 
//============================================================================
#include "book.h" // Include the header file for the Book class

// Constructor for the Book class with initialization list
Book::Book(std::string title, std::string author, std::string isbn, int publication_year, int total_copies, int available_copies)
{
    this->title = title; // Initialize the title of the book
    this->author = author; // Initialize the author(s) of the book
    this->isbn = isbn; // Initialize the ISBN of the book
    this->publication_year = publication_year; // Initialize the publication year of the book
    this->total_copies = total_copies; // Initialize the total copies of the book
    this->available_copies = available_copies; // Initialize the available copies of the book
}

// Method to display the details of a book
void Book :: display() 
{
    cout << "===================================================================================================" << endl; // Print separator line
    cout << "Title: " << title << endl; // Display the title of the book
    cout << "Author(s): " << author << endl; // Display the author(s) of the book
    cout << "ISBN : " << isbn << endl; // Display the ISBN of the book
    cout << "Year : " << publication_year << endl; // Display the publication year of the book
    cout << "Total Copies : " << total_copies << endl; // Display the total copies of the book
    cout << "Available Copies : " << available_copies << endl; // Display the available copies of the book

    cout << "===================================================================================================" << endl; // Print separator line
}
