#include "node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node Node;

// creates a new node
// returns newly created node
//
// n: new node being created
// oldspeak: the prohibited old word
// newspeak: the coresponding translation if applicable
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) calloc(1, sizeof(Node));
    if (n) {
        char *temp_old = strdup(oldspeak);
        n->oldspeak = temp_old;
        if (newspeak) {
            char *temp_new = strdup(newspeak);
            n->newspeak = temp_new;
        } else {
            n->newspeak = NULL;
        }
    }
    return n;
}

// deletes a node
// returns nothing
//
// n: current node
void node_delete(Node **n) {
    free((*n)->oldspeak);
    free((*n)->newspeak);
    free(*n);
    *n = NULL;
    return;
}

// prints the given node
// returns nothing
//
// n: node being printed
void node_print(Node *n) {
    if (n->newspeak) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    } else {
        printf("%s\n", n->oldspeak);
    }
    return;
}
