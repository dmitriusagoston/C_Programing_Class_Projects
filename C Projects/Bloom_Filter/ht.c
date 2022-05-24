#include "ht.h"
#include "bst.h"
#include "salts.h"
#include "speck.h"
#include <stdlib.h>
#include <stdio.h>

uint64_t lookups = 0;

typedef struct HashTable HashTable;

// Definition of HashTable, a data structure used to map keys to values
//
// salt: the salt being used in hashing
// size: the desired size of the hash table
// trees: the binary search trees of the hash table
struct HashTable {
    uint64_t salt[2];
    uint64_t size;
    Node **trees;
};

// creates a new hash table
// returns the newly created hash table
//
// ht: newly created hash table
// size: the desired size of the hash table
HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) calloc(1, sizeof(HashTable));
    if (ht) {
        ht->size = size;
        ht->salt[0] = SALT_HASHTABLE_LO;
        ht->salt[1] = SALT_HASHTABLE_HI;
        ht->trees = (Node **) calloc(size, sizeof(Node *));
        if (!ht->trees) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

// prints the given hash table
// returns nothing
//
// ht: the desired hash table
void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->trees[i]) {
            bst_print(ht->trees[i]);
        }
    }
    return;
}

// deletes the given hash table
// returns nothing
//
// ht: the desired hash table
void ht_delete(HashTable **ht) {
    if ((*ht)->trees) {
        for (uint32_t i = 0; i < ht_size(*ht); i++) {
            bst_delete(&(*ht)->trees[i]);
        }
        free((*ht)->trees);
    }
    free(*ht);
    *ht = NULL;
    return;
}

// gets the size of the given hash table
// returns the size of the hash table
//
// ht: the desired hash table
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

// looks up the key which is the desired oldspeak word in the hash table
// returns the node of the oldspeak word
//
// ht: the desired hash table
// oldspeak: the desired oldspeak word
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    lookups++;
    uint32_t i = hash(ht->salt, oldspeak) % ht->size;
    return bst_find(ht->trees[i], oldspeak);
}

// inserts an oldspeak word into the hash table with its coresponding translation
// returns nothing
//
// ht: the desired hash table
// oldspeak: the desired oldspeak word to add
// newspeak: the translation of the desired oldspeak word
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    lookups++;
    uint32_t i = hash(ht->salt, oldspeak) % ht->size;
    ht->trees[i] = bst_insert(ht->trees[i], oldspeak, newspeak);
    return;
}

// finds the number of non NULL binary search trees in the hash table
// returns the count of non NULL binary search trees
//
// ht: the desired hash table
uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->trees[i]) {
            count++;
        }
    }
    return count;
}

// gets the average binary search tree size
// returns the average size of binary search trees in the hash table
//
// ht: the desired hash table
double ht_avg_bst_size(HashTable *ht) {
    uint32_t sum = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->trees[i]) {
            sum += bst_size(ht->trees[i]);
        }
    }
    uint32_t div = ht_count(ht);
    return (double) sum / div;
}

// gets the average binary search tree height
// returns the average height of binary search trees in the hash table
//
// ht: the desired hash table
double ht_avg_bst_height(HashTable *ht) {
    uint32_t sum = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->trees[i]) {
            sum += bst_height(ht->trees[i]);
        }
    }
    uint32_t div = ht_count(ht);
    return (double) sum / div;
}
