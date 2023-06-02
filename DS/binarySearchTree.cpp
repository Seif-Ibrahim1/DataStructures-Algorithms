/*
    Author: Seif Ibrahim
    Project: BST 
    Description: Binary Search Tree Data Strcture implementation

    Last Updated: 2/6/2023

    Github: Seif-Ibrahim1

*/

#include<iostream>
#include <cassert>
using namespace std;

// Structure representing a node in the binary search tree
template <class T>
struct Node {
    Node* left;
    Node* right;
    T value;
    
    // Constructor for the Node structure
    Node(Node* l, Node* r, T v) {
        left = l;
        right = r;
        value = v;
    }
};

// BinarySearchTree class implementing a binary search tree
template <class T>
class BinarySearchTree {
    private:
    Node<T>* root; // Pointer to the root of the binary search tree
    int size; // Number of elements in the tree

    // Private helper function to recursively add an element to the binary search tree
    Node<T>* add(Node<T>* node, T element) {
        if(node == nullptr) {
            // If the node is null, create a new node with the given element
            node = new Node<T>(nullptr, nullptr, element);
        } else {
            // If the node is not null, recursively add the element to the left or right subtree
            if(element < node->value) {
                node->left = add(node->left, element);
            } else if (element > node->value) {
                node->right = add(node->right, element);
            } 
        }
        return node;
    }

    // Private helper function to recursively remove an element from the binary search tree
    Node<T>* remove(Node<T>* node, T element) {
        if(element < node->value) {
            node->left = remove(node->left, element);
        } else if (element > node->value) {
            node->right = remove(node->right, element);
        } else {
            if(node->left == nullptr) {
                // If the node has no left child, replace it with its right child
                Node<T>* rightNode = node->right;
                delete node;
                return rightNode;
            } else if(node->right == nullptr) {
                // If the node has no right child, replace it with its left child
                Node<T>* leftNode = node->left;
                delete node;
                return leftNode;
            } else {
                // If the node has both left and right children, replace it with the rightmost node in the left subtree
                Node<T>* rightMost = digRight(node->left);
                node->value = rightMost->value;
                node->left = remove(node->left, rightMost->value);
            }
        }
        return node;
    }

    // Private helper function to find the rightmost node in a subtree
    Node<T>* digRight(Node<T>* node) {
        while(node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    // Private helper function to calculate the height of a node in the binary search tree
    int height(Node<T>* node) {
        if(node == nullptr) {
            return 0;
        }
        // Recursively calculate the height of the left and right subtrees and return the maximum height plus 1
        return max(height(node->left), height(node->right)) + 1;
    }

    // Private helper function to perform a pre-order traversal of the binary search tree
    void preOrder(Node<T>* node) {
        if(node == nullptr) {
            return;
        }
        // Print the value of the current node, then recursively traverse the left and right subtrees
        cout << node->value << endl;
        preOrder(node->left);
        preOrder(node->right);   
    }

    // Private helper function to perform an in-order traversal of the binary search tree
    void inOrder(Node<T>* node) {
        if(node == nullptr) {
            return;
        }
        // Recursively traverse the left subtree, print the value of the current node, then recursively traverse the right subtree
        inOrder(node->left);
        cout << node->value << endl;
        inOrder(node->right);
    }

    // Private helper function to perform a post-order traversal of the binary search tree
    void postOrder(Node<T>* node) {
        if(node == nullptr) {
            return;
        }
        // Recursively traverse the left and right subtrees, then print the value of the current node
        postOrder(node->left);
        postOrder(node->right);
        cout << node->value << endl;
    }
    
    public:
    // Constructor for the BinarySearchTree class
    BinarySearchTree() {
        root = nullptr; // Initialize the root to null
        size = 0; // Initialize the size to 0
    }

    // Public function to check if the binary search tree is empty
    bool isEmpty() {
        return (size == 0);
    }

    // Public function to get the number of elements in the binary search tree
    int treeSize() {
        return size;
    }

    // Public function to add an element to the binary search tree
    bool add(T element) {
        if(!contains(element)) {
            // If the element does not exist in the tree, recursively add it
            root = add(root, element);
            size++;
            return true;
        }
        return false;
    }

    // Public function to remove an element from the binary search tree
    bool remove(T element) {
        if(contains(element)) {
            // If the element exists in the tree, recursively remove it
            remove(root, element);
            size--;
            return true;
        }
        return false;
    }

    // Public function to check if an element exists in the binary search tree
    bool contains(T element) {
        Node<T>* iter = root;
        while(iter != nullptr) {
            // Traverse the tree to find the element
            if(element < iter->value) {
                iter = iter->left;
            } else if (element > iter->value) {
                iter = iter->right;
            } else {
                // Return true if the element is found
                return true;
            }
        }
        // Return false if the element is not found
        return false;
    }

    // Public function to get the height of the binary search tree
    int height() {
        return height(root);
    }

    // Public function to perform a pre-order traversal of the binary search tree
    void preOrder() {
       preOrder(root);
    }

    // Public function to perform an in-order traversal of the binary search tree
    void inOrder() {
        inOrder(root);
    }

    // Public function to perform a post-order traversal of the binary search tree
    void postOrder() {
        postOrder(root);
    }
};

int main() {
    BinarySearchTree<int> myTree;

    // Test case 1: Add elements to the tree
    myTree.add(10);
    myTree.add(5);
    myTree.add(15);
    myTree.add(7);

    // Test case 2: Check if the tree is empty
    assert(!myTree.isEmpty());

    // Test case 3: Check the size of the tree
    assert(myTree.treeSize() == 4);

    // Test case 4: Check if the tree contains elements
    assert(myTree.contains(10));
    assert(myTree.contains(5));
    assert(myTree.contains(15));
    assert(myTree.contains(7));
    assert(!myTree.contains(20));

    // Test case 5: Remove elements from the tree
    assert(myTree.remove(5));
    assert(!myTree.contains(5));
    assert(myTree.treeSize() == 3);

    // Test case 6: Get the height of the tree
    assert(myTree.height() == 2);

    // Test case 7: Traverse the tree in different orders
    cout << "Pre-order traversal:" << endl;
    myTree.preOrder();
    cout << "In-order traversal:" << endl;
    myTree.inOrder();
    cout << "Post-order traversal:" << endl;
    myTree.postOrder();

    assert(!myTree.isEmpty());

    std::cout << "All test cases passed!" << std::endl;

    return 0;
}
