#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

//counter
static int terms = 0;

// approximates value of pi using Bailey-Borwein-Plouffe formula
// returns approxination of pi
//
// bbp: the double with the approximation of pi
// prevbbp: the double with the previous value of bbp
// exp: the double with the exponential value of 16^k
// numer: temporary double for the numerator math
// denom: temporary double for the denominator math
double pi_bbp() {
    double bbp = 0.0;
    double prevbbp = -1.0;
    //Bailey-Borwein-Plouffe formula
    for (double k = 0.0; absolute(bbp - prevbbp) > EPSILON; k += 1.0) {
        terms++;
        prevbbp = bbp;
        double exp = 1.0;
        //exponetial loop
        for (int lcv = 0; lcv < k; lcv++) {
            exp *= 16.0;
        }
        //first case for 16^0
        if (k == 0.0) {
            exp = 1.0;
        }
        //numerator math
        double numer = k * (120.0 * k + 151.0) + 47.0;
        //denominator math
        double denom = k * (k * (k * (512.0 * k + 1024.0) + 712.0) + 194.0) + 15.0;
        //Horner normal form
        bbp += (1 / exp) * (numer / denom);
    }
    return bbp;
}

// counts how many terms were used in the approximation
// returns number of terms used
//
// terms: the int for terms used
int pi_bbp_terms() {
    return terms;
}
