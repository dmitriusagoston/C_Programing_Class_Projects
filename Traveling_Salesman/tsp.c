#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OPTIONS "-hvui:o:"

static uint32_t count = 0;

// prints the help statement
// returns nothing
void help() {
    printf("SYNOPSIS\n");
    printf("  Traveling Salesman Problem using DFS.\n\n");
    printf("USAGE\n");
    printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n");
    printf("OPTIONS\n");
    printf("  -u             Use undirected graph.\n");
    printf("  -v             Enable verbose printing.\n");
    printf("  -h             Program usage and help.\n");
    printf("  -i infile      Input containing graph (default: stdin)\n");
    printf("  -o outfile     Output of computed path (default: stdout)\n");
}

// depth-first search
// returns nothing
//
// G: graph to search
// cur: current path
// best: shortest path
// cities: names of vertices
// outfile: file to print paths to
// ver: determines if verbose printing or not
// count: number of recursive calls
// temp: temporary variable
// i: index
void dfs(Graph *G, uint32_t v, Path *cur, Path *best, char *cities[], FILE *outfile, bool ver) {
    // incremenet recursive calls for each call
    count++;
    // mark visited and add to stack
    graph_mark_visited(G, v);
    path_push_vertex(cur, v, G);
    // check if current path is longer than best path to stop unecessary recursion
    if (path_length(cur) >= path_length(best) && path_length(best) != 0) {
        graph_mark_unvisited(G, v);
        path_pop_vertex(cur, &v, G);
        return;
    }
    // check if path needs to go back to origin vertex
    if (path_vertices(cur) == graph_vertices(G)) {
        if (path_push_vertex(cur, 0, G) == true) {
            // check for verbose printing
            if (ver == true) {
                path_print(cur, outfile, cities);
            }
            uint32_t temp = 0;
            // check if current path is shortest path
            if (path_length(cur) <= path_length(best) || path_length(best) == 0) {
                path_copy(best, cur);
            }
            path_pop_vertex(cur, &temp, G);
        }
    }
    // loop through adjacent edges
    for (uint32_t i = 0; i < graph_vertices(G); i++) {
        if (graph_visited(G, i) == false && graph_has_edge(G, v, i)) {
            dfs(G, i, cur, best, cities, outfile, ver);
        }
    }
    // for backtracking
    graph_mark_unvisited(G, v);
    path_pop_vertex(cur, &v, G);
}

int main(int argc, char **argv) {
    // variables for cases
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    bool verbose = false;
    bool undir = false;
    bool need_input = true;
    char line[256];
    uint32_t vertices = 0;
    // parse through command line
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        // help statement
        case 'h': help(); return 0;
        // verbose printing
        case 'v': verbose = true; break;
        // undirected graph
        case 'u': undir = true; break;
        // infile to read from
        case 'i':
            if ((infile = fopen(optarg, "r")) == NULL) {
                printf("Error: failed to open infile\n");
                return -1;
            } else {
                infile = fopen(optarg, "r");
                break;
            }
        // outfile to write to
        case 'o':
            if ((outfile = fopen(optarg, "w")) == NULL) {
                printf("Error: failed to open outfile\n");
                return -1;
            } else {
                outfile = fopen(optarg, "w");
                break;
            }
        }
    }
    // check if file failed to open
    if (need_input == false && undir == true) {
        printf("Error: failed to open infile");
        return -1;
    }
    // getting number of verticies
    fgets(line, sizeof(line), infile);
    line[strlen(line) - 1] = '\0';
    vertices = atoi(line);
    // check for malformed number of vertices
    if (vertices > VERTICES) {
        printf("Error: malformed number of vertices\n");
        return -1;
    }
    // check for only 1 vertex
    if (vertices == 1) {
        printf("There's nowhere to go");
        return -1;
    }
    // create graph and array for vertices
    Graph *graph = graph_create(vertices, undir);
    char *cities[vertices];
    // add names for vertices
    for (uint32_t i = 0; i < vertices; i++) {
        fgets(line, sizeof(line), infile);
        line[strlen(line) - 1] = '\0';
        cities[i] = strdup(line);
    }
    // get edges
    do {
        line[strlen(line) - 1] = '\0';
        uint32_t i = 0, j = 0, k = 0;
        fscanf(infile, "%u %u %u", &i, &j, &k);
        // stop reading if end of file
        if (fgetc(infile) == EOF) {
            break;
        }
        // check for malformed edge
        if (graph_add_edge(graph, i, j, k) == false && (k < 0 || i > VERTICES || j > VERTICES)) {
            printf("Error: malformed edge.\n");
            return -1;
        }
    } while (1);
    // close file being read
    fclose(infile);
    // search and find best path
    Path *cur_path = path_create();
    Path *best_path = path_create();
    dfs(graph, 0, cur_path, best_path, cities, outfile, verbose);
    // check for no path
    if (path_length(best_path) == 0) {
        printf("No Hamiltonian path found.");
    } else {
        path_print(best_path, outfile, cities);
    }
    printf("Total recursive calls: %u\n", count);
    // free memory used
    for (uint32_t i = 0; i < vertices; i++) {
        free(cities[i]);
    }
    graph_delete(&graph);
    path_delete(&cur_path);
    path_delete(&best_path);
    return 0;
}
