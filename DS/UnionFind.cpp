/*
    Author: Seif Ibrahim
    Description: Union Find implementation

    Last Updated: 18/7/2023

    Github: Seif-Ibrahim1

*/

#include <iostream>
#include <cassert>

using namespace std;

// UnionFind class for implementing the union-find data structure
class UnionFind {
    private:
    int* sizes;                 // Array to store the size of each component
    int* ids;                   // Array to store the parent id of each element
    int componentsCount = 0;    // Count of total components
    int count = 0;              // Count of total elements

    public:
    // Constructor to initialize the UnionFind object
    UnionFind(int _count) {
        count = componentsCount = _count;
        sizes = new int[count];
        ids = new int[count];

        // Initialize each element's id and size
        for(int i =0; i < count; i++) {
            ids[i] = i;
            sizes[i] = 1;
        }
    }

    // Find the root of the given element
    int find(int index) {
        int root = index;

        // Find the root of the element
        while(root != ids[root]) {
            root = ids[root];
        }

        // Perform path compression
        while(index != root) {
            int next = ids[index];
            ids[index] = root;
            index = next;
        }

        return root;
    }

    // Check if two elements are connected
    bool connected(int x, int y) {
        return (find(x) == find(y));
    }

    // Get the size of the component containing the given element
    int componentSize(int x) {
        return sizes[find(x)];
    }

    // Get the total number of elements
    int size() {
        return count;
    }

    // Get the total number of components
    int components() {
        return componentsCount;
    }

    // Unify (merge) two components containing the given elements
    void unify(int x, int y) {
        int root1 = find(x);
        int root2 = find(y);

        // If both elements are already in the same component, do nothing
        if(root1 == root2) {
            return;
        }

        // Merge the smaller component into the larger component
        if(sizes[root1] < sizes[root2]) {
            sizes[root2] += sizes[root1];
            ids[root1] = root2;
        } else {
            sizes[root1] += sizes[root2];
            ids[root2] = root1;
        }

        // Decrease the component count
        componentsCount--;
    }
};

int main() {
    // Test case 1: Testing initialization of UnionFind objects
    UnionFind uf1(5);
    assert(uf1.size() == 5);
    assert(uf1.components() == 5);

    // Test case 2: Testing the find method
    int root1 = uf1.find(3);
    assert(root1 == 3);

    // Test case 3: Testing the connected method
    assert(!uf1.connected(1, 4));

    // Test case 4: Testing the componentSize, size, and components methods
    assert(uf1.componentSize(2) == 1);
    assert(uf1.size() == 5);
    assert(uf1.components() == 5);

    // Test case 5: Testing the unify method
    uf1.unify(1, 3);
    assert(uf1.componentSize(1) == 2);
    assert(uf1.components() == 4);

    cout << "All test cases passed!" << endl;

    return 0;
}