/*
    Author: Seif Ibrahim
    Project: SLL
    Description: Single Linked List Data Strcture implementation

    Last Updated: 2/6/2023

    Github: Seif-Ibrahim1

*/

#include <iostream>
#include <exception>
#include <cassert>
using namespace std;

// Custom exception class for out-of-range errors
class OutOfRange : public exception {
public:
    const char* what() {
        return "Out Of Range";
    }
};

// Node structure for the singly linked list
template <class T>
struct Node {
    T value;
    Node* next;
};

// Class for the singly linked list
template <class T>
class SingleLinkedList {
    Node<T>* head; // Pointer to the head of the list
    int size = 0; // Size of the list

public:
    // Constructor for the SingleLinkedList class
    SingleLinkedList() {
        head = nullptr;
    }

    // Insert an element at the head of the list
    void insertAtHead(T elem) {
        Node<T>* current = new Node<T>();
        current->value = elem;
        current->next = head;
        head = current;
        size++;
    }

    // Insert an element at a specific index in the list
    void insertAt(T element, int index) {
        if (index > size || index < 0) {
            throw OutOfRange();
        }
        
        if (index == 0) {
            insertAtHead(element);
        }
        else if (index == size) {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            Node<T>* tmp = new Node<T>();
            tmp->next = nullptr;
            tmp->value = element;
            current->next = tmp;
            size++;
        }
        else {
            Node<T>* current = head->next;
            Node<T>* trailCurrent = head;
            int counter = 1;
            while (current != nullptr) {
                if (counter == index) {
                    Node<T>* tmp = new Node<T>();
                    tmp->next = current;
                    tmp->value = element;
                    trailCurrent->next = tmp;
                    size++;
                    break;
                }
                current = current->next;
                trailCurrent = trailCurrent->next;
                counter++;
            }
        }
    }

    // Remove the element at the head of the list
    void removeAtHead() {
        if (size == 0) {
            throw OutOfRange();
        }

        Node<T>* current = head;
        head = head->next;
        delete current;
        size--;
    }

    // Remove the element at a specific index in the list
    void removeAt(int index) {
        if (index >= size || index < 0) {
            throw OutOfRange();
        }

        if (index == 0) {
            removeAtHead();
        }
        else {
            Node<T>* current = head->next;
            Node<T>* trailCurrent = head;
            int counter = 1;
            while (current != nullptr) {
                if (counter == index) {
                    trailCurrent->next = current->next;
                    delete current;
                    size--;
                    break;
                }
                current = current->next;
                trailCurrent = trailCurrent->next;
                counter++;
            }
        }
    }

    // Retrieve the element at a specific index in the list
    T retrieveAt(int index) {
        if (index >= size || index < 0) {
            throw OutOfRange();
        }

        Node<T>* current = head;
        int counter = 0;
        while (current != nullptr) {
            if (counter == index) {
                return current->value;
            }
            current = current->next;
            counter++;
        }
    }

    // Replace the element at a specific index in the list with a new element
    void replaceAt(T newElement, int index) {
        if (index >= size || index < 0) {
            throw OutOfRange();
        }

        Node<T>* current = head;
        int counter = 0;
        while (current != nullptr) {
            if (counter == index) {
                current->value = newElement;
                break;
            }
            current = current->next;
            counter++;
        }
    }

