//============================================================================
// Name         : tree.cpp
// Author       : Sebahadin Aman Denur 
// Version      : 
// Date Created : 0/5/04/2024
// Date Modified:
// Description  : 
//============================================================================

#include "tree.h" 
#include <fstream> 
#include <iostream> 

// Constructor for a Node object, initializing with a given name
Node :: Node(string name)
{
	this->name = name; // Set the name of the node
	this->parent = nullptr; // Initially, this node has no parent
	this->bookCount = 0; // Initialize the book count to 0
}

// Method to get the category path for a node
string Node::getCategory(Node* node)
{
    if (node->parent == nullptr) return ""; // If the node has no parent, return an empty string

    string path = node->name; // Start with the name of the current node
    // Iterate upwards through the tree, prepending each parent's name to the path
    while (node->parent != nullptr && node->parent->parent != nullptr)
    {
        node = node->parent; // Move to the parent node
        path = node->name + "/" + path; // Prepend the parent's name to the path
    }

    return path; // Return the computed path
}

// Destructor for a Node, responsible for cleaning up dynamically allocated memory
Node :: ~Node()
{
    // Delete all dynamically allocated child nodes
	for(int i = 0 ; i < this->children.size(); i ++)
	{
		delete this->children[i]; // Delete each child node
	}

    // Delete all dynamically allocated books
	for(int i = 0 ; i < this->books.size(); i ++)
	{
		delete this->books[i]; // Delete each book
	}
}

// Constructor for the Tree class, initializing with a root node name
Tree :: Tree(string rootName)
{
    root = new Node(rootName); // Create a new Node as the root of the tree
}

// Destructor for the Tree class, cleans up the root node
Tree :: ~Tree()
{
    delete this->root; // Delete the root node, freeing its memory
}

// Method to get the root node of the tree
Node* Tree :: getRoot()
{
	return this->root; // Return a pointer to the root node
}

// Method to insert a new child node under a given parent node
void Tree :: insert(Node* node, string name)
{	
    bool exists = false; // Flag to track if the child already exists
	for (int i = 0; i < node->children.size(); ++i) // Iterate over existing children
	{
		if(node->children[i]->name == name) 
		{
			exists = true; // Mark as exists if found
			break;
		}
	}

    // If the child does not already exist, add it
	if (!exists)
	{
		Node* temp = new Node(name); // Create a new node
		temp->parent = node; // Set the parent of the new node
		node->children.push_back(temp); // Add the new node to the parent's children vector
	}
	else
	{
	    // If the child already exists, throw an error
		throw runtime_error("child with name " + name + " already exists in " + node->name);
	}
}

// Method to remove a child node from a given parent node
void Tree::remove(Node* node, string child_name) {
    if (node != nullptr) // Ensure the parent node is not null
    {
        bool found = false; // Flag to indicate if the child is found
        for (int i = 0; i < node->children.size(); i++) // Iterate over the children
        {
            if (node->children[i]->name == child_name) // Check if the child's name matches
            {
                // Calculate the total book count to be decremented
                int decrementCount = node->children[i]->bookCount;

                // Update bookCount for the node (parent of the child being removed) and all its ancestors
                Node* toUpdate = node; // Start from the parent node
                while (toUpdate != nullptr) 
                {
                    toUpdate->bookCount -= decrementCount; // Decrement the book count
                    toUpdate = toUpdate->parent; // Move to the parent node
                }

                // Remove the child node and free its memory
                delete node->children[i]; // Free the memory of the node being removed
                node->children.erase(i); // Erase the child from the vector
                found = true; // Mark as found
                break; // Exit after removing the child
            }
        }
        if (!found) { // If the child is not found, throw an error
            throw runtime_error("Child with name " + child_name + " not found!");
        }
    }
}

// Method to check if a given node is the root of the tree
bool Tree :: isRoot(Node* node)
{
	return node == this->root; // Return true if the node is the root, false otherwise
}

