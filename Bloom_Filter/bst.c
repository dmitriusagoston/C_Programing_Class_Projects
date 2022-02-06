// Some code was taken from Lecture-18-Trees-and-BST.pdf
// Written by Darrell Long
// code used: bst_height(), bst_find(), bst_insert()

#include "bst.h"
#include "node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

uint64_t branches = 0;

// creates a new empty binary search tree
// returns the root of the newly created tree
//
// bst: new binary search tree being created
Node *bst_create() {
    Node *bst = NULL;
    return bst;
}

// deletes a given binary search tree
// returns nothing
//
// root: the root node of the binary search tree
void bst_delete(Node **root) {
    if (*root) {
        bst_delete(&(*root)->left);
        bst_delete(&(*root)->right);
        node_delete(root);
    }
    return;
}

// finds the height of a given binary search tree
// returns the height of the tree
//
// root: the root node of the binary search tree
uint32_t bst_height(Node *root) {
    if (root) {
        uint32_t lheight = bst_height(root->left);
        uint32_t rheight = bst_height(root->right);
        if (lheight > rheight) {
            return 1 + lheight;
        } else {
            return 1 + rheight;
        }
    }
    return 0;
}

// gets the size of a given binary search tree
// returns the size of the tree
//
// root: the root node of the binary search tree
uint32_t bst_size(Node *root) {
    if (root) {
        uint32_t sum = 0;
        if (root->left) {
            sum += bst_size(root->left);
        }
        if (root->right) {
            sum += bst_size(root->right);
        }
        sum++;
        return sum;
    }
    return 0;
}

// searches the given binary search tree for an existing oldspeak node
// returns the oldspeak node if found or a null pointer
//
// root: the root node of the binary search tree
// oldspeak: the oldspeak word being searched for
Node *bst_find(Node *root, char *oldspeak) {
    if (root) {
        branches++;
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            return bst_find(root->left, oldspeak);
        } else if (strcmp(root->oldspeak, oldspeak) < 0) {
            return bst_find(root->right, oldspeak);
        }
    }
    return root;
}

// inserts a new node into the given binary search tree
// returns the new tree with the node inserted
//
// root: the root node of the binary search tree
// oldspeak: the oldspeak word being added
// newspeak: the translation of the oldspeak word if applicable
Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    if (root) {
        branches++;
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            root->left = bst_insert(root->left, oldspeak, newspeak);
        } else if (strcmp(root->oldspeak, oldspeak) < 0) {
            root->right = bst_insert(root->right, oldspeak, newspeak);
        }
        return root;
    }
    return node_create(oldspeak, newspeak);
}

// prints a given binary search tree
// returns nothing
//
// root: the root node of the binary search tree
void bst_print(Node *root) {
    if (root) {
        if (root->left) {
            bst_print(root->left);
        }
        node_print(root);
        if (root->right) {
            bst_print(root->right);
        }
    }
    return;
}
