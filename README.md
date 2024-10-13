# Library Management System

This repository contains the implementation of a **Library Management System (LMS)** that manages books, borrowers, and book transactions in a library. This system allows for book issuance, return tracking, and borrower management. It is written in C++ and is structured into several modular components, each focusing on a specific aspect of the system.

## Features

- Manage a library’s collection of books.
- Track borrowers and their information.
- Issue and return books.
- Data persistence through CSV file handling for books and borrowers.
- Custom data structures for optimized storage and retrieval.

## Files and Structure

### 1. `main.cpp`
This file serves as the entry point to the Library Management System. It manages the overall flow of the program, handling user interaction through a command-line interface (CLI). The menu allows users to interact with various functionalities of the system, such as adding books, borrowers, issuing, and returning books. Key functions include:

- Displaying menu options.
- Capturing user inputs to execute the corresponding actions.
- Managing the high-level logic and orchestration of system components.

**Code:** [`main.cpp`](./main.cpp)

---

### 2. `lcms.h` / `lcms.cpp`
The **Library Core Management System** (LCMS) is the core class that coordinates the interaction between books, borrowers, and transactions. This is where the main operations for adding, removing, issuing, and returning books are implemented. The class includes methods such as:

- `addBook()`: Adds a new book to the system.
- `removeBook()`: Removes a book based on its ID or title.
- `addBorrower()`: Registers a new borrower in the system.
- `issueBook()`: Issues a book to a borrower by linking their ID to the book.
- `returnBook()`: Marks a book as returned and updates its status.
- `saveData()`: Saves the current library state (books and borrowers) to CSV files.
- `loadData()`: Loads existing book and borrower data from CSV files.

**Code:** [`lcms.h`](./lcms.h) | [`lcms.cpp`](./lcms.cpp)

---

### 3. `borrower.h` / `borrower.cpp`
This module handles all **borrower-related operations**, including:

- **Borrower Structure**: The class defines the borrower, including attributes like name, ID, contact information, and the books currently borrowed by them.
- `addBorrower()`: Adds a new borrower to the system.
- `getBorrower()`: Retrieves borrower information based on ID.
- `displayBorrowers()`: Displays a list of all borrowers.

**Code:** [`borrower.h`](./borrower.h) | [`borrower.cpp`](./borrower.cpp)

---

### 4. `book.h` / `book.cpp`
The **Book Module** manages the collection of books in the library. Key attributes of the book include:

- **Title**, **Author**, **ISBN**, **Publication Year**, and **Availability Status**.
- The `book.cpp` file provides methods for handling book data, such as:
  - `addBook()`: Adds a new book.
  - `removeBook()`: Removes a book by its ID or title.
  - `updateBookInfo()`: Updates details about a book.
  - `displayBooks()`: Displays all books currently available in the system.

**Code:** [`book.h`](./book.h) | [`book.cpp`](./book.cpp)

---

### 5. `tree.h` / `tree.cpp`
This part of the system implements a **Binary Search Tree (BST)** or other tree-based structure for efficiently storing and retrieving data about books and borrowers. Operations include:

- **Insertion**, **deletion**, and **searching** for nodes based on specific keys (like book ID or borrower ID).
- The tree structure ensures optimal performance for large datasets by providing efficient searching and sorting mechanisms.

**Code:** [`tree.h`](./tree.h) | [`tree.cpp`](./tree.cpp)

---

### 6. `myvector.h`
This file implements a **custom vector class**, similar to C++’s built-in `std::vector`. It provides:

- **Dynamic resizing**: The vector automatically grows as elements are added.
- **Efficient memory management**: Handling dynamic arrays with features like capacity management and size tracking.
- **Operations like `push_back()`, `pop_back()`, and random access**: These operations allow for efficient management of collections of books or borrowers.

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