// Method to find a node given a path in the format category/sub-category/...
Node* Tree::getNode(string path) 
{
    int start = 0, end; // Initialize indices for parsing the path
    if (path[start] == '/') start++; // Skip the leading '/' if present

    end = path.find('/', start); // Find the first '/' to delimit the first segment
    string segment; // String to hold each path segment
    if (end != string::npos) {
        segment = path.substr(start, end - start); // Extract the segment from the path
    } else {
        segment = path.substr(start); // If there's no '/', the whole path is the segment
    }

    Node* node = root; // Start from the root node

    do {
        bool exists = false; // Flag to check if the segment exists among the node's children
        for (size_t i = 0; i < node->children.size(); ++i)
        { 
            if (node->children[i]->name == segment) 
            {
                node = node->children[i]; // If the segment matches a child, move to that child
                exists = true; // Mark as exists
                break; // Break the loop since the segment was found
            }
        }
        if (!exists) return nullptr; // If the segment is not found, return nullptr

        if (end == string::npos) break; // If there are no more segments, exit the loop

        // Prepare for the next segment
        start = end + 1; // Move start index past the '/'
        end = path.find('/', start); // Find the next '/'
        if (end != string::npos)
        {
            segment = path.substr(start, end - start); // Extract the next segment
        } else 
        {
            segment = path.substr(start); // If there's no '/', the rest of the path is the segment
        }
    } while (true);

    return node; // Return the node found at the end of the path
}

// Method to create a node given a path, creating intermediate nodes as necessary
Node* Tree::createNode(string path)
{
    int start = 0, end; // Initialize indices for parsing the path
    if (path[start] == '/') start++; // Skip the leading '/' if present

    end = path.find('/', start); // Find the first '/' to delimit the first segment
    string segment; // String to hold each path segment
    if (end != string::npos) {
        segment = path.substr(start, end - start); // Extract the segment from the path
    } else {
        segment = path.substr(start); // If there's no '/', the whole path is the segment
    }

    Node* node = root; // Start from the root node

    do {
        bool exists = false; // Flag to check if the segment exists among the node's children
        for (int i = 0; i < node->children.size(); ++i)
        { 
            if (node->children[i]->name == segment) 
            {
                node = node->children[i]; // If the segment matches a child, move to that child
                exists = true; // Mark as exists
                break; // Break the loop since the segment was found
            }
        }
        if (!exists) // If the segment is not found among children, create it
        {
            insert(node, segment); // Insert a new child node for the segment
            node = node->children[node->children.size()-1]; // Move to the newly created child
        }

        if (end == string::npos) break; // If there are no more segments, exit the loop

        // Prepare for the next segment
        start = end + 1; // Move start index past the '/'
        end = path.find('/', start); // Find the next '/'
        if (end != string::npos)
        {
            segment = path.substr(start, end - start); // Extract the next segment
        } else 
        {
            segment = path.substr(start); // If there's no '/', the rest of the path is the segment
        }
    } while (true);

    return node; // Return the node found or created at the end of the path
}

// Method to get a child node by name from a given parent node
Node* Tree::getChild(Node *ptr, string childname)
{
	Node* ch_ptr = nullptr; // Initialize a pointer to hold the found child
	for(int i = 0; i < ptr->children.size(); i++)
	{
		if(ptr->children[i]->name == childname) // Check if the child's name matches the given name
		{	
			ch_ptr = ptr->children[i]; // Set the pointer to the found child
			break; // Exit the loop since the child was found
		}
	}
	return ch_ptr; // Return the found child, or nullptr if not found
} 

// Method to update the book count of a node by a given offset
void Tree :: updateBookCount(Node *ptr, int offset)
{
	if (ptr != nullptr) // Ensure the node is not null
	{
		ptr->bookCount += offset; // Update the book count by the given offset
	} else throw runtime_error("couldn't update bookCount, category does not exist!");
}

// Method to find a book by title in a given node
Book* Tree :: findBook(Node *node, string bookTitle)
{
	Book* b_ptr = nullptr; // Initialize a pointer to hold the found book
	for (int i = 0; i < node->books.size(); ++i) // Iterate over the books in the node
	{
		if(node->books[i]->title == bookTitle) // Check if the book's title matches the given title
			{
				b_ptr = node->books[i]; // Set the pointer to the found book
				break; // Exit the loop since the book was found
			}
	}
	return b_ptr; // Return the found book, or nullptr if not found
}

