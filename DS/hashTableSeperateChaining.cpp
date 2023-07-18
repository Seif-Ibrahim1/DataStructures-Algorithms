/*
    Author: Seif Ibrahim
    Description: Hash Table Seperate Chaining Data Strcture implementation

    Last Updated: 2/6/2023

    Github: Seif-Ibrahim1

*/

#include <iostream>
#include <list>
#include <cassert>

using namespace std;

// Function to compute the hash code of a key
template <typename K>
int getHashCode(K key) {
    hash<K> hash_fn;
    return hash_fn(key);
}

// Entry class to represent a key-value pair
template<typename K, typename V>
class Entry {
    public:
    int _hash;  // Hash code of the key
    K key;      // Key
    V value;    // Value

    Entry(K _key, V _value) {
        key = _key;
        value = _value;
        _hash = getHashCode(key);
    }

    // Check if two entries are equal
    bool equals(Entry<K, V> other) {
        if (other._hash == _hash) {
            return other.key == key;
        }
        return false;
    }
};

// HashTableSeperateChaining class for implementing a hash table with separate chaining
template<typename K, typename V>
class HashTableSeperateChaining {
    private:
    double maxLoadFactor = 0.75;            // Maximum load factor for resizing
    int capacity, threshold, _size = 0;    // Capacity, threshold, and current size of the hash table
    list<Entry<K, V>*> **table;             // Array of linked lists for storing entries

    // Normalize the key's hash code to an index within the capacity of the hash table
    int normalizeIndex(int keyHash) {
        return (keyHash & 0x7FFFFFFF ) % capacity;
    }

    // Get the entry with the given key from a specific bucket
    Entry<K, V>* bucketGetEntry(int bucketIndex, K* key) {
        if(key == NULL) {
            return NULL;
        }
        list<Entry<K, V>*>* bucket = table[bucketIndex];
        if(bucket == NULL) {
            return NULL;
        }
        for(Entry<K, V> *entry : *bucket) {
            if(entry->key == *key) {
                return entry;
            }
        }
        return NULL;
    }

    // Insert an entry into a specific bucket
    void bucketInsertEntry(int bucketIndex, Entry<K, V>* entry) {
        if (table[bucketIndex] == NULL) {
            table[bucketIndex] = new list<Entry<K, V>*>;
        }
        list<Entry<K, V>*>* bucket = table[bucketIndex];
        Entry<K, V>* existentEntry = bucketGetEntry(bucketIndex, &entry->key);
        if(existentEntry == NULL) {
            bucket->push_back(entry);
            if(++_size > threshold) {
                resize();
            }
        } else { 
            existentEntry->value = entry->value;
        }
    }

    // Remove an entry with the given key from a specific bucket
    void bucketRemoveEntry(int bucketIndex, K* key) {
        Entry<K, V>* entry = bucketGetEntry(bucketIndex, key);

        list<Entry<K, V>*>* bucket = table[bucketIndex];
        bucket->remove(entry);
        _size--;
    }

    // Resize the hash table when the load factor exceeds the maximum load factor
    void resize() {
        int oldCapacity = capacity;
        capacity *= 2;
        list<Entry<K, V>*>** newTable = new list<Entry<K, V>*>*[capacity];

        for (int i = 0; i < capacity; i++) {
            newTable[i] = new list<Entry<K, V>*>();
        }

        // Rehash all existing entries to the new table
        for (int i = 0; i < oldCapacity; i++) {
            if (table[i] != NULL) {
                for (Entry<K, V>* entry : *(table[i])) {
                    int newBucketIndex = normalizeIndex(entry->_hash);
                    newTable[newBucketIndex]->push_back(entry);
                }

                // Clean up the old bucket
                delete table[i];
            }
        }

        delete[] table;

        table = newTable;
        threshold = capacity * maxLoadFactor;
    }

    public:
    // Constructor to initialize the hash table with a given capacity
    HashTableSeperateChaining(int _capacity) {
        if (_capacity < 3) {
            capacity = 3;
        } else {
            capacity = _capacity;
        }

        threshold = capacity * maxLoadFactor;
        
        table = new list<Entry<K, V>*>*[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = new list<Entry<K, V>*>();
        }
    }

    // Get the current size of the hash table
    int size() {
        return _size;
    }

    // Check if the hash table is empty
    bool isEmpty() {
        return (_size == 0);
    }

    // Clear the hash table and reset it to its initial state
    void clear() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] != NULL) {
                for (Entry<K, V>* entry : *(table[i])) {
                    delete entry;
                }
                delete table[i];
            }
        }

        delete[] table;
        _size = 0;

        // Reset capacity and threshold
        capacity = 3;
        threshold = capacity * maxLoadFactor;

        // Create a new table with the initial capacity
        table = new list<Entry<K, V>*>*[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = new list<Entry<K, V>*>();
        }
    }

    // Check if the hash table contains an entry with the given key
    bool containsKey(K key) {
        int bucketIndex = normalizeIndex(getHashCode(key));
        return bucketGetEntry(bucketIndex, &key) != NULL;
    }

    // Insert a new entry with the given key and value into the hash table
    void insert(K key, V value) {
        Entry<K, V>* entry = new Entry<K, V>(key, value);
        int bucketIndex = normalizeIndex(entry->_hash);

        bucketInsertEntry(bucketIndex, entry);
    }

    // Remove the entry with the given key from the hash table
    void remove(K key) {
        int bucketIndex = normalizeIndex(getHashCode(key));
        bucketRemoveEntry(bucketIndex, &key);
    }

    // Get the value associated with the given key from the hash table
    V get(K key) {
        int bucketIndex = normalizeIndex(getHashCode(key));
        Entry<K, V>* entry = bucketGetEntry(bucketIndex, &key);

        if(entry == NULL) {
            throw out_of_range("Key not found");
        }

        return entry->value;
    }
};


int main() {
    // Test case 1: Inserting and retrieving values
    HashTableSeperateChaining<string, int> hashTable(5);
    hashTable.insert("Alice", 1);
    hashTable.insert("Bob", 2);
    hashTable.insert("Charlie", 3);
    assert(hashTable.size() == 3);
    assert(hashTable.containsKey("Alice") == true);
    assert(hashTable.get("Alice") == 1);
    assert(hashTable.get("Charlie") == 3);

    // Test case 2: Removing values
    hashTable.remove("Bob");
    assert(hashTable.size() == 2);
    assert(hashTable.containsKey("Bob") == false);

    // Test case 3: Handling collisions
    HashTableSeperateChaining<int, string> hashTable2(3);
    hashTable2.insert(1, "Apple");
    hashTable2.insert(4, "Banana");
    hashTable2.insert(5, "Cherry");

    // Test case 4: Clearing the hash table
    assert(hashTable2.isEmpty() == false);
    hashTable2.clear();
    assert(hashTable2.size() == 0);
    assert(hashTable2.isEmpty() == true);

    cout << "All test cases passed successfully!" << endl;

    return 0;
}
