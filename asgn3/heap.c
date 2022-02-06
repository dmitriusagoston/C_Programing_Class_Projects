#include "heap.h"

#include "stats.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// finds max child of array
// returns max child
//
// stats: the stats for the sort
// A: the array being sorted
// first: first element
// last: last elemnet
// left: left element
// right: right element
uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    // checks if right is larger
    if (right <= last && cmp(stats, A[right - 1], A[left - 1]) == 1) {
        return right;
    }
    // left was larger
    return left;
}

// fixes the heap
// returns nothing
//
// stats: the stats for the sort
// A: the array being sorted
// first: first element
// last: last elemnet
// mother: first element
// great: max child of mother
void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first;
    uint32_t great = max_child(stats, A, mother, last);
    while (mother <= floor(last / 2) && found != true) {
        // checks if child is bigger
        if (cmp(stats, A[mother - 1], A[great - 1]) == -1) {
            swap(stats, &A[mother - 1], &A[great - 1]);
            mother = great;
            great = max_child(stats, A, mother, last);
        } else {
            found = true;
        }
    }
}

// builds the heap
// returns nothing
//
// stats: the stats for the sort
// A: the array being sorted
// first: first element
// last: last elemnet
// father: root of heap
void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t father = floor(last / 2); father > first - 1; father--) {
        fix_heap(stats, A, father, last);
    }
}

// sorts a given array using heap sort
// returns nothing
//
// stats: the stats for the sort
// A: the array being sorted
// n: the size of the array
// first: first element
// last: last elemnet
// prev: previous element
// leaf: used to create "leafs" for the arrary
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(stats, A, first, last);
    // creates leafs
    for (uint32_t leaf = last; leaf > first; leaf--) {
        swap(stats, &A[first - 1], &A[leaf - 1]);
        fix_heap(stats, A, first, leaf - 1);
    }
}
