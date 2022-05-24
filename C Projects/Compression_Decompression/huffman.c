#include "huffman.h"
#include "node.h"
#include "pq.h"
#include "io.h"
#include "stack.h"
#include "defines.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// builds a tree given a histogram
// returns built tree
//
// hist: histogram for building tree
Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *pq = pq_create(ALPHABET);
    Node *root;
    // create nodes from histogram
    for (uint32_t i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            Node *node = node_create(i, hist[i]);
            enqueue(pq, node);
        }
    }
    // construct tree
    while (pq_size(pq) >= 2) {
        Node *left, *right;
        dequeue(pq, &left);
        dequeue(pq, &right);
        Node *parent = node_join(left, right);
        enqueue(pq, parent);
    }
    // return root of tree
    dequeue(pq, &root);
    pq_delete(&pq);
    return root;
}

static Code code;

// builds code given a huffman tree and code table
// returns nothing
//
// root: node of root of huffman tree
// table: code table
void build_codes(Node *root, Code table[static ALPHABET]) {
    if (root) {
        if (!root->left && !root->right) {
            table[root->symbol] = code;
        } else {
            uint8_t temp = 0;
            // left link
            code_push_bit(&code, 0);
            build_codes(root->left, table);
            code_pop_bit(&code, &temp);
            // right link
            code_push_bit(&code, 1);
            build_codes(root->right, table);
            code_pop_bit(&code, &temp);
        }
    }
    return;
}

// give the dump tree of a huffman tree to the outfile
// returns nothing
//
// root: node of root of huffman tree
// outfile: file to write to
void dump_tree(int outfile, Node *root) {
    // Leaf
    uint8_t L = 'L';
    // Internal
    uint8_t I = 'I';
    if (root) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);
        // Leaf case
        if (!root->left && !root->right) {
            write_bytes(outfile, &L, 1);
            write_bytes(outfile, &root->symbol, 1);
            // Internal case
        } else {
            write_bytes(outfile, &I, 1);
        }
    }
    return;
}

// given a tree dump rebuilds the Huffman tree
// returns root of Huffman tree
//
// nbytes: number of bytes
// tree_dump: data for Huffman tree rebuilding
Node *rebuild_tree(uint16_t nbytes, uint8_t tree_dump[static nbytes]) {
    Stack *stack = stack_create(ALPHABET);
    for (int i = 0; i < nbytes; i++) {
        // Leaf case
        if (tree_dump[i] == 'L') {
            Node *leaf = node_create(tree_dump[i + 1], 0);
            stack_push(stack, leaf);
            i++;
            // Internal case
        } else if (tree_dump[i] == 'I') {
            Node *right, *left;
            stack_pop(stack, &right);
            stack_pop(stack, &left);
            Node *parent = node_join(left, right);
            stack_push(stack, parent);
        }
    }
    // root of tree
    Node *root;
    stack_pop(stack, &root);
    stack_delete(&stack);
    return root;
}

// deletes a given tree
// returns nothing
//
// root: root of the tree
void delete_tree(Node **root) {
    if (*root) {
        delete_tree(&(*root)->left);
        delete_tree(&(*root)->right);
        node_delete(root);
    }
    return;
}
