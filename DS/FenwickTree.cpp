/*
    Author: Seif Ibrahim
    Description: Suffix Array Data Strcture implementation

    Last Updated: 18/7/2023

    Github: Seif-Ibrahim1

*/

#include <iostream>
#include <cassert>

using namespace std;

// FenwickTree class for efficient range sum queries and point updates
class FenwickTree {
    long* tree;     // Array storing the Fenwick tree
    int size;       // Size of the Fenwick tree

    // Function to get the least significant bit
    int lsb(int i) {
        return i & -i;
    }

public:
    // Constructor to initialize the Fenwick tree with a given size
    FenwickTree(int _size) {
        size = _size + 1;
        tree = new long[size];

        for (int i = 0; i < size; i++) {
            tree[i] = 0; 
        }
    }

    // Constructor to initialize the Fenwick tree with an existing array
    FenwickTree(long other[], int _size) {
        size = _size;
        tree = new long[size + 1];

        for (int i = 1; i <= _size; i++) {
            tree[i] = 0;
            tree[i] = other[i - 1];
        }

        for (int i = 1; i < size; i++) {
            int j = i + lsb(i);
            if (j <= size) {
                tree[j] += tree[i];
            }
        }
    }

    // Destructor to deallocate memory
    ~FenwickTree() {
        delete[] tree;
    }

    // Function to compute the prefix sum from index 1 to i
    long prefixSum(int i) {
        long sum = 0L;
        while (i != 0) {
            sum += tree[i];
            i &= ~lsb(i);
        }

        return sum;
    }

    // Function to compute the sum of elements in the range [i, j]
    long sum(int i, int j) {
        return prefixSum(j) - prefixSum(i - 1);
    }

    // Function to add a value k to the element at index i
    void add(int i, long k) {
        while (i < size) {
            tree[i] += k;
            i += lsb(i);
        }
    }

    // Function to set the element at index i to a value k
    void set(int i, long k) {
        long value = sum(i, i);
        add(i, k - value);
    }
};


int main() {
    // Test case 1: Creating a FenwickTree object and testing prefixSum() and add() methods
    cout << "Test Case 1:" << endl;
    FenwickTree tree(10); // Create a FenwickTree object of size 10

    // Add values to the tree
    tree.add(1, 5);
    tree.add(2, 3);
    tree.add(4, 2);
    tree.add(5, 7);
    tree.add(6, 1);
    tree.add(8, 4);

    // Compute and validate prefix sums
    assert(tree.prefixSum(1) == 5);
    assert(tree.prefixSum(2) == 8);
    assert(tree.prefixSum(4) == 10);
    assert(tree.prefixSum(6) == 18);
    assert(tree.prefixSum(8) == 22);
    assert(tree.prefixSum(10) == 22);

    cout << "All prefix sums are correct." << endl << endl;

    // Test case 2: Creating a FenwickTree object using an array and testing sum() and set() methods
    cout << "Test Case 2:" << endl;
    long arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    FenwickTree tree2(arr, 10); // Create a FenwickTree object using the array

    // Compute and validate sums
    assert(tree2.sum(2, 7) == 27);
    assert(tree2.sum(4, 9) == 39);

    // Set a new value
    tree2.set(5, 20);

    // Compute and validate sums after updating a value
    assert(tree2.sum(2, 7) == 42);
    assert(tree2.sum(4, 9) == 54);

    cout << "All sums are correct." << endl;

    return 0;
}
