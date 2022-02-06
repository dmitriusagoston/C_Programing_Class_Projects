#include "insert.h"

#include "stats.h"

#include <stdio.h>
#include <stdlib.h>

// sorts a given array using insertion sort
// returns nothing
//
// stats: the stats for the sort
// A: the array being sorted
// n: the size of the array
// i: index
// lcv: loop control variable
void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t i = 1; i < n; i++) {
        uint32_t lcv = i;
        uint32_t temp = move(stats, A[i]);
        // checks if in correct position
        while (lcv > 0 && cmp(stats, temp, A[lcv - 1]) == -1) {
            A[lcv] = move(stats, A[lcv - 1]);
            lcv -= 1;
        }
        A[lcv] = move(stats, temp);
    }
}
