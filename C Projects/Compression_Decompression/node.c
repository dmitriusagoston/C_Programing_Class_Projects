#include "node.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Node Node;

// creates a new node
// returns newly created node
//
// n: new node being created
// symbol: the symbol for the node
// frequency: how often the symbol appears
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) calloc(1, sizeof(Node));
    if (n) {
        n->symbol = symbol;
        n->frequency = frequency;
    }
    return n;
}

// deletes a node
// returns nothing
//
// n: current node
void node_delete(Node **n) {
    free(*n);
    *n = NULL;
    return;
}

// joins two nodes together
// returns new node of two joined nodes
//
// left: left node being joined
// right: right node being joined
Node *node_join(Node *left, Node *right) {
    Node *parent = node_create('$', left->frequency + right->frequency);
    parent->left = left;
    parent->right = right;
    return parent;
}

// prints the given node
// returns nothing
//
// n: node being printed
void node_print(Node *n) {
    printf("symbol: %c frequency: %lu\n", n->symbol, n->frequency);
    if (n->left) {
        printf("left: %c %hhu\n", n->left->symbol, n->left->symbol);
    }
    if (n->right) {
        printf("right: %c %hhu\n", n->right->symbol, n->right->symbol);
    }
    printf("\n");
}
