//============================================================================
// Name         : myvector.h
// Author       : Sebahadin Denur
// Version      : 1.0
// Date Created : 31/03/2024
// Date Modified:
// Description  : Vector implementation in C++
//============================================================================
#ifndef MYVECTOR_H
#define MYVECTOR_H
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include <stdexcept>
#include<sstream>

using namespace std;
template <typename T>
class MyVector
{
	private:
		T *data;						//pointer to int(array) to store elements
		int v_size;						//current size of vector (number of elements in vector)
		int v_capacity;					//capacity of vector
	public:
		MyVector();						//No argument constructor
		MyVector(int cap);				//One Argument Constructor
		MyVector(const MyVector& other);		//Copy Constructor
		~MyVector();					//Destructor
		void push_back(T element);		//Add an element at the end of vector
		void insert(int index, T element); //Add an element at the index 
		void erase(int index);			//Removes an element from the index
		T& operator[](int index);		//return reference of the element at index
		T& at(int index); 				//return reference of the element at index
		const T& front();				//Returns reference of the first element in the vector
		const T& back();				//Returns reference of the Last element in the vector
		int size() const;				//Return current size of vector
		int capacity() const;			//Return capacity of vector
		bool empty() const; 			//Return true if the vector is empty, False otherwise
		void shrink_to_fit();			//Reduce vector capacity to fit its size
};
//========================================

// Custom exception class for empty vector
class VectorEmpty : public exception
{
public:
    // Override what() method to return error message
    virtual const char * what() const throw()
    {
        return "Vector is empty"; // Return error message
    }
};

template <typename T>
MyVector<T>::MyVector()
{
    data = nullptr;
    this->v_capacity = 0;
    this->v_size = 0;
}
//========================================
template <typename T>
MyVector<T>::MyVector(int cap)
{
    this->v_capacity = cap;
    this->v_size = 0;
    data = new T[v_capacity];
}
//========================================
template <typename T>
MyVector<T>::MyVector(const MyVector &other)
{
    this->v_capacity = other.v_capacity;
    this->v_size = other.v_size;
    this->data = new T [v_capacity];
    for(int i=0; i<v_capacity; i++)
        this->data[i] = other.data[i];
}
//========================================
template <typename T>
MyVector<T>::~MyVector()
{
    delete [] this->data;
}
//========================================
template <typename T>
int MyVector<T>::size() const
{
    return v_size; // Return the size of the vector
}
//========================================
template <typename T>
int MyVector<T>::capacity() const
{
    return v_capacity; // Return the capacity of the vector
}
//========================================
template <typename T>
bool MyVector<T>::empty() const
{
    return v_size == 0; // Return true if vector is empty, false otherwise
}
//========================================
template <typename T>
void MyVector<T>::push_back(T element)
{
    if (v_size == v_capacity) // Check if vector is full
    {
        if (v_capacity == 0) // If capacity is 0
        {
            data = new T[1]; // Create a new element
            data[0] = element;
            v_size++; // Increment vector size
            v_capacity++; // Increment vector capacity
        }
        else // If capacity is not 0
        {
            T* temp = new T[v_capacity * 2]; // Create temporary array with doubled capacity
            
            for (int i = 0; i < v_size; i++) // Copy elements to temporary array
            {
                temp[i] = data[i];
            }
            
            delete [] data; // Deallocate memory for current array
            data = temp; // Update data pointer
            data[v_size] = element; // Add new element
            v_size++; // Increment vector size
            v_capacity = v_capacity * 2; // Double vector capacity
        }
    }
    else // If vector has space
    {
        data[v_size] = element; // Add element to vector
        v_size++; // Increment vector size
    }
}
//===============================================================================
template <typename T>	
void MyVector<T>::insert(int index,T element)
{
    if (index < 0 || index > v_size - 1) // Check if index is out of range
    {
        throw out_of_range("Vector index out of range"); // Throw exception if index is out of range
    }
    else
    {
        if (v_size == v_capacity) // Check if vector is full
        {
            T* temp = new T[v_capacity * 2]; // Create temporary array with doubled capacity
            
            for (int i = 0; i <= v_size; i++) // Copy elements to temporary array
            {
                if (index == i) // Insert element at specified index
                {
                    temp[i] = element;
                }
                else if (index > i) // Copy elements before index
                {
                    temp[i] = data[i];
                }
                else // Copy elements after index and shift right
                {
                    temp[i] = data[i - 1];
                }
            }
            
            delete [] data; // Deallocate memory for current array
            data = temp; // Update data pointer
            v_size++; // Increment vector size
            v_capacity = v_capacity * 2; // Double vector capacity
        }
        else // If vector has space
        {
            T temp = data[index]; // Store the element at the specified index
            data[index] = element; // Insert new element at specified index
            
            for(int i = index + 1 ; i <= v_size; i++) // Shift elements to the right
            {
                T temp2 = data[i];
                data[i] = temp;
                temp = temp2;
                
            }
            v_size++; // Increment vector size
        }
    }

}
//================================================================================
template <typename T>	
void MyVector<T>::erase(int index)
{
    if (index < 0 || index > v_size - 1) // Check if index is out of range
    {
        throw out_of_range("Vector index out of range"); // Throw exception if index is out of range
    }
    else
    {
        for (int i = index ; i < v_size - 1; i++) // Shift elements to the left
        {
            data[i] = data[i+1];
        }
        v_size--; // Decrement vector size
    }
}
//==================================================================================
template <typename T>
T& MyVector<T>::operator[](int index)
{
    return data[index]; // Return reference to element at index
}
//========================================
template <typename T>
T& MyVector<T>::at(int index)
{
    if (index < 0 || index > v_size - 1) // Check if index is out of range
    {
        throw out_of_range("Vector index out of range"); // Throw exception if index is out of range
    }
    else
    {
        return data[index]; // Return reference to element at index
    }
}
//========================================
template <typename T>
const T& MyVector<T>::front()
{
    if (empty()) // Check if the vector is empty
    {
        throw VectorEmpty(); // Throw exception if vector is empty
    }
    else
    {
        return data[0]; // Return reference to the first element
    }
}
//========================================
template <typename T>
const T& MyVector<T>::back()
{
    if (empty()) // Check if the vector is empty
    {
        throw VectorEmpty(); // Throw exception if vector is empty
    }
    else
    {
        return data[v_size-1]; // Return reference to the last element
    }
}
//======================================
template <typename T>
void MyVector<T>::shrink_to_fit()		//Reduce vector capacity to fit its size.
{
    if (v_capacity > v_size) // Check if capacity is greater than size
    {
        T* temp = new T[v_size]; // Create temporary array with size equal to vector size
        
        for(int i = 0 ; i < v_size; i++) // Copy elements to temporary array
        {
            temp[i] = data[i];
        }
        
        delete [] data; // Deallocate memory for current array
        data = temp; // Update data pointer
        v_capacity = v_size; // Set capacity equal to size
    }
}
#endif

