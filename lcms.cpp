//============================================================================
// Name         : lcms.cpp
// Author       : Sebahadin Aman Denur 
// Version      : 
// Date Created : 0/5/04/2024
// Date Modified:
// Description  : 
//============================================================================
#include <fstream> 
#include <iostream> 
#include "lcms.h" 
using namespace std; 

// Constructor for the LCMS class, initializes a new library tree with a given name
LCMS :: LCMS(string name)
{
	this->libTree = new Tree(name); // Allocate memory for a new Tree object and assign it to libTree
}

// Destructor for the LCMS class, cleans up allocated memory
LCMS :: ~LCMS()
{
	delete this->libTree; // Deallocate memory for the library tree

	for(int i = 0 ; i < this->borrowers.size(); i ++) // Loop through the vector of borrowers
	{
		delete this->borrowers[i]; // Deallocate memory for each borrower in the vector
	}
}

// Method to import books from a CSV file into the library system
int LCMS::import(string path) {
    ifstream infile(path); // Open the file at the given path for reading
    if (infile.fail()) { // Check if the file failed to open
        throw runtime_error("Couldn't open the file"); // Throw an exception if the file cannot be opened
    }

    string line; // String to hold each line read from the file
    getline(infile, line); // Read and discard the header line
    int num_import = 0; // Counter for the number of records successfully imported

    while (getline(infile, line)) { // Read each line until the end of the file
        MyVector<string> book_data; // Vector to hold the split fields of each book record
        string field; // String to hold each field value
        bool inQuotes = false; // Flag to track whether the current character is within quotes
        int startField = 0; // Index to mark the start of a field

        // Loop over each character in the line to split it into fields
        for (int i = 0; i <= line.size(); ++i) {
            // Check for end of line or comma outside quotes, marking the end of a field
            if (i == line.size() || (line[i] == ',' && !inQuotes)) {
                field = line.substr(startField, i - startField); // Extract the field
                if (!field.empty() && field.front() == '"' && field.back() == '"') { // Remove surrounding quotes
                    field = field.substr(1, field.size() - 2);
                }
                book_data.push_back(field); // Add the field to the book_data vector
                startField = i + 1; // Set the start of the next field
            } else if (line[i] == '"') { // Toggle the inQuotes flag on encountering a quote
                inQuotes = !inQuotes;
            }
        }

        // Process the book record if it has the correct number of fields
        if (book_data.size() == 7) {
            // Extract book information from the vector
            string title = book_data[0];
            string author = book_data[1];
            string isbn = book_data[2];
            int publn_year = stoi(book_data[3]);
            string category = book_data[4];
            int total_copies = stoi(book_data[5]);
            int available_copies = stoi(book_data[6]);

            // Create or find the category node and add the book to it if it doesn't already exist
            Node* temp = libTree->createNode(category);
            bool found = false; // Flag to indicate if the book was found in the category
            for (int i = 0; i < temp->books.size() && !found; ++i) {
                if (temp->books[i]->title == title) {
                    found = true; // Set flag if book exists
                }
            }
            if (!found) { // If book doesn't exist, add it
                temp->books.push_back(new Book(title, author, isbn, publn_year, total_copies, available_copies));
                // Increment the book count for the category and its ancestors
                Node* toUpdate = temp;
                while (toUpdate) {
                    toUpdate->bookCount += 1;
                    toUpdate = toUpdate->parent;
                }
                num_import++; // Increment the import counter
            }
        } else { // If the book record is malformed, skip it and print an error
            cerr << "Skipping malformed line: " << line << endl;
        }
    }

    infile.close(); // Close the file stream
    cout << num_import << " records have been imported" << endl; // Print the number of imported records
    return num_import; // Return the count of imported records
}

// Recursive helper function to export book data to a file
int LCMS :: export_helper(Node* node, ofstream& file)
{
    if (node == nullptr) // Base case: node is null
    {
        return 0;
    }
    if(node->children.size() == 0) // If the node has no children, it's a leaf node
    {
        return libTree->exportData(node, file); // Export the node's data
    }

    int sum = libTree->exportData(node, file); // Export the current node's data and get the count

    // Recursively call export_helper for each child and add their counts to the sum
    for (int i = 0; i < node->children.size(); ++i)
    {
        sum += export_helper(node->children[i], file);
    }
    return sum; // Return the total count of exported records

}

