#include "shell.h"

#include "stats.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// sorts a given array using shell sort
// returns nothing
//
// stats: the stats for the sort
// A: the array being sorted
// n: the size of the array
// gap: size of gap to be used
// i: index
// prev: previous element
// temp: temporary varaible
void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t gap = 0;
    // generate gaps
    for (uint32_t i = log(3 + 2 * n) / log(3); i > 0; i--) {
        gap = floor((pow(3, i) - 1) / 2);
        // sorts elemnts based on gap
        for (uint32_t k = gap; k < n; k++) {
            uint32_t prev = k;
            uint32_t temp = move(stats, A[k]);
            // checks for correct order
            while (prev >= gap && cmp(stats, temp, A[prev - gap]) == -1) {
                A[prev] = move(stats, A[prev - gap]);
                prev -= gap;
            }
            A[prev] = move(stats, temp);
        }
    }
}
