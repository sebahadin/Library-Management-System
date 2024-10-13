# Library Management System

This repository contains the implementation of a **Library Management System (LMS)** written in C++. The system manages books, borrowers, and book transactions within a library. It includes functionalities for importing/exporting book data, managing book categories, and handling borrower information.

## Features

- Add, edit, remove books.
- Borrow and return books.
- Manage categories for books (such as genres or sections).
- Export and import book data from/to CSV files.
- List books by category and borrower.
- Track current and past borrowers.

## Files and Structure

### 1. `main.cpp`
This file serves as the entry point for the Library Management System. It handles user interaction via the command line and invokes the appropriate methods from the LCMS.

**Code:** [`main.cpp`](./main.cpp)

---

### 2. `lcms.h` / `lcms.cpp`
The **LCMS** class is the core of the system, responsible for managing books, borrowers, and categories. Key methods include:

- `import()`: Imports books from a CSV file.
- `exportData()`: Exports all books to a given file.
- `findAll()`: Displays all books in a given category.
- `findBook()`: Finds and displays a book by title.
- `addBook()`: Adds a new book to the library.
- `editBook()`: Edits details of an existing book.
- `borrowBook()`: Issues a book to a borrower.
- `returnBook()`: Processes the return of a borrowed book.
- `removeBook()`: Removes a book from the catalog.
- `listCurrentBorrowers()`: Lists the current borrowers of a book.
- `listAllBorrowers()`: Lists all borrowers that have ever borrowed a book.
- `listBooks()`: Lists all books borrowed by a specific borrower.
- `addCategory()`: Adds a category to the catalog.
- `findCategory()`: Finds a category in the catalog.
- `removeCategory()`: Removes a category from the catalog.
- `editCategory()`: Edits a category's name.
- `list()`: Displays the entire catalog as a tree structure.

**Code:** [`lcms.h`](./lcms.h) | [`lcms.cpp`](./lcms.cpp)

---

### 3. `borrower.h` / `borrower.cpp`
The **Borrower** class represents a borrower in the library system. Borrowers can borrow and return books, and the system tracks which books they have borrowed. Key methods include:

- `listBooks()`: Lists all the books a borrower has borrowed.

**Code:** [`borrower.h`](./borrower.h) | [`borrower.cpp`](./borrower.cpp)

---

### 4. `book.h` / `book.cpp`
The **Book** class manages individual book information. Each book contains attributes such as title, author, ISBN, publication year, total copies, and available copies. Key methods include:

- `display()`: Displays the details of a book.

**Code:** [`book.h`](./book.h) | [`book.cpp`](./book.cpp)

---

### 5. `tree.h` / `tree.cpp`
The **Tree** class manages the hierarchical structure of categories and subcategories in the library, along with their associated books. Key methods include:

- `insert()`: Inserts a new category or subcategory into the catalog.
- `remove()`: Removes a category from the catalog.
- `createNode()`: Creates a new node (category).
- `findBook()`: Finds a book in a specific category.
- `removeBook()`: Removes a book from a category.
- `printAll()`: Prints all books within a category and its subcategories.
- `exportData()`: Exports book data from a specific category to a file.
- `print()`: Prints the entire catalog as a tree structure.

**Code:** [`tree.h`](./tree.h) | [`tree.cpp`](./tree.cpp)

---

### 6. `myvector.h`
This file implements a custom **Vector** class that supports dynamic resizing and common operations such as:

- `push_back()`: Adds an element to the end of the vector.
- `insert()`: Inserts an element at a specified position.
- `erase()`: Removes an element from a specified position.
- `at()`: Retrieves the element at a specified position.
- `shrink_to_fit()`: Shrinks the vector's capacity to its current size.

**Code:** [`myvector.h`](./myvector.h)

---

### 7. `booklist.csv` & `bookslist_long.csv`
These CSV files contain **data for books** that can be loaded into the system. They serve as a persistent store of information. `booklist.csv` contains a small dataset for testing, while `bookslist_long.csv` contains a larger dataset for more extensive testing. These files are:

- **Read at the start** to load book data into the system.
- **Updated during runtime** whenever books are added or removed.
- **Saved upon program exit** to ensure persistence of changes made during execution.

**Files:** [`booklist.csv`](./booklist.csv) | [`bookslist_long.csv`](./bookslist_long.csv)

---

### 8. `makefile`
The `makefile` is used to compile and build the project. It defines the instructions for building the project, automating the compilation process with commands like:


**Code:** [`makefile`](./makefile)



## How to Use

### Menu Options
When you run the program, a menu will be presented with the following options:

- **Add a Book**: Adds a new book to the library’s collection by capturing its details (title, author, etc.).
- **Remove a Book**: Removes a book based on ID or title.
- **Add a Borrower**: Registers a new borrower in the system.
- **Issue a Book**: Issues a book to a registered borrower, marking it as unavailable.
- **Return a Book**: Marks a book as returned, updating its availability in the system.

### Input and Output
- The system reads initial book and borrower data from CSV files (`booklist.csv`) and saves updated data back to these files at the end of the session.
- User input is required through the CLI to perform operations like adding books or issuing them.

## Future Enhancements

- Integration with a GUI for easier management and user experience.
- Expansion to handle multiple libraries and synchronize data between them.
- Enhancing the system to handle overdue books and fines.


```bash

