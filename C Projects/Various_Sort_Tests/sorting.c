#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define OPTIONS "-haeisqn:p:r:"

typedef enum { HEAP, INSERTION, SHELL, QUICK, END } Sorts;

// prints help statement
// returns nothing
void help() {
    printf("Select at least one sort to perform.\n");
    printf("SYNOPSIS\n");
    printf("    A collection of comparison-based sorting algorithms.\n\n");
    printf("USAGE\n");
    printf("    ./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n\n");
    printf("OPTIONS\n");
    printf("-h              display program help and usage.\n");
    printf("-a              enable all sorts.\n");
    printf("-e              enable Heap Sort.\n");
    printf("-i              enable Insertion Sort.\n");
    printf("-s              enable Shell Sort.\n");
    printf("-q              enable Quick Sort.\n");
    printf("-n length       specify number of array elements (default: 100).\n");
    printf("-p elements     specify number of elements to print (default: 100)\n");
    printf("-r seed         specify random seed (default: 13371453).\n");
}

// creates pseudo random array
// returns nothing
//
// stats: the stats for the sort
// arr: array for random numbers
// n: the size of the array
// seed: seed for random numbers
void make_array(uint32_t *arr, int seed, int size) {
    // sets seed
    srandom(seed);
    for (int i = 0; i < size; i++) {
        // bit masks array
        int mask = 0x3FFFFFFF;
        arr[i] = random() & mask;
    }
}

int main(int argc, char **argv) {
    int s = empty_set();
    int curoptarg;
    int opt = 0;
    int seed = 13371453;
    int size = 100;
    int elements = 100;
    bool help_switch = true;
    // get commands given
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        help_switch = false;
        if (opt == 114 || opt == 110 || opt == 112) {
            sscanf(optarg, "%d", &curoptarg);
        }
        switch (opt) {
        // run all tests
        case 'a':
            s = insert_set(HEAP, s);
            s = insert_set(INSERTION, s);
            s = insert_set(SHELL, s);
            s = insert_set(QUICK, s);
            break;
        // insert desired cases
        case 'e': s = insert_set(HEAP, s); break;
        case 'i': s = insert_set(INSERTION, s); break;
        case 's': s = insert_set(SHELL, s); break;
        case 'q': s = insert_set(QUICK, s); break;
        // set seed
        case 'r':
            if (curoptarg >= 0) {
                seed = curoptarg;
            }
            break;
        // set size
        case 'n':
            if (curoptarg >= 0) {
                size = curoptarg;
            }
            break;
        // set number of elements to be displayed
        case 'p':
            if (curoptarg >= 0) {
                elements = curoptarg;
            }
            break;
        // print help statement
        case 'h': help(); return 0;
        }
    }
    // case if no command given
    if (help_switch == true) {
        help();
        return 0;
    }
    // print all elements instead
    if (size < elements) {
        elements = size;
    }
    // dynamic memory allocation
    uint32_t *arr = (uint32_t *) calloc(size, sizeof(uint32_t));
    void (*sorts[])(Stats *, uint32_t *, uint32_t)
        = { heap_sort, insertion_sort, shell_sort, quick_sort };
    // runs tests
    for (Sorts curtest = HEAP; curtest < END; curtest += 1) {
        if (member_set(curtest, s)) {
            Stats stats;
            // ensure accurate stats for each test
            reset(&stats);
            make_array(arr, seed, size);
            sorts[curtest](&stats, arr, size);
            if (curtest == HEAP) {
                printf("Heap Sort, %d elements ", elements);
            } else if (curtest == INSERTION) {
                printf("Insertion Sort, %d elements ", elements);
            } else if (curtest == SHELL) {
                printf("Shell Sort, %d elements ", elements);
            } else if (curtest == QUICK) {
                printf("Quick Sort, %d elements ", elements);
            }
            printf("%lu moves, %lu compares\n", stats.moves, stats.compares);
            // display sort in correct format
            for (int i = 1; i <= elements; i++) {
                printf("%13" PRIu32, arr[i - 1]);
                if (i % 5 == 0) {
                    printf("\n");
                }
            }
        }
    }
    free(arr);
    printf("\n");
    return 0;
}
