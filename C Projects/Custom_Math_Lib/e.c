#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

// counter
static int terms = 0;

// approximates value of e using Taylor series
// returns approxination of e
//
// e: the double with the approximation
// preve: the double with the previous value of e
// prev: the double for computing factorial
double e() {
    double e = 1.0;
    double prev = 1.0;
    double preve = 0.0;
    // taylor series
    for (double k = 1.0; e - preve > EPSILON; k += 1.0) {
        terms++;
        prev *= k;
        preve = e;
        e += (1.0 / prev);
    }
    return e;
}

// counts how many terms were used in the approximation
// returns number of terms used
//
// terms: the int for terms used
int e_terms() {
    return terms;
}
