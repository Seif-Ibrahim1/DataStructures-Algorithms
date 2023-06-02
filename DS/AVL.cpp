/*
    Author: Seif Ibrahim
    Project: AVL 
    Description: AVL Data Strcture implementation

    Last Updated: 2/6/2023

    Github: Seif-Ibrahim1

*/

#include<iostream>
#include <cassert>
using namespace std;

// Node structure for AVL Tree
template <class T>
struct Node {
    Node* left;
    Node* right;
    T value;
    int balanceFactor;
    int height = 0;
    
    // Constructor to initialize Node
    Node(Node* l, Node* r, T v) {
        left = l;
        right = r;
        value = v;
    }
};

// AVL Tree class
template <class T>
class AVLTree {
private:
    Node<T>* root;
    int size;

    // Private helper function to recursively add an element to the AVL tree
    Node<T>* add(Node<T>* node, T element) {
        if(node == nullptr) {
            // Create a new node when reaching an empty spot
            return new Node<T>(nullptr, nullptr, element);
        } else {
            if(element < node->value) {
                // Go to the left subtree if the element is smaller
                node->left = add(node->left, element);
            } else if (element > node->value) {
                // Go to the right subtree if the element is greater
                node->right = add(node->right, element);
            } 
        }
        
        // Update the height and balance factor of the current node
        update(node);
        
        // Balance the node and return the updated node
        return balance(node);
    }

    // Private helper function to recursively remove an element from the AVL tree
    Node<T>* remove(Node<T>* node, T element) {
        if(node == nullptr) {
            return node;
        }
        if(element < node->value) {
            // Go to the left subtree if the element is smaller
            node->left = remove(node->left, element);
        } else if (element > node->value) {
            // Go to the right subtree if the element is greater
            node->right = remove(node->right, element);
        } else {
            // Element found, handle the removal cases
            
            if(node->left == nullptr) {
                // If the left subtree is empty, replace the node with its right child
                Node<T>* rightNode = node->right;
                delete node;
                return rightNode;
            } else if(node->right == nullptr) {
                // If the right subtree is empty, replace the node with its left child
                Node<T>* leftNode = node->left;
                delete node;
                return leftNode;
            } else {
                // If both subtrees are non-empty, replace the node with the maximum value from the left subtree
                if(node->left->height > node->right->height) {
                    int rightValue = findMax(node->left);
                    node->value = rightValue;
                    node->left = remove(node->left, rightValue);

               } else {
                    // Replace the node with the minimum value from the right subtree
                    int leftValue = findMin(node->right);
                    node->value = leftValue;
                    node->right = remove(node->right, leftValue);
               }
            }
        }

        // Update the height and balance factor of the current node
        update(node);
        
        // Balance the node and return the updated node
        return balance(node);
    }

    // Private helper function to balance the AVL tree
    Node<T>* balance(Node<T>* node) {
        if(node->balanceFactor == -2) {
            if(node->left->balanceFactor <= 0) {
                return leftLeftCase(node);
            } else {
                return leftRightCase(node);
            }
        } else if(node->balanceFactor == 2) {
            if(node->right->balanceFactor >= 0) {
                return rightRightCase(node);
            } else {
                return rightLeftCase(node);
            }
        }

        return node;
    }

    // Private helper functions for different balance cases
    Node<T>* leftLeftCase(Node<T>* node) {
        return rightRotation(node);
    }
    
    Node<T>* leftRightCase(Node<T>* node) {
        node->left = leftRotation(node->left);
        return leftLeftCase(node);
    }

    Node<T>* rightRightCase(Node<T>* node) {
        return leftRotation(node);
    }

    Node<T>* rightLeftCase(Node<T>* node) {
        node->right = rightRotation(node->right);
        return rightRightCase(node);
    }

    // Private helper functions for single rotations
    Node<T>* leftRotation(Node<T>* node) {
        Node<T>* newParent = node->right;
        node->right = newParent->left;
        newParent->left = node;
        
        // Update the heights and balance factors
        update(node);
        update(newParent);
        
        return newParent;
    }