    // Check if an element exists in the list
    bool isExist(T element) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->value == element) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Check if the element at a specific index is equal to a given element
    bool isItemAtEqual(T element, int index) {
        if (index >= size || index < 0) {
            throw OutOfRange();
        }

        Node<T>* current = head;
        int counter = 0;
        while (current != nullptr) {
            if (counter == index) {
                return current->value == element;
            }
            current = current->next;
            counter++;
        }
    }

    // Swap two nodes in the list without swapping data
    void swap(int firstItemIdx, int secondItemIdx) {
        if (firstItemIdx >= size || firstItemIdx < 0 || secondItemIdx >= size || secondItemIdx < 0) {
            throw OutOfRange();
        }

        if (firstItemIdx > secondItemIdx) {
            swap(secondItemIdx, firstItemIdx);
            return;
        }

        if (firstItemIdx == secondItemIdx) {
            return;
        }

        Node<T>* firstIter = head;
        Node<T>* firstIterTrail = head;
        int counter = 0;
        while (firstIter != nullptr) {
            if (counter == firstItemIdx) {
                break;
            }
            firstIter = firstIter->next;
            firstIterTrail = firstIterTrail->next;
            counter++;
        }

        counter++;
        Node<T>* secondIter = firstIter->next;
        Node<T>* secondIterTrail = firstIter;

        while (secondIter != nullptr) {
            if (counter == secondItemIdx) {
                break;
            }
            secondIter = secondIter->next;
            secondIterTrail = secondIterTrail->next;
            counter++;
        }

        Node<T>* tmp = firstIter->next;
        firstIter->next = secondIter->next;
        secondIter->next = tmp;

        if (firstIter != head) {
            firstIterTrail->next = secondIter;
        }
        else {
            head = secondIter;
        }
        secondIterTrail->next = firstIter;
    }

    // Reverse the elements in the list
    void reverse() {
        Node<T>* current = head->next;
        Node<T>* trailCurrent = head;
        Node<T>* tmp = head->next;
        trailCurrent->next = nullptr;
        while (tmp != nullptr) {
            tmp = current->next;
            current->next = trailCurrent;
            trailCurrent = current;
            current = tmp;
        }
        head = trailCurrent;
    }

    // Check if the list is empty
    bool isEmpty() {
        return (size == 0);
    }

    // Get the size of the list
    int listSize() {
        return size;
    }

    // Clear the list and free memory
    void clear() {
        Node<T>* current = head->next;
        Node<T>* trailCurrent = head;
        while (current != nullptr) {
            delete trailCurrent;
            trailCurrent = current;
            current = current->next;
        }
        delete trailCurrent;
        size = 0;
    }

    // Print the elements in the list
    void print() {
        Node<T>* current = head;
        while (current != nullptr) {
            cout << current->value << endl;
            current = current->next;
        }
    }
};


// int main() {
//     SingleLinkedList<int> myList;

//     // Test case 1: Inserting elements
//     myList.insertAtHead(5);
//     myList.insertAtHead(10);
//     myList.insertAt(15, 1);
//     assert(myList.listSize() == 3);

//     // Test case 2: Retrieving elements
//     assert(myList.retrieveAt(0) == 10);
//     assert(myList.retrieveAt(1) == 15);
//     assert(myList.retrieveAt(2) == 5);

//     // Test case 3: Removing elements
//     myList.removeAtHead();
//     assert(myList.listSize() == 2);
//     assert(myList.retrieveAt(0) == 15);

//     myList.removeAt(1);
//     assert(myList.listSize() == 1);
//     assert(myList.retrieveAt(0) == 15);

//     // Test case 4: Replacing elements
//     myList.replaceAt(20, 0);
//     assert(myList.retrieveAt(0) == 20);

//     // Test case 5: Checking existence of elements
//     assert(myList.isExist(20));
//     assert(!myList.isExist(15));

//     // Test case 6: Checking equality of elements at a specific index
//     assert(myList.isItemAtEqual(20, 0));
//     assert(!myList.isItemAtEqual(15, 0));

//     // Test case 7: Swapping elements
//     myList.insertAtHead(25);
//     myList.insertAtHead(30);
//     myList.swap(0, 2);
//     assert(myList.retrieveAt(0) == 20);
//     assert(myList.retrieveAt(1) == 25);
//     assert(myList.retrieveAt(2) == 30);

//     // Test case 8: Reversing the list
//     myList.reverse();
//     assert(myList.retrieveAt(0) == 30);
//     assert(myList.retrieveAt(1) == 25);
//     assert(myList.retrieveAt(2) == 20);

//     // Test case 9: Checking if the list is empty
//     assert(!myList.isEmpty());
//     myList.clear();
//     assert(myList.isEmpty());

//     std::cout << "All test cases passed!" << std::endl;

//     return 0;
// }
