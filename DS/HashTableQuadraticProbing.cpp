/*
    Author: Seif Ibrahim
    Description: Hash Table Quadratic Probing Data Strcture implementation

    Last Updated: 2/6/2023

    Github: Seif-Ibrahim1

*/

#include <iostream>
#include <cassert>

using namespace std;

// Function to compute the hash code of a key
template <typename K>
int getHashCode(K key) {
    hash<K> hash_fn;
    return hash_fn(key);
}

// HashTableQuadraticProbing class for implementing a hash table with quadratic probing
template<typename K, typename V>
class HashTableQuadraticProbing {
    private:
    double loadFactor = 0.45;              // Load factor for resizing
    int capacity, threshold, modificationCount = 0, keyCount = 0, usedBuckets = 0;   // Capacity, threshold, modification count, key count, and used bucket count of the hash table
    K** keyTable;                          // Array for storing keys
    V** valueTable;                        // Array for storing values
    bool containsFlag = false;             // Flag to track key existence
    K* TOMBSTONE = new K();                 // Special key value to mark deleted entries

    // Function to find the next power of 2
    int nextPowerOf2(int n) {
        while (n & (n - 1)) {
            n &= n - 1;        
        }
        return n << 1;
    }

    // Function to compute the quadratic probing function p(x) = (x^2 + x) / 2
    int p(int x) {
        return (x * x + x) >> 1;
    }

    // Function to normalize the key's hash code to an index within the capacity of the hash table
    int normalizeIndex(int keyHash) {
        return (keyHash & 0x7FFFFFFF) % capacity;
    }

    // Function to resize the hash table when the load factor exceeds the maximum load factor
    void resize() {
        int oldCapacity = capacity;
        capacity = nextPowerOf2(capacity);
        threshold = capacity * loadFactor;
        K** oldKeyTable = keyTable;
        V** oldValueTable = valueTable;

        keyTable = new K*[capacity];
        valueTable = new V*[capacity];
        keyCount = 0;
        usedBuckets = 0;

        for (int i = 0; i < capacity; i++) {
            keyTable[i] = nullptr;
            valueTable[i] = nullptr;
        }

        for (int i = 0; i < oldCapacity; i++) {
            if (oldKeyTable[i] != nullptr && oldKeyTable[i] != TOMBSTONE) {
                insert(*oldKeyTable[i], *oldValueTable[i]);
            }
        }

        for (int i = 0; i < oldCapacity; i++) {
            delete oldKeyTable[i];
            delete oldValueTable[i];
        }

        delete[] oldKeyTable;
        delete[] oldValueTable;
    }

    public:
    // Constructor to initialize the hash table with a given capacity
    HashTableQuadraticProbing(int _capacity) {
        if (_capacity < 8) {
            capacity = 8;
        } else {
            capacity = _capacity;
        }

        threshold = capacity * loadFactor;
        
        keyTable = new K*[capacity];
        valueTable = new V*[capacity];
        for(int i = 0; i < capacity; i++) {
            keyTable[i] = nullptr;
            valueTable[i] = nullptr;
        }
    }

    // Get the current size of the hash table
    int size() {
        return keyCount;
    }

    // Check if the hash table is empty
    bool isEmpty() {
        return (keyCount == 0);
    }

    // Clear the hash table and reset it to its initial state
    void clear() {
        for(int i = 0; i < keyCount; i++) {
            keyTable[i] = nullptr;
            valueTable[i] = nullptr;
        }
        keyCount = 0, usedBuckets = 0, modificationCount++;
    }

    // Check if the hash table contains an entry with the given key
    bool containsKey(K key) {
        get(key);
        return containsFlag;
    }

    // Insert a new entry with the given key and value into the hash table
    void insert(K key, V value) {
        if(usedBuckets >= threshold) {
            resize();
        }
        int _hash = normalizeIndex(getHashCode(key));
        int i = _hash, tombstonePos = -1, offset = 1;
        do {
            if(keyTable[i] == TOMBSTONE) {
                if(tombstonePos == -1) {
                    tombstonePos = i;
                }
            } else if (keyTable[i] != nullptr) {
                if(key == *keyTable[i]) {
                    if(tombstonePos == -1) {
                        *valueTable[i] = value;
                    } else {
                        keyTable[i] = TOMBSTONE;
                        valueTable[i] = nullptr;
                        *keyTable[tombstonePos] = key;
                        *valueTable[tombstonePos] = value;
                    }

                    modificationCount++;
                    return;
                }
            } else {
                if(tombstonePos == -1) {
                    usedBuckets++;
                    keyTable[i] = new K(key);
                    valueTable[i] = new V(value);
                } else {
                    keyTable[tombstonePos] = new K(key);
                    valueTable[tombstonePos] = new V(value);
                }
                keyCount++;
                modificationCount++;
                return;
            }
            i = normalizeIndex(_hash + p(offset++));

        } while (true);
    }

