/*
    Author: Seif Ibrahim
    Project: Min Heap
    Description: Min Heap Data Strcture implementation

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

template <class T>
class MinHeap {
    T* heap; // Dynamic array to store the heap elements
    int size; // Current number of elements in the heap
    int cap; // Current capacity of the heap

    // Private helper function to resize the heap
    void resize() {
        cap *= 2;
        T* newHeap = new T[cap];
        for (int i = 0; i < size; i++) {
            newHeap[i] = heap[i];
        }
        delete[] heap;
        heap = new T[cap];
        for (int i = 0; i < size; i++) {
            heap[i] = newHeap[i];
        }
        delete[] newHeap;
    }

    // Private helper function to remove an element at the given index
    void removeAt(int index) {
        // Swap the element to be removed with the last element
        swap(heap[index], heap[--size]);
        T changed = heap[index];

        // Restore heap property by performing top-down and bottom-up heapify
        heapifyTopDown(index);

        if (changed == heap[index]) {
            heapifyBottomUp(index);
        }
    }

    // Private helper function to find the index of an element in the heap
    int _contains(int element) {
        for (int i = 0; i < size; i++) {
            if (heap[i] == element) {
                return i;
            }
        }
        return -1;
    }

public:
    // Constructor for the MinHeap class
    MinHeap(int newCap = 2) {
        cap = newCap;
        size = 0;
        heap = new T[cap];
    }

    // Private helper function to restore heap property from bottom to top
    void heapifyBottomUp(int index) {
        int parent = (index - 1) / 2;

        // Swap the element with its parent if it violates the heap property
        if (parent >= 0 && heap[parent] > heap[index]) {
            swap(heap[parent], heap[index]);
            heapifyBottomUp(parent);
        }
    }

    // Private helper function to restore heap property from top to bottom
    void heapifyTopDown(int index) {
        int l = (2 * index) + 1;
        int r = (2 * index) + 2;

        int min = index;

        // Find the smallest element among the current node and its children
        if (l < size && heap[min] > heap[l]) {
            min = l;
        }

        if (r < size && heap[min] > heap[r]) {
            min = r;
        }

        // Swap the element with the smallest child if it violates the heap property
        if (min != index) {
            swap(heap[min], heap[index]);
            heapifyTopDown(min);
        }
    }

    // Public function to add an element to the heap
    void add(T element) {
        if (size >= cap) {
            resize();
        }

        heap[size] = element;

        // Restore heap property by performing bottom-up heapify
        heapifyBottomUp(size);
        size++;
    }

    // Public function to remove an element from the heap
    void remove(T element) {
        int index = _contains(element);

        if (index != -1) {
            removeAt(index);
        } else {
            throw OutOfRange(); // Throw an exception if the element is not found
        }
    }

    // Public function to get the minimum element (top of the heap)
    T peek() {
        return heap[0];
    }

    // Public function to extract the minimum element from the heap
    T extractMin() {
        T min = peek();
        removeAt(0);
        return min;
    }

    // Public function to get the size of the heap
    int heapSize() {
        return size;
    }

    // Public function to check if the heap contains an element
    bool contains(int element) {
        return (_contains(element) != -1);
    }

    // Public function to check if the heap is empty
    bool isEmpty() {
        return (size == 0);
    }

    // Public function to clear the heap
    void clear() {
        delete[] heap;
        size = 0;
    }
};

int main() {
    MinHeap<int> myHeap;

    // Test case 1: Add elements to the heap
    myHeap.add(10);
    myHeap.add(5);
    myHeap.add(15);

    // Test case 2: Peek at the minimum element
    assert(myHeap.peek() == 5);

    // Test case 3: Extract the minimum element
    int minElement = myHeap.extractMin();
    assert(minElement == 5);

    // Test case 4: Remove an element from the heap
    myHeap.add(20);
    myHeap.add(10);
    myHeap.remove(10);
    assert(myHeap.peek() == 10);

    // Test case 5: Check heap size
    assert(myHeap.heapSize() == 3);

    // Test case 6: Check if the heap contains an element
    assert(myHeap.contains(20));
    assert(!myHeap.contains(5));

    // Test case 7: Check if the heap is empty
    assert(!myHeap.isEmpty());

    // Test case 8: Clear the heap
    myHeap.clear();
    assert(myHeap.isEmpty());

    std::cout << "All test cases passed!" << std::endl;

    return 0;
}
