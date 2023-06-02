/*
    Author: Seif Ibrahim, Ahmed Hanafy
    Project: Min Heap
    Description: Min Heap Data Strcture implementation

    Last Updated: 2/6/2023

    Github: Seif-Ibrahim1, ahanfybekheet

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

//----------------------------------------------------------------
//----------------------Heap as functions-------------------------
//----------------------------------------------------------------
/**
 * Performs the Max-Heapify operation on the given array at the specified index.
 * It assumes that the binary trees rooted at the left and right children of index are max-heaps,
 * but array[index] might be smaller than its children, violating the max-heap property.
 * This function corrects the violation by recursively swapping elements until the max-heap property is restored.
 *
 * @param array The array to perform Max-Heapify on.
 * @param index The index at which Max-Heapify operation needs to be performed.
 * @param size The size of the array.
 * @tparam T The type of elements in the array.
 */
template<typename T>
void MAX_HEAPIFY(T *array, int index, int size) {
    int leftOfIndex = 2 * index + 1;
    int rightOfIndex = 2 * index + 2;
    int largest = index;

    // Compare the element at index with its left child
    if (leftOfIndex < size && array[leftOfIndex] > array[largest]) {
        largest = leftOfIndex;
    }

    // Compare the element at index with its right child
    if (rightOfIndex < size && array[rightOfIndex] > array[largest]) {
        largest = rightOfIndex;
    }

    // If the largest element is not the current index, swap the elements and recursively perform Max-Heapify
    if (largest != index) {
        std::swap(array[index], array[largest]);
        MAX_HEAPIFY(array, largest, size);
    }
}

/**
 * Builds a max-heap from the given array by repeatedly calling MAX_HEAPIFY on non-leaf nodes in reverse order.
 *
 * @param array The array to build a max-heap from.
 * @param size The size of the array.
 * @tparam T The type of elements in the array.
 */
template<typename T>
void BUILD_MAX_HEAP(T *array, int size) {
    // Start from the last non-leaf node and perform Max-Heapify on each node in reverse order
    for (int i = size / 2 - 1; i >= 0; i--) {
        MAX_HEAPIFY(array, i, size);
    }
}

/**
 * Sorts the given array in ascending order using the Heap Sort algorithm.
 *
 * @param array The array to be sorted.
 * @param size The size of the array.
 * @tparam T The type of elements in the array.
 */
template<typename T>
void HEAP_SORT(T *array, int size) {
    BUILD_MAX_HEAP(array, size);

    // Extract the maximum element from the heap and place it at the end of the array
    for (int i = size - 1; i > 0; i--) {
        std::swap(array[0], array[i]);
        MAX_HEAPIFY(array, 0, i);
    }
}

/**
 * Returns the maximum element from the heap (the first element in the array).
 *
 * @param array The array representing the heap.
 * @tparam T The type of elements in the array.
 * @return The maximum element from the heap.
 */
template<typename T>
T HEAP_MAXIMUM(T *array) {
    return array[0];
}

/**
 * Extracts the maximum element from the heap and updates the heap size.
 *
 * @param array The array representing the heap.
 * @param size The current size of the heap.
 * @tparam T The type of elements in the array.
 */
template<typename T>
void HEAP_EXTRACT_MAX(T *array, int& size) {
    if (size <= 0) {
        return; // Heap is empty
    }

    // Replace the maximum element with the last element, remove the last element, and perform Max-Heapify
    std::swap(array[0], array[size - 1]);
    array[size - 1] = T();
    size--;
    MAX_HEAPIFY(array, 0, size);
}

/**
 * Prints the elements of the array.
 *
 * @param array The array to be printed.
 * @param size The size of the array.
 * @tparam T The type of elements in the array.
 */
template<typename T>
void printArray(T *array, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * Changes the value of an element at the specified index in the heap and maintains the max-heap property.
 *
 * @param array The array representing the heap.
 * @param keyIndex The index of the element to be changed.
 * @param newValue The new value to be assigned to the element.
 * @tparam T The type of elements in the array.
 */
template<typename T>
void HEAP_CHANGE_KEY(T *array, int keyIndex, T newValue) {
    array[keyIndex] = newValue;
    int parentIndex = (keyIndex - 1) / 2;

    // Swap the element with its parent as long as it is greater, and update indices
    while (keyIndex > 0 && array[parentIndex] < array[keyIndex]) {
        std::swap(array[keyIndex], array[parentIndex]);
        keyIndex = parentIndex;
        parentIndex = (keyIndex - 1) / 2;
    }
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------





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
//----------------------------------------------------------------
//              Test Cases For MAX HEAP FUNCTIONS
//----------------------------------------------------------------
    int array1[] = { 4, 10, 3, 5, 1 };
    int size1 = sizeof(array1) / sizeof(array1[0]);

    std::cout << "Original array: ";
    printArray(array1, size1);

    // Testing MAX_HEAPIFY
    MAX_HEAPIFY(array1, 0, size1);
    std::cout << "MAX_HEAPIFY result: ";
    printArray(array1, size1);

    int array2[] = { 3, 7, 2, 5, 1, 8, 6, 4 };
    int size2 = sizeof(array2) / sizeof(array2[0]);

    std::cout << "\nOriginal array: ";
    printArray(array2, size2);

    // Testing BUILD_MAX_HEAP
    BUILD_MAX_HEAP(array2, size2);
    std::cout << "BUILD_MAX_HEAP result: ";
    printArray(array2, size2);

    // Testing HEAP_SORT
    HEAP_SORT(array2, size2);
    std::cout << "HEAP_SORT result: ";
    printArray(array2, size2);

    int array3[] = { 9, 6, 8, 2, 4 };
    int size3 = sizeof(array3) / sizeof(array3[0]);

    std::cout << "\nOriginal array: ";
    printArray(array3, size3);

    // Testing HEAP_MAXIMUM
    int maxElement = HEAP_MAXIMUM(array3);
    std::cout << "HEAP_MAXIMUM: " << maxElement << std::endl;

    // Testing HEAP_EXTRACT_MAX
    HEAP_EXTRACT_MAX(array3, size3);
    std::cout << "HEAP_EXTRACT_MAX result: ";
    printArray(array3, size3);

    // Testing HEAP_CHANGE_KEY
    HEAP_CHANGE_KEY(array3, 2, 10);
    std::cout << "HEAP_CHANGE_KEY result: ";
    printArray(array3, size3);
    return 0;
}

