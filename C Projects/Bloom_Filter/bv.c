#include "bv.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct BitVector BitVector;

// Definition of BitVector, a structure used to efficently store bits in vectors
//
// length: the amount the bit vector can store
// vector: the vectors being used to store bits
struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

// creates a bit vector
// returns the newly created bit vector
//
// bv: newly created bit vector
// length: length in bits of the bit vector
BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) calloc(1, sizeof(BitVector));
    if (bv) {
        bv->length = length;
        bv->vector = (uint8_t *) calloc(length, sizeof(uint8_t));
        if (!bv->vector) {
            free(bv);
            bv = NULL;
        }
    }
    return bv;
}

// deletes a bit vector
// returns nothing
//
// bv: bit vector being deleted
void bv_delete(BitVector **bv) {
    free((*bv)->vector);
    free(*bv);
    *bv = NULL;
    return;
}

// gets the length of the bit vector
// returns the length of the bit vector
//
// bv: bit vector
uint32_t bv_length(BitVector *bv) {
    return (bv->length);
}

// sets a bit in the bit vector to a desired bit
// returns true or false if bit was set
//
// bv: current bit vector
// i: index of bit
bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (i <= bv->length) {
        int temp = i % 8;
        uint8_t bit = 1;
        bit = bit << temp;
        bv->vector[i / 8] = bv->vector[i / 8] | bit;
        return true;
    }
    return false;
}

// clear a desired bit in the bit vector
// returns true or false if bit was cleared
//
// bv: current bit vector
// i: index of bit
bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (i <= bv->length) {
        int temp = i % 8;
        uint8_t bit = 1;
        bit = bit << temp;
        bit = ~bit;
        bv->vector[i / 8] = bv->vector[i / 8] & bit;
        return true;
    }
    return false;
}

// gets a desired bit in the bit vector
// returns true or false if bit was got
//
// bv: current bit vector
// i: index of bit
bool bv_get_bit(BitVector *bv, uint32_t i) {
    if (i < bv->length) {
        int temp = i % 8;
        uint8_t bit = 1;
        bit = bit << temp;
        uint8_t temp_bit = bv->vector[i / 8];
        if ((temp_bit & bit) == bit) {
            return true;
        }
    }
    return false;
}

// prints given bit vector
// returns nothing
//
// bv: current bit vector
void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv->length; i++) {
        printf("index:%u bit:%u", i, bv->vector[i]);
    }
}
