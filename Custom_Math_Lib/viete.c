#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

//counter
static int terms = 0;

// approximates value of pi using Viete's formula
// returns approxination of pi
//
// viete: the double with the approximation of pi
// prevviete: the double with the previous value of viete
// roottwo: value for neststed square root
double pi_viete() {
    double viete = (sqrt_newton(2.0)) / 2.0;
    double prevviete = 0.0;
    double root_two = sqrt_newton(2.0);
    //Viete's Formula
    while (absolute(viete - prevviete) > EPSILON) {
        terms++;
        root_two = sqrt_newton(2.0 + root_two);
        prevviete = viete;
        viete *= root_two / 2.0;
    }
    //get pi by itself
    return 2.0 / viete;
}

// counts how many terms were used in the approximation
// returns number of terms used
//
// terms: the int for terms used
int pi_viete_factors() {
    return terms;
}
