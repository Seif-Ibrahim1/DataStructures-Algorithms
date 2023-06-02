/*
    Author: Youssef Moataz
    Project: Double Linked List
    Description: Double linked list implementation

    Last Updated: 2/6/2023

    Github: YoussefMoataz

*/

#include <iostream>

using namespace std;

template<typename T>
struct DoubleNode {
    T value;
    DoubleNode *next;
    DoubleNode *previous;
};

template<typename T>
class DoubleLinkedList {

private:
    DoubleNode<T> *head;
    DoubleNode<T> *tail;
    int size = 0;

    void incrementSize() { size++; }

    void decrementSize() { size--; }

public:

    DoubleLinkedList() {

        head = NULL;
        tail = NULL;
        size = 0;

    }

    void insertAtHead(T element) {

        // create the node
        DoubleNode<T> *temp = new DoubleNode<T>;
        temp->value = element;
        temp->next = NULL;
        temp->previous = NULL;

        // check if list is empty
        if (head == NULL) {
            // set as the first element
            head = temp;
            tail = head;
        } else {

            head->previous = temp;
            temp->next = head;
            head = temp;

        }

        incrementSize();

    }

    void insertAtTail(T element) {

        // create the node
        DoubleNode<T> *temp = new DoubleNode<T>;
        temp->value = element;
        temp->next = NULL;
        temp->previous = NULL;

        DoubleNode<T> *current = head;

        // check if list is empty
        if (head == NULL) {
            // set as the first element
            head = temp;
            tail = head;
        } else {

            temp->previous = tail;
            tail->next = temp;
            tail = temp;

        }

        incrementSize();

    }

    void insertAt(T element, int index) {

        // create the node
        DoubleNode<T> *temp = new DoubleNode<T>;
        temp->value = element;
        temp->next = NULL;
        temp->previous = NULL;

        if (index == 0) {
            insertAtHead(element);
        } else if (index == size) {
            insertAtTail(element);
        } else {

            if (index > 0 && index < size) {

                DoubleNode<T> *current = head;
                int counter = 0;

                while (counter < index) {
                    current = current->next;
                    counter++;
                }

                current->previous->next = temp;
                temp->previous = current->previous;
                temp->next = current;
                current->previous = temp;

                incrementSize();

            }

        }

    }

    void insertAfter(T prev_node, T element) {

        DoubleNode<T> *current = head;

        DoubleNode<T> *temp = new DoubleNode<T>;
        temp->value = element;
        temp->next = NULL;
        temp->previous = NULL;

        if (head == NULL) {

            insertAtHead(element);

        } else {

            if (!isExist(prev_node)) {
                return;
            }

            while (current->value != prev_node) {

                current = current->next;

            }

            current->next->previous = temp;
            temp->next = current->next;
            temp->previous = current;
            current->next = temp;

            incrementSize();

        }

    }

    void removeAtHead() {

        DoubleNode<T> *temp = head;

        if (head == tail) {
            head = tail = NULL;
            return;
        }

        if (head != NULL) {

            if (head->next != NULL) {
                head->next->previous = NULL;
                head = head->next;

                free(temp);
                decrementSize();

            }

        }

    }

    void removeAtTail() {

        DoubleNode<T> *temp = tail;

        if (head == tail) {
            head = tail = NULL;
            return;
        }

        if (tail != NULL) {

            if (tail->previous != NULL) {
                tail->previous->next = NULL;
                tail = tail->previous;

                free(temp);
                decrementSize();
            }

        }

    }

    void removeAt(int index) {

        if (index == 0) {
            removeAtHead();
        } else if (index == size - 1) {
            removeAtTail();
        } else {

            if (index > 0 && index < size) {

                DoubleNode<T> *temp;
                DoubleNode<T> *current = head;
                int counter = 0;

                while (counter < index) {

                    current = current->next;
                    counter++;

                }

                temp = current;
                current->next->previous = current->previous;
                current->previous->next = current->next;

                free(temp);
                decrementSize();

            }

        }

    }

    T retrieveAt(int index) {

        if (index >= 0 && index < size) {

            DoubleNode<T> *current = head;
            int counter = 0;

            while (counter < index) {

                current = current->next;
                counter++;

            }

            return current->value;

        } else {

            return NULL;

        }

    }