// Method to export all books to a given file
void LCMS :: exportData(string path)
{
    ofstream outfile(path); // Open the file at the given path for writing

    if (outfile.fail()) // Check if the file failed to open
    {
        throw runtime_error("Couldn't export the data"); // Throw an exception if the file cannot be opened
    }
    else
    {
        // Write the CSV header
        outfile << "Title" << "," << "Author" << "," << "ISBN" << "," << "Publication Year" << "," << "Total Copies" << "," << "Available Copies" << endl;
        int count = export_helper(libTree->getRoot(), outfile); // Export the data starting from the root
        std::cout << count << " records have been successfully exported to " << path << std::endl; // Print the export summary

        outfile.close(); // Close the file stream
    }
}

// Method to display all books of a specific category
void LCMS :: findAll(string category)
{
    Node* node = libTree->getNode(category); // Find the node for the given category

    if (node == nullptr) // If the category does not exist
    {
        cout << "Category " << category << " does not exist" << endl;
    }
    else
    {
        libTree->printAll(node); // Print all books in the category
        cout << node->bookCount << " records found" << endl; // Print the count of found records
    }
}

// Helper function to find a book in the library tree
Book* LCMS::find_book_helper(Node* node, Tree* tree, const string& title) {
    if (node == nullptr) return nullptr; // If the node is null, return nullptr indicating the book is not found

    // Try to find the book in the current node if it's a leaf node
    if (node->children.size() == 0)
    {
        Book* foundBook = tree->findBook(node, title); // Search for the book in the current node
        if (foundBook != nullptr) 
        {
            return foundBook; // If found, return the book
        }
        return nullptr;    // If not found, return nullptr
    }

    // If the node is not a leaf node, first check in the current node
    Book* foundBook = tree->findBook(node, title);
    if (foundBook != nullptr) 
    {
        return foundBook; // If found, return the book
    }

    // If the book is not found in the current node, search in the children nodes
    for (int i = 0; i < node->children.size(); ++i) {
        foundBook = find_book_helper(node->children[i], tree, title); // Recursively search in each child
        if (foundBook != nullptr) {
            return foundBook; // If found in a child, return the book
        }
    }

    // If the book is not found in the current node or any children, return nullptr
    return nullptr;
}

// Method to find a book by title and display its details
void LCMS :: findBook(string bookTitle)
{
    Book* b1 = find_book_helper(this->libTree->getRoot(), this->libTree, bookTitle); // Use the helper to find the book
    if (b1 != nullptr) {
        cout << "Book found in the library:" << endl;
        b1->display(); // Display the book's details if found
    } else 
    {
        cout << "Book not found in the library." << endl; // Print a message if the book is not found
    }
}

