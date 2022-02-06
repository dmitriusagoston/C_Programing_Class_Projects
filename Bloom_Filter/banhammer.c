// Some code was taken from asgn7.pdf
// Written by Darrell Long
// code used: regex

#include "node.h"
#include "bv.h"
#include "parser.h"
#include "messages.h"
#include "bf.h"
#include "ht.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <regex.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>

#define OPTIONS "-hst:f:"
#define WORD    "[a-zA-Z0-P_'-]+"
// prints help message
// returns nothing
void help() {
    printf("SYNOPSIS\n");
    printf("  A word filtering program for the GPRSC.\n");
    printf("  Filters out and reports bad words parsed from stdin\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./banhammer [-hs] [-t size] [-f size]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -h             Pprogram usage and help.\n");
    printf("  -s             Print program statistics.\n");
    printf("  -t size        Specify hash table size (default: 2^16).\n");
    printf("  -f size        Specify Bloom filter size (default: 2^20).\n");
}

int main(int argc, char **argv) {
    // variables for cases
    int opt = 0;
    uint32_t htsize = pow(2, 16);
    uint32_t bfsize = pow(2, 20);
    bool stats = false;
    // parse through command line
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        // help statement
        case 'h': help(); return 0;
        // statistics printing
        case 's': stats = true; break;
        // specify size of hash table
        case 't': htsize = atoi(optarg); break;
        // specify size of bloom filter
        case 'f': bfsize = atoi(optarg); break;
        }
    }
    // initalizes the bloom filter and hash table
    BloomFilter *bf = bf_create(bfsize);
    HashTable *ht = ht_create(htsize);
    FILE *badspeak = fopen("badspeak.txt", "r");
    FILE *newspeak = fopen("newspeak.txt", "r");
    // populate the bloom filter
    do {
        char bad[256] = { 0 };
        fscanf(badspeak, "%s", bad);
        if (fgetc(badspeak) == EOF) {
            break;
        }
        bf_insert(bf, bad);
        ht_insert(ht, bad, NULL);
    } while (1);
    fclose(badspeak);
    // populate the hash table
    do {
        char old[256] = { 0 };
        char new[256] = { 0 };
        fscanf(newspeak, "%s %s", old, new);
        if (fgetc(newspeak) == EOF) {
            break;
        }
        bf_insert(bf, old);
        ht_insert(ht, old, new);
    } while (1);
    fclose(newspeak);
    // filtering words and parts taken from asgn7.pdf
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return -1;
    }
    char *word = NULL;
    // create binary search trees for words with and without translations
    Node *thoughtcrimes = bst_create();
    Node *oldspeak = bst_create();
    // parse through the user input
    while ((word = next_word(stdin, &re)) != NULL) {
        for (uint32_t i = 0; i < strlen(word); i++) {
            word[i] = tolower(word[i]);
        }
        if (bf_probe(bf, word)) {
            Node *bad = ht_lookup(ht, word);
            if (bad) {
                // case for no translation
                if (!bad->newspeak) {
                    thoughtcrimes = bst_insert(thoughtcrimes, word, NULL);
                    // case for newspeak translation
                } else if (bad->newspeak) {
                    oldspeak = bst_insert(oldspeak, word, bad->newspeak);
                }
            }
        }
    }
    // case for printing statistics and early termination
    if (stats) {
        printf("Average BST size: %.6f\n", ht_avg_bst_size(ht));
        printf("Average BST height: %.6f\n", ht_avg_bst_height(ht));
        printf("Average branches traversed: %.6f\n", (double) branches / lookups);
        printf("Hash table load: %.6f%%\n", 100 * ((double) ht_count(ht) / ht_size(ht)));
        printf("Bloom filter load: %.6f%%\n", 100 * ((double) bf_count(bf) / bf_size(bf)));
        return 0;
    }
    bool mixspeak = false;
    bool thoughtcrime = false;
    bool wrongthink = false;
    // no translation words only
    if (bst_size(thoughtcrimes) > 0) {
        thoughtcrime = true;
    }
    // words with translation only
    if (bst_size(oldspeak) > 0) {
        wrongthink = true;
    }
    // mix of both words with and without translation
    if (thoughtcrime && wrongthink) {
        mixspeak = true;
        thoughtcrime = false;
        wrongthink = false;
    }
    if (mixspeak) {
        printf("%s", mixspeak_message);
        bst_print(thoughtcrimes);
        bst_print(oldspeak);
    } else if (thoughtcrime) {
        printf("%s", badspeak_message);
        bst_print(thoughtcrimes);
    } else if (wrongthink) {
        printf("%s", goodspeak_message);
        bst_print(oldspeak);
    }
    // free memory
    clear_words();
    regfree(&re);
    bf_delete(&bf);
    ht_delete(&ht);
    bst_delete(&thoughtcrimes);
    bst_delete(&oldspeak);
    return 0;
}
