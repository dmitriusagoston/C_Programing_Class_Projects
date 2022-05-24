#include "code.h"
#include "defines.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// creates a new code
// returns the newly created code
//
// code: newly created code
// top: top of the code
// bits: bits of the code
Code code_init() {
    Code code;
    code.top = 0;
    for (uint32_t i = 0; i < MAX_CODE_SIZE; i++) {
        code.bits[i] = 0;
    }
    return code;
}

// gets the current size of the code
// returns the size of the code
//
// c: current code
uint32_t code_size(Code *c) {
    return (c->top);
}

// determines if the code is empty
// returns true or false if the code is empty
//
// c: current code
bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    }
    return false;
}

// determines if the code is full
// returns true or false if the code is full
//
// c: current code
bool code_full(Code *c) {
    if (c->top == ALPHABET) {
        return true;
    }
    return false;
}

// sets a bit in the code to a desired bit
// returns true or false if bit was set
//
// c: current code
// i: index of bit
bool code_set_bit(Code *c, uint32_t i) {
    if (i <= ALPHABET) {
        int temp = i % 8;
        uint8_t bit = 1;
        bit = bit << temp;
        c->bits[i / 8] = c->bits[i / 8] | bit;
        return true;
    }
    return false;
}

// clear a desired bit in the code
// returns true or false if bit was cleared
//
// c: current code
// i: index of bit
bool code_clr_bit(Code *c, uint32_t i) {
    if (i <= ALPHABET) {
        int temp = i % 8;
        uint8_t bit = 1;
        bit = bit << temp;
        bit = ~bit;
        c->bits[i / 8] = c->bits[i / 8] & bit;
        return true;
    }
    return false;
}

// gets a desired bit in the code
// returns true or false if bit was got
//
// c: current code
// i: index of bit
bool code_get_bit(Code *c, uint32_t i) {
    if (i < ALPHABET) {
        int temp = i % 8;
        uint8_t bit = 1;
        bit = bit << temp;
        uint8_t temp_bit = c->bits[i / 8];
        if ((temp_bit & bit) == bit) {
            return true;
        }
    }
    return false;
}

// pushes a desired bit in the code
// returns true or false if bit was pushed
//
// c: current code
// bit: bit being pushed
bool code_push_bit(Code *c, uint8_t bit) {
    if (!code_full(c)) {
        if (bit == 0) {
            code_clr_bit(c, c->top);
        } else {
            code_set_bit(c, c->top);
        }
        c->top++;
        return true;
    }
    return false;
}

// pops a desired bit from the code
// returns true or false if bit was popped
//
// c: current code
// bit: bit being popped
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (!code_empty(c)) {
        c->top--;
        if (code_get_bit(c, c->top) == 0) {
            *bit = 0;
        } else {
            *bit = 1;
        }
        code_clr_bit(c, c->top);
        return true;
    }
    return false;
}

// prints given code
// returns nothing
//
// c: current code
void code_print(Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        printf("index:%u bit:%u", i, c->bits[i]);
    }
}
