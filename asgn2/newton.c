#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

//counter
static int iters = 0;

// approximates value of a square root using Newton-Raphson method.
// returns approxination of square root with given value
//
// cursqrt: the double with the approximation
// prevsqrt: the double with the previous value of sqrt
double sqrt_newton(double num) {
    double prevsqrt = 0.0;
    double cursqrt = 1.0;
    //Square root
    while (absolute(cursqrt - prevsqrt) > EPSILON) {
        iters++;
        prevsqrt = cursqrt;
        cursqrt = 0.5 * (prevsqrt + num / prevsqrt);
    }
    return cursqrt;
}
// counts how many terms were used in the approximation
// returns number of iterations it took
//
// iters: the int for iterations completed
int sqrt_newton_iters() {
    int curiters = iters;
    iters = 0;
    return curiters;
}
