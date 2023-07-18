/*
    Author: Seif Ibrahim
    Description: indexed Priority Queue Data Strcture implementation

    Last Updated: 18/7/2023

    Github: Seif-Ibrahim1

*/


#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
class indexedPriorityQueue {
    int _size = 0;          // Current size of the indexed priority queue
    int capacity;           // Capacity of the indexed priority queue
    int degree = 2;         // Degree of each node in the heap
    int* child;             // Array storing the indices of child nodes
    int* parent;            // Array storing the indices of parent nodes
    int* posMap;            // Mapping from key index to position in the heap
    int* inVMap;            // Mapping from position in the heap to key index
    T* values;              // Array storing the values associated with key indices

    // Function to sink the element at index i in the heap
    void sink(int i) {
        for (int j = minChild(i); j != -1;) {
            _swap(i, j);
            i = j;
            j = minChild(i);
        }
    }

    // Function to swim the element at index i in the heap
    void swim(int i) {
        while (values[inVMap[i]] < values[inVMap[parent[i]]]) {
            _swap(i, parent[i]);
            i = parent[i];
        }
    }

    // Function to find the minimum child index of the element at index i in the heap
    int minChild(int i) {
        int index = -1;
        for (int j = child[i]; j < min(_size, child[i] + degree); j++) {
            if (values[inVMap[j]] < values[inVMap[i]]) {
                index = i = j;
            }
        }

        return index;
    }

    // Function to swap the elements at indices i and j in the heap
    void _swap(int i, int j) {
        posMap[inVMap[i]] = j;
        posMap[inVMap[j]] = i;
        swap(inVMap[i], inVMap[j]);
    }

public:
    // Constructor to initialize the indexed priority queue with a given capacity
    indexedPriorityQueue(int _capacity) {
        capacity = _capacity;
        if (capacity < 3) {
            capacity = 3;
        }

        child = new int[capacity];
        parent = new int[capacity];
        posMap = new int[capacity];
        inVMap = new int[capacity];
        values = new T[capacity];

        for (int i = 0; i < capacity; i++) {
            parent[i] = (i - 1) / degree;
            child[i] = i * degree + 1;
            posMap[i] = inVMap[i] = -1;
        }
    }

    // Destructor to deallocate memory
    ~indexedPriorityQueue() {
        delete[] child;
        delete[] parent;
        delete[] posMap;
        delete[] inVMap;
        delete[] values;
    }

    // Function to get the current size of the indexed priority queue
    int size() {
        return _size;
    }

    // Function to check if the indexed priority queue is empty
    int isEmpty() {
        return _size == 0;
    }

    // Function to check if the indexed priority queue contains a key index
    bool contains(int keyIndex) {
        return posMap[keyIndex] != -1;
    }

    // Function to get the key index with the minimum value
    int peekMinKeyIndex() {
        return inVMap[0];
    }

    // Function to remove and return the key index with the minimum value
    int pollMinKeyIndex() {
        int minKeyIndex = peekMinKeyIndex();
        remove(minKeyIndex);
        return minKeyIndex;
    }

    // Function to get the minimum value
    int peekMinvalue() {
        return values[inVMap[0]];
    }

    // Function to remove and return the minimum value
    T pollMinvalue() {
        T minvalue = peekMinvalue();
        remove(peekMinKeyIndex());
        return minvalue;
    }

    // Function to insert a key index with a value into the indexed priority queue
    void insert(int keyIndex, T value) {
        if (!contains(keyIndex)) {
            posMap[keyIndex] = _size;
            inVMap[_size] = keyIndex;
            values[keyIndex] = value;
            swim(_size++);
        } else {
            throw invalid_argument("Key already exists");
        }
    }

    // Function to get the value associated with a key index
    T valueOf(int keyIndex) {
        return values[keyIndex];
    }

    // Function to remove a key index from the indexed priority queue and return its value
    T remove(int keyIndex) {
        if (contains(keyIndex)) {
            int i = posMap[keyIndex];
            _swap(i, --_size);
            sink(i);
            swim(i);
            T value = values[keyIndex];
            posMap[keyIndex] = -1;
            inVMap[keyIndex] = -1;

            return value;
        }

        throw out_of_range("Key not found");
    }

    // Function to update the value associated with a key index and return its previous value
    T update(int keyIndex, T value) {
        if (contains(keyIndex)) {
            int i = posMap[keyIndex];
            T oldValue = values[keyIndex];
            values[keyIndex] = value;
            sink(i);
            swim(i);

            return oldValue;
        } else {
            throw out_of_range("Key not found");
        }
    }

    // Function to decrease the value associated with a key index
    void decrease(int keyIndex, T value) {
        if (value < values[keyIndex]) {
            values[keyIndex] = value;
            swim(posMap[keyIndex]);
        }
    }

    // Function to increase the value associated with a key index
    void increase(int keyIndex, T value) {
        if (values[keyIndex] < value) {
            values[keyIndex] = value;
            sink(posMap[keyIndex]);
        }
    }
};

int main() {
    // Test case 1
    indexedPriorityQueue<int> pq1(5);
    pq1.insert(0, 5);
    pq1.insert(1, 2);
    pq1.insert(2, 7);
    assert(pq1.size() == 3);

    // Test case 2
    indexedPriorityQueue<int> pq2(5);
    assert(pq2.isEmpty() == true);
    pq2.insert(0, 5);
    assert(pq2.isEmpty() == false);

    // Test case 3
    indexedPriorityQueue<int> pq3(5);
    pq3.insert(0, 5);
    pq3.insert(1, 2);
    assert(pq3.contains(0) == true);
    assert(pq3.contains(2) == false);

    // Test case 4
    indexedPriorityQueue<int> pq4(5);
    pq4.insert(0, 5);
    pq4.insert(1, 2);
    pq4.insert(2, 7);
    assert(pq4.peekMinKeyIndex() == 1);
    assert(pq4.peekMinvalue() == 2);

    // Test case 5
    indexedPriorityQueue<int> pq5(5);
    pq5.insert(0, 5);
    pq5.insert(1, 2);
    pq5.insert(2, 7);
    int minKeyIndex = pq5.pollMinKeyIndex();
    assert(minKeyIndex == 1);
    assert(pq5.peekMinKeyIndex() == 0);

    // Test case 6
    indexedPriorityQueue<int> pq6(5);
    pq6.insert(0, 5);
    pq6.insert(1, 2);
    pq6.insert(2, 7);
    int minValue = pq6.pollMinvalue();
    assert(minValue == 2);
    assert(pq6.peekMinvalue() == 5);

    // Test case 7
    indexedPriorityQueue<int> pq7(5);
    pq7.insert(0, 5);
    pq7.insert(1, 2);
    pq7.insert(2, 7);
    int oldValue = pq7.update(1, 3);
    assert(oldValue == 2);
    assert(pq7.peekMinvalue() == 3);

    cout << "All test cases passed!" << endl;

    return 0;
}