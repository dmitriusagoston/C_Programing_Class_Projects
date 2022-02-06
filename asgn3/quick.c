#include "quick.h"

#include "stats.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// sorts a given array using a pivot point and two sub arrays
// returns a pivot point
//
// stats: the stats for the sort
// lo: low of the array (initially 1)
// hi: high of the array (initially the original size of the array)
// i: array index
uint32_t partition(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    uint32_t i = lo - 1;
    // go through array
    for (uint32_t j = lo; j < hi; j++) {
        // sorts based on low and high
        if (cmp(stats, A[j - 1], A[hi - 1]) == -1) {
            i += 1;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }
    swap(stats, &A[i], &A[hi - 1]);
    return i + 1;
}

// sorts a given array using a pivot point and two sub arrays
// returns nothing
//
// stats: the stats for the sort
// lo: low of the array (initially 1)
// hi: high of the array (initially the original size of the array)
// p: variable for partioning array and pivot
void quick_sorter(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    if (lo < hi) {
        // pivot
        uint32_t p = partition(stats, A, lo, hi);
        quick_sorter(stats, A, lo, p - 1);
        quick_sorter(stats, A, p + 1, hi);
    }
}

// sorts a given array using quick sorter
// returns nothing
//
// stats: the stats for the sort
// A: the array being sorted
// n: the size of the array
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
}
