#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

//counter
static int terms = 0;

// approximates value of pi using Madhava series
// returns approxination of pi
//
// curpi: the double with the approximation
// prevpi: the double with the previous value of e
// numerator: value to grow exponetially
// factor: control for exponetial growth
// multby: holder for sqrt(12) value
double pi_euler() {
    double euler = 1.0;
    double preveuler = 0.0;
    //Euler's solution
    for (double k = 2.0; absolute(euler - preveuler) > EPSILON; k += 1.0) {
        terms++;
        preveuler = euler;
        double temp = k * k;
        euler += (1.0 / temp);
    }
    //multiply by 6 and square root final number
    euler *= 6;
    return sqrt_newton(euler);
}

// counts how many terms were used in the approximation
// returns number of terms used
//
// terms: the int for terms used
int pi_euler_terms() {
    return terms;
}