// Method to remove a book by title from a given node
bool Tree::removeBook(Node* node, string bookTitle) {
    if (node == nullptr) return false; // If the node is null, indicate the book was not removed

    for (int i = 0; i < node->books.size(); ++i) { // Iterate over the books in the node
        if (node->books[i]->title == bookTitle) { // Check if the book's title matches the given title
            delete node->books[i]; // Free the memory allocated for the book
            node->books.erase(i); // Remove the book from the vector
            
            // Update the book count for the node and all its ancestors
            Node* current = node;
            while (current != nullptr) {
                current->bookCount--; // Decrement the book count
                current = current->parent; // Move to the parent node
            }

            return true; // Indicate the book was successfully removed
        }
    }
    return false; // Indicate the book was not found and therefore not removed
}

// Recursive method to print all books of a node and its children
void Tree :: printAll(Node *node)   
{ 
    // If the node is a leaf node (no children), print its books
	if (node->children.size() == 0)
	{
        // Iterate over the books and print their details
		for (int i = 0; i < node->books.size(); ++i)
		{
			cout << "Title: " << node->books[i]->title << endl;
			cout << "Author(s): " << node->books[i]->author << endl;
			cout << "ISBN: " << node->books[i]->isbn << endl;
			cout << "Year: " << node->books[i]->publication_year << endl;
			cout << "=====================================================================================================" << endl;
		}
	}
	else
	{
        // If the node has children, print its books and then recursively print the books of its children
		for (int i = 0; i < node->books.size(); ++i)
		{
			cout << "Title: " << node->books[i]->title << endl;
			cout << "Author(s): " << node->books[i]->author << endl;
			cout << "ISBN: " << node->books[i]->isbn << endl;
			cout << "Year: " << node->books[i]->publication_year << endl;
			cout << "=====================================================================================================" << endl;
		}
		for(int i = 0; i < node->children.size(); i++)
		{
			printAll(node->children[i]); // Recursively print the books of each child
		}

	}
}

// Method to check if a node is the last child of its parent
bool Tree :: isLastChild(Node *ptr)
{
    // Check if the node is not the root and is the last child in its parent's children vector
	if(ptr != root && ptr == ptr->parent->children[ptr->parent->children.size()-1])
        return true; // Return true if it is the last child
    return false; // Otherwise, return false
}

// Method to print the entire tree structure
void Tree :: print()
{
	print_helper("", "", root); // Start the recursive printing from the root node
}

// Recursive helper method for printing the tree structure
void Tree :: print_helper(string padding, string pointer, Node *node)
{
    if (node != nullptr) // Ensure the node is not null
    {
        cout << padding << pointer << node->name << "(" << node->bookCount << ")" << endl; // Print the current node

        if(node != root)	padding += (isLastChild(node)) ? "   " : "│  "; // Adjust the padding based on whether the node is the last child

        // Recursively print each child of the node
        for(int i = 0; i < node->children.size(); i++)	
        {
            string marker = isLastChild(node->children[i]) ? "└──" : "├──"; // Choose the correct marker based on whether the child is the last child
            print_helper(padding, marker, node->children[i]); // Recursively call the helper for each child
        }
    }
}

// Method to export all books of a given node to a specific file
int Tree::exportData(Node* node, ofstream& file) {
    if (!node) return 0; // If the node is null, return 0 indicating no books were exported

    string category = node->getCategory(node); // Get the category path for the node
    int count = 0; // Initialize a counter for the number of books exported

    // Iterate over the books in the node and export their details to the file
    for (int i = 0; i < node->books.size(); ++i) {
        // Output the title, handling commas by enclosing in quotes if necessary
        if (node->books[i]->title.find(',') != string::npos) {
            file << '"' << node->books[i]->title << '"' << ',';
        } else {
            file << node->books[i]->title << ',';
        }

        // Output the author, handling commas by enclosing in quotes if necessary
        if (node->books[i]->author.find(',') != string::npos) {
            file << '"' << node->books[i]->author << '"' << ',';
        } else {
            file << node->books[i]->author << ',';
        }

        file << node->books[i]->isbn << ','; // Output the ISBN
        file << to_string(node->books[i]->publication_year) << ',' << "," << category << ','; // Output the publication year and category
        file << to_string(node->books[i]->total_copies) << ','; // Output the total copies
        file << to_string(node->books[i]->available_copies) << endl; // Output the available copies and move to the next line

        count++; // Increment the counter for each book exported
    }

    return count; // Return the total number of books exported
}