    // Remove the entry with the given key from the hash table
    void remove(K key) {
        int _hash = normalizeIndex(getHashCode(key));
        int i = _hash, offset = 1;
        while (true) {
            if(keyTable[i] == TOMBSTONE) {
                i = normalizeIndex(_hash + p(offset++));
                continue;
            }

            if(keyTable[i] == nullptr) {
                return;
            }

            if(*keyTable[i] == key) {
                keyCount--, modificationCount++;
                keyTable[i] = TOMBSTONE;
                valueTable[i] = nullptr;
                return;
            }
        }
    }

    // Get the value associated with the given key from the hash table
    V get(K key) {
        int _hash = normalizeIndex(getHashCode(key));
        int i = _hash, tombstonePos = -1, offset = 1;
        do {
            if(keyTable[i] == TOMBSTONE) {
                if(tombstonePos == -1) {
                    tombstonePos = i;
                }
            } else if (keyTable[i] != nullptr) {
                if(key == *keyTable[i]) {
                    containsFlag = true;
                    if(tombstonePos == -1) {
                        return *valueTable[i];
                    } else {
                        keyTable[tombstonePos] = keyTable[i];
                        valueTable[tombstonePos] = valueTable[i];

                        keyTable[i] = TOMBSTONE;
                        valueTable[i] = nullptr;

                        return *valueTable[tombstonePos];
                    }
                }
            } else {
                containsFlag = false;
                return V();
            }
            i = normalizeIndex(_hash + p(offset++));

        } while (true);
    }
};


int main() {
    // Test Case 1: Insertion and Retrieval
    {
        HashTableQuadraticProbing<int, string> hashTable(10);
        hashTable.insert(1, "John");
        hashTable.insert(2, "Alice");
        hashTable.insert(3, "Bob");

        // Retrieve values
        string value1 = hashTable.get(1);
        string value2 = hashTable.get(2);
        string value3 = hashTable.get(3);

        // Expected values
        string expectedValue1 = "John";
        string expectedValue2 = "Alice";
        string expectedValue3 = "Bob";

        // Check if retrieved values are correct
        assert(value1 == expectedValue1);
        assert(value2 == expectedValue2);
        assert(value3 == expectedValue3);
    }

    // Test Case 2: Removal
    {
        HashTableQuadraticProbing<int, string> hashTable(10);
        hashTable.insert(1, "John");
        hashTable.insert(2, "Alice");
        hashTable.insert(3, "Bob");

        // Remove a key
        hashTable.remove(2);

        // Try to retrieve the removed key
        string value = hashTable.get(2);

        // Expected value is an empty string as the key was removed
        assert(value.empty());
    }

    // Test Case 3: Resize and Rehash
    {
        HashTableQuadraticProbing<string, int> hashTable(5);
        hashTable.insert("apple", 5);
        hashTable.insert("banana", 10);
        hashTable.insert("cherry", 15);

        // Check the initial size of the hash table
        int initialSize = hashTable.size();
        assert(initialSize == 3);

        // Insert more elements to trigger a resize
        hashTable.insert("date", 20);
        hashTable.insert("elderberry", 25);

        // Check the new size of the hash table after resizing
        int newSize = hashTable.size();
        assert(newSize == 5);

        // Retrieve values after resizing
        int value1 = hashTable.get("apple");
        int value2 = hashTable.get("banana");
        int value3 = hashTable.get("cherry");
        int value4 = hashTable.get("date");
        int value5 = hashTable.get("elderberry");

        // Expected values remain the same after resizing
        int expectedValue1 = 5;
        int expectedValue2 = 10;
        int expectedValue3 = 15;
        int expectedValue4 = 20;
        int expectedValue5 = 25;

        // Check if retrieved values are correct after resizing
        assert(value1 == expectedValue1);
        assert(value2 == expectedValue2);
        assert(value3 == expectedValue3);
        assert(value4 == expectedValue4);
        assert(value5 == expectedValue5);
    }


    cout << "All test cases passed!" << endl;

    return 0;
}
