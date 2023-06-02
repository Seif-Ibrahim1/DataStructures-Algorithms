/*
    Author: Seif Ibrahim
    Project: Queue
    Description: Queue Data Strcture implementation using Linked List

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
class Queue {
    SingleLinkedList<T>* list; // Singly linked list to store the queue elements

public:
    // Constructor for the Queue class
    Queue() {
        list = new SingleLinkedList<T>();
    }

    // Public function to get the size of the queue
    int queueSize() {
        return list->listSize();
    }

    // Public function to check if the queue is empty
    bool isEmpty() {
        return list->isEmpty();
    }

    // Public function to enqueue an element at the rear of the queue
    void enqueue(T element) {
        list->insertAt(element, list->listSize());
    }

    // Public function to dequeue an element from the front of the queue
    T dequeue() {
        if (!isEmpty()) {
            T dequeued = list->retrieveAt(0);
            list->removeAtHead();
            return dequeued;
        }

        throw OutOfRange(); // Throw an exception if the queue is empty
    }

    // Public function to peek at the front element of the queue
    T peek() {
        if (!isEmpty()) {
            return list->retrieveAt(0);
        }

        throw OutOfRange(); // Throw an exception if the queue is empty
    }

    // Public function to clear the queue
    void clear() {
        list->clear();
    }

    // Public function to print the elements of the queue
    void print() {
        list->print();
    }
};

int main() {
    Queue<int> myQueue;

    // Test case 1: Enqueue elements
    myQueue.enqueue(5);
    myQueue.enqueue(10);
    myQueue.enqueue(15);

    // Test case 2: Check queue size
    assert(myQueue.queueSize() == 3);

    // Test case 3: Dequeue elements
    int dequeued = myQueue.dequeue();
    assert(dequeued == 5);
    assert(myQueue.queueSize() == 2);

    // Test case 4: Peek at the front element
    int frontElement = myQueue.peek();
    assert(frontElement == 10);

    // Test case 5: Clear the queue
    myQueue.clear();
    assert(myQueue.queueSize() == 0);
    assert(myQueue.isEmpty());

    std::cout << "All test cases passed!" << std::endl;

    return 0;
}
