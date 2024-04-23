#ifndef PROJECT3A_EVOLVE_SPLAYTREE_H
#define PROJECT3A_EVOLVE_SPLAYTREE_H


#include <iostream>
using namespace std;

template <typename T>
class SplayTree {
public:
    struct Node {
        T data;
        Node *left, *right, *parent;
        int count = 0;
        Node(T data, int count = 1) : data(data), count(count), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;

    SplayTree() : root(nullptr) {}

    ~SplayTree() {
        destroyTree(root);
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void splay(Node* x) {
        while (x->parent != nullptr) {
            if (x->parent->parent == nullptr) {
                if (x->parent->left == x) {
                    rightRotate(x->parent);
                } else {
                    leftRotate(x->parent);
                }
            } else if (x->parent->left == x && x->parent->parent->left == x->parent) {
                rightRotate(x->parent->parent);
                rightRotate(x->parent);
            } else if (x->parent->right == x && x->parent->parent->right == x->parent) {
                leftRotate(x->parent->parent);
                leftRotate(x->parent);
            } else if (x->parent->left == x && x->parent->parent->right == x->parent) {
                rightRotate(x->parent);
                leftRotate(x->parent);
            } else {
                leftRotate(x->parent);
                rightRotate(x->parent);
            }
        }
    }

    Node* insert(T key) {
        Node* z = root;
        Node* p = nullptr;

        while (z != nullptr) {
            p = z;
            if (key < z->data) {
                z = z->left;
            } else if (key > z->data) {
                z = z->right;
            } else {
                z->count++;  // Increment count on finding a duplicate
                splay(z);    // Splay the node to the top
                return z;    // Return the node after incrementing the count
            }
        }

        z = new Node(key);  // Create a new node if not a duplicate
        z->parent = p;

        if (p == nullptr) {
            root = z;  // New node is root if tree was empty
        } else if (p->data > z->data) {
            p->left = z;
        } else {
            p->right = z;
        }

        splay(z);  // Splay the new node to the top
        return z;
    }

    void inOrderDisplay(Node* root) {
        if (root != nullptr) {
            inOrderDisplay(root->left);
            cout << root->data << endl;
            inOrderDisplay(root->right);
        }
    }

    void inOrderDisplayDuplicates(Node* root) {
        if (root != nullptr) {
            inOrderDisplayDuplicates(root->left);
            cout << root->data << " (" << root->count << " times)" << endl;
            inOrderDisplayDuplicates(root->right);
        }
    }

    void display() {
        inOrderDisplay(this->root);
    }

    void displayDuplicates() {
        inOrderDisplayDuplicates(this->root);
    }

    Node* search(const T& key) {
        Node* z = root;
        Node* last = nullptr;

        while (z != nullptr) {
            last = z;
            if (key < z->data) {
                z = z->left;
            } else if (key > z->data) {
                z = z->right;
            } else {
                splay(z);
                return z;  // key found and splayed to the root
            }
        }

        if (last != nullptr) {
            splay(last);  // Splay the last accessed node to root if key not found
        }
        return nullptr;  // key not found
    }


    void deleteNode(const T& key) {
        Node* nodeToDelete = search(key);  // This will splay the node to the root
        if (nodeToDelete == nullptr) {
            cout << "Node not found." << endl;
            return;  // Node to delete not found
        }
        if (nodeToDelete->count > 1) {
        nodeToDelete->count--;
        }

        Node* leftSubtree = nodeToDelete->left;
        Node* rightSubtree = nodeToDelete->right;

        if (leftSubtree != nullptr) {
            leftSubtree->parent = nullptr;
        }
        if (rightSubtree != nullptr) {
            rightSubtree->parent = nullptr;
        }

        // If there's a left child, it becomes the new root
        if (leftSubtree != nullptr) {
            root = leftSubtree;
            Node* maxNode = root;
            while (maxNode->right != nullptr) {  // Find the maximum node on the left subtree
                maxNode = maxNode->right;
            }
            maxNode->right = rightSubtree;  // Attach the right subtree
            if (rightSubtree != nullptr) {
                rightSubtree->parent = maxNode;
            }
            splay(maxNode);  // Splay the max node of the left subtree
        } else {
            root = rightSubtree;  // No left child, the right child becomes the root
        }

        delete nodeToDelete;  // Free the memory of the node to be deleted
    }

private:
    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
};

#endif //PROJECT3A_EVOLVE_SPLAYTREE_H
