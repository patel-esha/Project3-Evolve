#ifndef PROJECT3A_EVOLVE_REDBLACKTREE_H
#define PROJECT3A_EVOLVE_REDBLACKTREE_H


#include <iostream>
using namespace std;

template <typename T>
class RedBlackTree {
public:
    struct Node {
        T data;
        Node *parent;
        Node *left;
        Node *right;
        int color; // 1 -> Red, 0 -> Black
        Node(T data) : data(data), parent(nullptr), left(nullptr), right(nullptr), color(1) {}
    };

    Node* root;

    RedBlackTree() : root(nullptr) {}

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

    void insertFixUp(Node* z) {
        while (z->parent != nullptr && z->parent->color == 1) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y != nullptr && y->color == 1) {
                    z->parent->color = 0;
                    y->color = 0;
                    z->parent->parent->color = 1;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = 0;
                    z->parent->parent->color = 1;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y != nullptr && y->color == 1) {
                    z->parent->color = 0;
                    y->color = 0;
                    z->parent->parent->color = 1;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = 0;
                    z->parent->parent->color = 1;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = 0;
    }

    void insert(const T& data) {
        Node* z = new Node(data);
        Node* y = nullptr;
        Node* x = this->root;

        while (x != nullptr) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == nullptr) {
            root = z;
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }

        insertFixUp(z);
    }

    void inOrderDisplay(Node* root) {
        if (root != nullptr) {
            inOrderDisplay(root->left);
            cout << root->data << endl;
            inOrderDisplay(root->right);
        }
    }

    void display() {
        inOrderDisplay(this->root);
    }

    Node* search(const T& key) {
        Node* current = root;
        while (current != nullptr) {
            if (key < current->data) {
                current = current->left;
            } else if (key > current->data) {
                current = current->right;
            } else {
                return current; // key is found
            }
        }
        return nullptr; // key is not found
    }

    void deleteNode(Node*& root, Node *z) {
        Node *x, *y;

        if (!z || z == nullptr) return;

        if (z->left == nullptr || z->right == nullptr) {
            /* y has a NIL node as a child */
            y = z;
        } else {
            /* find tree successor with a NIL node as a child */
            y = z->right;
            while (y->left != nullptr) y = y->left;
        }

        /* x is y's only child */
        if (y->left != nullptr)
            x = y->left;
        else
            x = y->right;

       /* remove y from the parent chain */
        if (x != nullptr) {
            x->parent = y->parent;
        }

        if (y->parent) {
            if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;
        } 
        else {
            root = x;
        }

        if (y != z) z->data = y->data;

        if (y->color == 0 && x != nullptr)
            deleteFixUp(root, x);

        delete y;
    }


    void deleteFixUp(Node*& root, Node* x) {
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                Node *w = x->parent->right;
                if (w->color == 1) {
                    w->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == 0 && w->right->color == 0) {
                    w->color = 1;
                    x = x->parent;
                } else {
                    if (w->right->color == 0) {
                        w->left->color = 0;
                        w->color = 1;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                if (x == x->parent->right) {
                Node *w = x->parent->left;
                if (w->color == 1) {
                    w->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == 0 && w->right->color == 0) {
                    w->color = 1;
                    x = x->parent;
                } else {
                    if (w->left->color == 0) {
                        w->right->color = 0;
                        w->color = 1;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                    }
                }
            }
        }
        x->color = 0;
    }



    ~RedBlackTree() {
        // Implement a destructor to clean up memory
    }
};

#endif //PROJECT3A_EVOLVE_REDBLACKTREE_H