// Method to add a new book to the library
void LCMS::addBook() 
{
    // Prompt the user to enter book details
    string title, author, isbn, category;
    int publn_year, total_copies, available_copies;

    cout << "Enter Title: ";
    getline(cin >> ws, title); // Read the title with leading whitespace skipped
    cout << "Enter Author(s): ";
    getline(cin, author);
    cout << "Enter ISBN: ";
    cin >> isbn;
    cout << "Enter Publication Year: ";
    cin >> publn_year;
    cout << "Enter number of total copies: ";
    cin >> total_copies;
    cout << "Enter number of available copies: ";
    cin >> available_copies;

    if (available_copies > total_copies) 
    {
        throw invalid_argument("Number of available copies cannot exceed total copies."); // Validate copies count
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    cout << "Enter Category: ";
    getline(cin, category); // Read the category

    Node* node = libTree->createNode(category); // Create or find the node for the category
    bool bookExists = false;
    for (int i = 0; i < node->books.size(); ++i) 
    {
        if (node->books[i]->title == title) 
        {
            bookExists = true; // Check if the book already exists in the category
            break;
        }
    }

    if (!bookExists) { // If the book does not exist, add it
        node->books.push_back(new Book(title, author, isbn, publn_year, total_copies, available_copies)); // Add the new book

        Node* toUpdate = node; // Update book count for the category and its ancestors
        while (toUpdate) 
        {
            libTree->updateBookCount(toUpdate, 1); // Update the book count
            toUpdate = toUpdate->parent;
        }
        cout << "Book " << title << " has been successfully added to the catalog." << endl;
    } else {
        cout << "A book with this title already exists in the category." << endl; // Inform the user if the book already exists
    }
}

// Method to edit details of an existing book
void LCMS :: editBook(string bookTitle)
{
    Book* b1 = find_book_helper(this->libTree->getRoot(), this->libTree, bookTitle); // Find the book in the library
 
    if (b1 == nullptr) 
    {
        cout << "Book not found in the library." << endl; // If the book is not found, inform the user and return
        return;
    }

    do 
    {
        string user_input = "";
        string command = "";
        string parameter = "";
        try {
            // Show the fields that can be edited
            cout << "1: Title" << endl;
            cout << "2: Author" << endl;
            cout << "3: ISBN" << endl;
            cout << "4: Publication Year" << endl;
            cout << "5: Total Copies" << endl;
            cout << "6: Available Copies" << endl;
            cout << "7: Exit" << endl;
            cout << "Choose the field you want to edit: ";
            getline(cin, user_input); // Read the user's choice

            stringstream sstr(user_input); // Use stringstream to parse the input
            getline(sstr, command, ' '); // Get the command (field number to edit)

            int choice = stoi(command); // Convert the command to an integer

            if (choice >= 1 && choice <= 6) 
            {
                cout << "> ";
                getline(cin, parameter); // Read the new value for the chosen field
            }

            // Update the selected field with the new value
            switch (choice) 
            {
                case 1:
                    b1->title = parameter; // Update the title
                    break;
                case 2:
                    b1->author = parameter; // Update the author
                    break;
                case 3:
                    b1->isbn = parameter; // Update the ISBN
                    break;
                case 4:
                    b1->publication_year = stoi(parameter); // Update the publication year
                    break;
                case 5:
                    b1->total_copies = stoi(parameter); // Update the total copies
                    break;
                case 6:
                    b1->available_copies = stoi(parameter); // Update the available copies
                    break;
                case 7:
                    cout << "Changes made have been successfully saved to the book details" << endl;
                    return; // Exit the editing loop
                default:
                    cout << "Invalid option, please try again." << endl; // Handle invalid options
            }
        } catch (exception &ex) 
        {
            cout << "Error: " << ex.what() << endl; // Catch and display any errors
        }
    } while (true); // Repeat until the user chooses to exit
}

// Method for borrowing a book
void LCMS::borrowBook(string bookTitle)
{
    Book* b1 = find_book_helper(this->libTree->getRoot(), this->libTree, bookTitle); // Find the book in the library

    if (b1 == nullptr)
    {
        cout << "Book not found in the library." << endl; // Inform the user if the book is not found
        return;
    }
    if (b1->available_copies > 0) // Check if there are copies available to borrow
    {
        // Prompt the user for borrower details
        string name, id;
        cout << "Enter borrower's name: ";
        cin >> name;
        cout << "Enter borrower's id: ";
        cin >> id;

        Borrower* borrower = new Borrower(name, id); // Create a new borrower object
        bool foundInCurrent = false, foundInAll = false, foundInLib = false;

        // Check if the borrower is already borrowing the book
        for (int i = 0; i < b1->currentBorrowers.size() && !foundInCurrent; ++i)
        {
            if (b1->currentBorrowers[i]->name == name && b1->currentBorrowers[i]->id == id)
            {
                foundInCurrent = true; // Mark as found in current borrowers
                break;
            }
        }

        // If the borrower is not already borrowing the book, proceed
        if (!foundInCurrent)
        {
            // Check if the borrower has ever borrowed this book before
            for (int i = 0; i < b1->allBorrowers.size() && !foundInAll; ++i)
            {
                if (b1->allBorrowers[i]->name == name && b1->allBorrowers[i]->id == id)
                {
                    foundInAll = true; // Mark as found in all borrowers
                    break;
                }
            }

            // Check if the borrower is registered in the library system
            for (int i = 0; i < this->borrowers.size() && !foundInLib; ++i)
            {
                if (this->borrowers[i]->name == name && this->borrowers[i]->id == id)
                {
                    foundInLib = true; // Mark as found in library borrowers
                    break;
                }
            }

            // If the borrower is not found in all borrowers, add them
            if (!foundInAll)
            {
                b1->allBorrowers.push_back(borrower);
            }
            // If the borrower is not found in library borrowers, add them
            if (!foundInLib)
            {
                this->borrowers.push_back(borrower);
            }

            // Add the borrower to the current borrowers of the book
            b1->currentBorrowers.push_back(borrower);
            // Add the book to the list of books borrowed by the borrower
            borrower->books_borrowed.push_back(b1);

            b1->available_copies--; // Decrement the available copies of the book
            cout << "Book " << b1->title << " has been issued to " << name << endl; // Inform the user that the book has been issued
        }
        else
        {
            delete borrower; // If the borrower is already borrowing the book, delete the newly created borrower object
            cout << "Book with title: " << b1->title << " is already borrowed by: " << name << endl; // Inform the user
        }
    }
    else
    {
        cout << "Book " << b1->title << " is not available in the library right now!" << endl; // Inform the user if no copies are available
    }
}

// Method for returning a borrowed book
void LCMS::returnBook(string bookTitle) 
{
    Book* b1 = find_book_helper(this->libTree->getRoot(), this->libTree, bookTitle); // Find the book in the library
    if (b1 == nullptr) 
    {
        cout << "Book not found in the library." << endl; // Inform the user if the book is not found
        return;
    }

    // Prompt the user for borrower details
    string name, id;
    cout << "Enter borrower's name: ";
    cin >> name;
    cout << "Enter borrower's id: ";
    cin >> id;

    // Loop through the list of current borrowers of the book
    for (int borrowerIndex = 0; borrowerIndex < b1->currentBorrowers.size(); ++borrowerIndex) 
    {
        Borrower* currentBorrower = b1->currentBorrowers[borrowerIndex];
        if (currentBorrower->name == name && currentBorrower->id == id) // Check if the borrower matches the input
        {
            // Loop through the list of books borrowed by the borrower to find the book being returned
            for (int bookIndex = 0; bookIndex < currentBorrower->books_borrowed.size(); ++bookIndex) 
            {
                if (currentBorrower->books_borrowed[bookIndex]->title == bookTitle) 
                {
                    currentBorrower->books_borrowed.erase(bookIndex); // Remove the book from the borrower's list
                    b1->available_copies++; // Increment the available copies of the book
                    cout << "Book has been successfully returned." << endl; // Inform the user that the book has been returned
                    b1->currentBorrowers.erase(borrowerIndex); // Remove the borrower from the list of current borrowers
                    return; // Exit the method
                }
            }
        }
    }

    cout << "Borrower not found." << endl; // Inform the user if the borrower is not found in the list of current borrowers
}

// Method to list the current borrowers of a book
void LCMS :: listCurrentBorrowers(string bookTitle)
{
    Book* b1 = find_book_helper(this->libTree->getRoot(), this->libTree, bookTitle); // Find the book in the library
    if (b1 == nullptr) 
    {
        cout << "Book not found in the library." << endl; // Inform the user if the book is not found
    }
    else
    {
        // Loop through the list of current borrowers and print their details
        for (int i = 0; i < b1->currentBorrowers.size(); ++i)
        {
            cout << i + 1 << " " << b1->currentBorrowers[i]->name << "(" << b1->currentBorrowers[i]->id << ")" << endl;
        }
    }
}

// Method to list all borrowers that have ever borrowed a book
void LCMS :: listAllBorrowers(string bookTitle)
{
    Book* b1 = find_book_helper(this->libTree->getRoot(), this->libTree, bookTitle); // Find the book in the library
    if (b1 == nullptr) 
    {
        cout << "Book not found in the library." << endl; // Inform the user if the book is not found
    }
    else
    {
        // Loop through the list of all borrowers and print their details
        for (int i = 0; i < b1->allBorrowers.size(); ++i)
        {
            cout << i + 1 << " " << b1->allBorrowers[i]->name << "(" << b1->allBorrowers[i]->id << ")" << endl;
        }
    }
}

// Method to display the books a borrower has ever borrowed
void LCMS :: listBooks(string borrower_name_id)
{
    string name, id;
    stringstream iss(borrower_name_id); // Use stringstream to split the input string
    getline(iss, name, ','); // Extract the borrower's name
    getline(iss, id); // Extract the borrower's ID

    bool borrowerFound = false; // Flag to track if the borrower is found
    for (int i = 0; i < this->borrowers.size(); ++i) // Loop through the list of borrowers in the library
    {
        if (this->borrowers[i]->name == name && this->borrowers[i]->id == id) // Check if the borrower matches the input
        {
            borrowerFound = true; // Mark the borrower as found
            cout << "Books borrowed by " << name << " (ID: " << id << "):" << endl; // Print the borrower's details
            if (this->borrowers[i]->books_borrowed.empty()) // Check if the borrower has borrowed any books
            {
                cout << "No books borrowed." << endl; // Inform the user if no books have been borrowed
            } 
            else 
            {
                // Loop through the list of books borrowed by the borrower and print their titles
                for (int j = 0; j < this->borrowers[i]->books_borrowed.size(); ++j) 
                {
                    Book* book = this->borrowers[i]->books_borrowed[j];
                    cout << j + 1 << ": " << book->title << endl; 
                }
            }
            break; // Break the loop once the borrower is found
        }
    }

    if (!borrowerFound) // If the borrower is not found
    {
        cout << "Borrower " << name << " (ID: " << id << ") not found." << endl; // Inform the user
    }
}

// Method to remove a book from the library
void LCMS::removeBook(string bookTitle) {
    string userResponse; // String to store the user's response
    while (true) 
    {
        // Prompt the user for confirmation to delete the book
        cout << "Are you sure you want to delete the book \"" << bookTitle << "\"? yes/no: ";
        cin >> userResponse;

        if (userResponse == "yes") 
        {
            // If the user confirms, attempt to delete the book
            bool removed = removeBookHelper(this->libTree->getRoot(), bookTitle); // Use the helper to remove the book
            if (removed) 
            {
                cout << "Book " << bookTitle << " removed successfully." << endl; // Inform the user if the book was successfully removed
            } else 
            {
                cout << "Couldn't delete the book " << bookTitle << ", book doesn't exist in the catalog" << endl; // Inform the user if the book does not exist
            }
            break; // Exit the loop after handling the user's response
        } else if (userResponse == "no") 
        {
            cout << "Deletion canceled." << endl; // Inform the user if the deletion is canceled
            break; // Exit the loop without deleting the book
        }
    }
}

// Helper method to remove a book recursively
bool LCMS::removeBookHelper(Node* node, const string& bookTitle) {
    if (node == nullptr) return false; // If the node is null, return false indicating the book was not found

    // Attempt to remove the book from the current node
    bool foundAndRemoved = libTree->removeBook(node, bookTitle);
    if (foundAndRemoved) {
        // If the book was found and removed, return true
        return true;
    }

    // If the book was not found in the current node, search in the children nodes
    for (int i = 0; i < node->children.size(); ++i) {
        Node* child = node->children[i];
        if (removeBookHelper(child, bookTitle)) {
            // If the book was found and removed in a child node, return true
            return true;
        }
    }

    // If the book was not found in any nodes, return false
    return false;
}

// Method to add a new category to the catalog
void LCMS :: addCategory(string category)
{
    this->libTree->createNode(category); // Create a new node for the category
    cout << category << " has been successfully created." << endl; // Inform the user that the category has been added
}

// Method to find a category in the catalog
void LCMS :: findCategory(string category)
{
    if (libTree->getNode(category) != nullptr) // Check if the category exists in the library
    {
        cout << "Category " << category << " was found in the catalog" << endl; // Inform the user if the category is found
    }
    else
    {
        cout << "Category " << category << " was not found in the catalog" << endl; // Inform the user if the category is not found
    }
}

// Method to remove a category from the catalog
void LCMS :: removeCategory(string category)
{
    Node* n1 = libTree->getNode(category); // Find the node for the category

    if(n1 != nullptr)
    {
        libTree->remove(n1->parent, n1->name); // Remove the category node from the tree
        cout << category << " has been successfully removed" << endl; // Inform the user that the category has been removed
    }
    else
    {
        throw runtime_error("Category does not exist"); // Throw an exception if the category does not exist
    }
}

// Method to edit a category in the catalog
void LCMS :: editCategory(string category)
{
    Node* n1 = libTree->getNode(category); // Find the node for the category
    string name;

    cout << "Enter name of the category" << endl; // Prompt the user for the new name of the category
    cin >> name;
    n1->name = name; // Update the name of the category

    cout << "Category edited successfully" << endl; // Inform the user that the category has been edited
}

// Method to display the catalog in a tree format
void LCMS :: list()                   
{
    libTree->print(); // Call the print method of the library tree to display the catalog
}
