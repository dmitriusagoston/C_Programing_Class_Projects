#include "randstate.h"
#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>

gmp_randstate_t state;

// initalizes random state
// returns nothing
//
// seed: seed for random number generation
void randstate_init(uint64_t seed) {
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
    return;
}

// clears the random state
// returns nothing
void randstate_clear() {
    gmp_randclear(state);
    return;
}
