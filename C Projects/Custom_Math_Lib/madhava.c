#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

// counter
static int terms = 0;

// approximates value of pi using Madhava series
// returns approxination of pi
//
// curpi: the double with the approximation
// prevpi: the double with the previous value of e
// numerator: value to grow exponetially
// factor: control for exponetial growth
// multby: holder for sqrt(12) value
double pi_madhava() {
    double curpi = 1.0;
    double prevpi = 0.0;
    // Madhava Series
    for (double k = 1.0; absolute(curpi - prevpi) > EPSILON; k += 1.0) {
        terms++;
        prevpi = curpi;
        double numerator = -3.0;
        double factor = -3.0;
        // exponential loop
        for (int lcv = 1.0; lcv < k; lcv++) {
            numerator *= factor;
        }
        curpi += (1.0 / numerator) / (2.0 * k + 1.0);
    }
    double multby = sqrt_newton(12);
    // multiply final result by root 12
    curpi *= multby;
    return curpi;
}

// counts how many terms were used in the approximation
// returns number of terms used
//
// terms: the int for terms used
int pi_madhava_terms() {
    return terms;
}
