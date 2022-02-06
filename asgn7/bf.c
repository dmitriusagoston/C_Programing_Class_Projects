#include "bf.h"
#include "salts.h"
#include "speck.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct BloomFilter BloomFilter;

// Definition of BloomFilter, a data structure used to test if an element is a member of a set
//
// primary: the primary salts to be hashed
// secondary: the secondary salts to be hashed
// tertiary: the tertiary salts to be hashed
// filter: the bit vector to be used as a filter
struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

// creates a new bloom filter
// returns the newly created bloom filter
//
// bf: newly created bloom filter
// size: the desired size of the bloom filter
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) calloc(1, sizeof(BloomFilter));
    if (bf) {
        bf->primary[0] = SALT_PRIMARY_LO;
        bf->primary[1] = SALT_PRIMARY_HI;
        bf->secondary[0] = SALT_SECONDARY_LO;
        bf->secondary[1] = SALT_SECONDARY_HI;
        bf->tertiary[0] = SALT_TERTIARY_LO;
        bf->tertiary[1] = SALT_TERTIARY_HI;
        bf->filter = bv_create(size);
    }
    return bf;
}

// deletes a given bloom filter
// returns nothing
//
// bf: the given bloom filter
void bf_delete(BloomFilter **bf) {
    bv_delete(&(*bf)->filter);
    free(*bf);
    *bf = NULL;
    return;
}

// gets the size of a given bloom filter
// returns the size of the bloom filter
//
// bf: the given bloom filter
uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

// inserts a desired oldspeak word into the bloom filter
// returns nothing
//
// bf: the given bloom filter
// oldspeak: the oldspeak word to be inserted
void bf_insert(BloomFilter *bf, char *oldspeak) {
    uint32_t hash_primary = hash(bf->primary, oldspeak) % bf_size(bf);
    uint32_t hash_secondary = hash(bf->secondary, oldspeak) % bf_size(bf);
    uint32_t hash_tertiary = hash(bf->tertiary, oldspeak) % bf_size(bf);
    bv_set_bit(bf->filter, hash_primary);
    bv_set_bit(bf->filter, hash_secondary);
    bv_set_bit(bf->filter, hash_tertiary);
    return;
}

// probes the bloom filter for a desired oldspeak word
// returns true if found and false otherwise
//
// bf: the given bloom filter
// oldspeak: the oldspeak word to be probed for
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint32_t hash_primary = hash(bf->primary, oldspeak) % bf_size(bf);
    uint32_t hash_secondary = hash(bf->secondary, oldspeak) % bf_size(bf);
    uint32_t hash_tertiary = hash(bf->tertiary, oldspeak) % bf_size(bf);
    if (bv_get_bit(bf->filter, hash_primary) && bv_get_bit(bf->filter, hash_secondary)
        && bv_get_bit(bf->filter, hash_tertiary)) {
        return true;
    }
    return false;
}

// counts the number of set bits in the bloom filter
// returns the number of set bits
//
// bf: the given bloom filter
uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        if (bv_get_bit(bf->filter, i)) {
            count++;
        }
    }
    return count;
}

// prints the given bloom filter
// returns nothing
//
// bf: the given bloom filter
void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
    return;
}