    void replaceAt(T newElement, int index) {

        if (index >= 0 && index < size) {

            DoubleNode<T> *current = head;
            int counter = 0;

            while (counter < index) {

                current = current->next;
                counter++;

            }

            current->value = newElement;

        }

    }

    bool isExist(T element) {

        DoubleNode<T> *current = head;

        // loop till out of the list
        while (current != NULL) {

            if (current->value == element) {
                return true;
            }

            // go to next node
            current = current->next;
        }

        return false;

    }

    bool isItemAtEqual(T element, int index) {

        return element == retrieveAt(index);

    }

    void swap(int firstItemIdx, int secondItemIdx) {

        int firstItemIndex, secondItemIndex;

        if (firstItemIdx >= 0 && secondItemIdx < size) {

            if (firstItemIdx < secondItemIdx) {
                firstItemIndex = firstItemIdx;
                secondItemIndex = secondItemIdx;
            } else {
                firstItemIndex = secondItemIdx;
                secondItemIndex = firstItemIdx;
            }

            DoubleNode<T> *firstItem = head;
            DoubleNode<T> *secondItem = head;

            DoubleNode<T> *firstItemPrevious = NULL;
            DoubleNode<T> *firstItemNext = NULL;
            DoubleNode<T> *secondItemPrevious = NULL;
            DoubleNode<T> *secondItemNext = NULL;

            // get first node
            for (int i = 0; i < firstItemIndex; ++i) {

                firstItem = firstItem->next;

            }
            firstItemPrevious = firstItem->previous;
            firstItemNext = firstItem->next;

            // get second node
            for (int i = 0; i < secondItemIndex; ++i) {

                secondItem = secondItem->next;

            }
            secondItemPrevious = secondItem->previous;
            secondItemNext = secondItem->next;

            if (firstItemIndex != 0) {
                // attach the new node to its previous except for head
                firstItemPrevious->next = secondItem;
            }

            // attach the new first node to the list
            firstItemNext->previous = secondItem;

            // attach the new second node to the list
            secondItemPrevious->next = firstItem;

            if (secondItemIndex != (size - 1)) {
                // attach the new node to its next except for tail
                secondItemNext->previous = firstItem;
            }

            if (secondItemIndex - firstItemIndex != 1) {
                // swap non-consecutive nodes

                // place the new first node in the new position
                firstItem->previous = secondItemPrevious;
                firstItem->next = secondItemNext;

                // place the new second node in the new position
                secondItem->previous = firstItemPrevious;
                secondItem->next = firstItemNext;
            } else {
                // swap consecutive nodes

                // place the new first node in the new position
                firstItem->previous = secondItem;
                firstItem->next = secondItemNext;

                // place the new second node in the new position
                secondItem->previous = firstItemPrevious;
                secondItem->next = firstItem;
            }

            // assign the new head
            if (firstItemIndex == 0) {
                head = secondItem;
            }

            // assign the new tail
            if (secondItemIndex == (size - 1)) {
                tail = firstItem;
            }

        }

    }

    void reverse() {

        DoubleNode<T> *current = head;
        DoubleNode<T> *temp;

        while (current != NULL) {

            temp = current->previous;
            current->previous = current->next;
            current->next = temp;
            current = current->previous;

        }

        tail = head;
        head = temp->previous;

    }

    bool isEmpty() {

        return size == 0;

    }

    int doubleLinkedListSize() {

        return size;

    }

    void clear() {

        DoubleNode<T> *previous;

        while (head != NULL) {

            previous = head;
            head = head->next;

            free(previous);

        }

        size = 0;

    }

    void forwardTraversal() {

        DoubleNode<T> *current = head;

        // loop till out of the list
        while (current != NULL) {
            // print the value of the current node
            cout << current->value << " ";
            // go to next node
            current = current->next;
        }

        cout << endl;

    }

    void backwardTraversal() {

        DoubleNode<T> *current = tail;

        // loop till out of the list
        while (current != NULL) {
            // print the value of the current node
            cout << current->value << " ";
            // go to next node
            current = current->previous;
        }

        cout << endl;

    }

};
