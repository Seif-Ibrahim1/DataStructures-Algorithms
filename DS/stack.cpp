/*
    Author: Seif Ibrahim
    Project: Stack 
    Description: Stack Data Strcture implementation using Linked List

    Last Updated: 2/6/2023

    Github: Seif-Ibrahim1

*/

#include <iostream>
#include <exception>
#include <cassert>
#include "singleLinkedList.cpp"
using namespace std;

// // Custom exception class for out-of-range errors
// class OutOfRange : public exception {
// public:
//     const char* what() {
//         return "Out Of Range";
//     }
// };

template <class T>
class Stack {
private:
    SingleLinkedList<T>* list; // Singly linked list to store the stack elements

public:
    // Constructor for the Stack class
    Stack() {
        list = new SingleLinkedList<T>;
    }

    // Public function to get the size of the stack
    int stackSize() {
        return list->listSize();
    }

    // Public function to check if the stack is empty
    bool isEmpty() {
        return list->isEmpty();
    }

    // Public function to push an element onto the stack
    void push(T element) {
        list->insertAtHead(element);
    }

    // Public function to pop an element from the top of the stack
    T pop() {
        if (!isEmpty()) {
            T popped = list->retrieveAt(0);
            list->removeAtHead();
            return popped;
        }

        throw OutOfRange(); // Throw an exception if the stack is empty
    }

    // Public function to peek at the top element of the stack
    T peek() {
        if (!isEmpty()) {
            return list->retrieveAt(0);
        }

        throw OutOfRange(); // Throw an exception if the stack is empty
    }

    // Public function to clear the stack
    void clear() {
        list->clear();
    }

    // Public function to print the elements of the stack
    void print() {
        list->print();
    }
};

int main() {
    Stack<int> myStack;

    // Test case 1: Push elements onto the stack
    myStack.push(5);
    myStack.push(10);
    myStack.push(15);

    // Test case 2: Check stack size
    assert(myStack.stackSize() == 3);

    // Test case 3: Pop elements from the stack
    int popped = myStack.pop();
    assert(popped == 15);
    assert(myStack.stackSize() == 2);

    // Test case 4: Peek at the top element
    int topElement = myStack.peek();
    assert(topElement == 10);

    // Test case 5: Clear the stack
    myStack.clear();
    assert(myStack.stackSize() == 0);
    assert(myStack.isEmpty());

    std::cout << "All test cases passed!" << std::endl;

    return 0;
}