    Node<T>* rightRotation(Node<T>* node) {
        Node<T>* newParent = node->left;
        node->left = newParent->right;
        newParent->right = node;
        
        // Update the heights and balance factors
        update(node);
        update(newParent);
        
        return newParent;
    }

    // Private helper function to update the height and balance factor of a node
    void update(Node<T>* node) {
        int leftHeight = (node->left == nullptr) ? 0 : node->left->height;
        int rightHeight = (node->right == nullptr) ? 0 : node->right->height;

        node->height = max(leftHeight, rightHeight) + 1;
        node->balanceFactor = rightHeight - leftHeight;
    }

    // Private helper functions to find the minimum and maximum values in the subtree
    T findMin(Node<T>* node) {
        while(node->left != NULL) {
            node = node->left;
        }
        return node->value;
    }

    T findMax(Node<T>* node) {
        while(node->right != NULL) {
            node = node->right;
        }
        return node->value;
    }

    // Private helper functions for tree traversals
    void preOrder(Node<T>* node) {
        if(node == nullptr) {
            return;
        }
       cout << node->value << endl;
       preOrder(node->left);
       preOrder(node->right);
       
    }

    void inOrder(Node<T>* node) {
        if(node == nullptr) {
            return;
        }
        inOrder(node->left);
        cout << node->value << endl;
        inOrder(node->right);
    }

    void postOrder(Node<T>* node) {
        if(node == nullptr) {
            return;
        }
        postOrder(node->left);
        postOrder(node->right);
        cout << node->value << endl;
    }
    
public:
    // Public constructor for AVL Tree
    AVLTree() {
        root = nullptr;
        size = 0;
    }

    bool isEmpty() {
        return (size == 0);
    }

    int treeSize() {
        return size;
    }

    // Public function to add an element to the AVL tree
    bool add(T element) {
        if(!contains(element)) {
            root = add(root, element);
            size++;
            return true;
        }

        return false;
    }

    // Public function to remove an element from the AVL tree
    bool remove(T element) {
        if(contains(element)) {
            root = remove(root, element);
            size--;
            return true;
        }

        return false;
    }

    // Public function to check if an element exists in the AVL tree
    bool contains(T element) {
        Node<T>* iter = root;
        while(iter != nullptr) {
            if(element < iter->value) {
                iter = iter->left;
            } else if (element > iter->value) {
                iter = iter->right;
            } else {
                return true;
            }
        }

        return false;
    }

    // Public function to get the height of the AVL tree
    int height() {
        return (root != nullptr) ? root->height : 0;
    }

    // Public functions for tree traversals
    void preOrder() {
       preOrder(root);
    }

    void inOrder() {
        inOrder(root);
    }

    void postOrder() {
        postOrder(root);
    }
};

int main() {
    AVLTree<int> tree;

    // Test Case 1: Inserting elements into the AVL tree
    assert(tree.add(10) == true);
    assert(tree.add(20) == true);
    assert(tree.add(30) == true);
    assert(tree.add(40) == true);
    assert(tree.add(50) == true);
    assert(tree.add(60) == true);

    // Test Case 2: Adding duplicate elements
    assert(tree.add(30) == false); // Should return false, as 30 already exists in the tree

    // Test Case 3: Removing elements from the AVL tree
    assert(tree.remove(20) == true);
    assert(tree.remove(40) == true);
    assert(tree.remove(60) == true);
    
    // Test Case 4: Removing elements that don't exist
    assert(tree.remove(70) == false); // Should return false, as 70 doesn't exist in the tree

    // Test Case 5: Checking if elements exist in the AVL tree
    assert(tree.contains(10) == true);
    assert(tree.contains(30) == true);
    assert(tree.contains(50) == true);
    assert(tree.contains(20) == false); // Should return false, as 20 has been removed

    // Test Case 6: Getting the height of the AVL tree
    assert(tree.height() == 2); // The height of the tree should be 2 after removing some elements

    // Test Case 7: Traversing the AVL tree
    cout << "Pre-order traversal:" << endl;
    tree.preOrder();
    cout << endl;

    cout << "In-order traversal:" << endl;
    tree.inOrder();
    cout << endl;

    cout << "Post-order traversal:" << endl;
    tree.postOrder();
    cout << endl;

    return 0;
}
