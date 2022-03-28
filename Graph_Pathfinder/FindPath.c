#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char** argv) {
    FILE *infile = NULL;
    FILE *outfile = NULL;
    if (argc != 3) {
        fprintf(stderr, "USAGE: ./FindPath [infile] [outfile]\n");
        return -1;
    }
    if ((infile = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error: failed to open infile\n");
        return -1;
    }
    if ((outfile = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "Error: failed to open outfile\n");
        fclose(infile);
        return -1;
    }
    int v = 0;
    fscanf(infile, "%d", &v);
    Graph G = newGraph(v);
    fgetc(infile);
    while(1) {
        int i = 0, j = 0;
        fscanf(infile, "%d %d", &i, &j);
        if (i == 0 && j == 0) {
            break;
        }
        if (i > v || j > v || i < 1 || j < 1) {
            fprintf(stderr, "Error: malformed edge.\n");
            return -1;
        }
        addEdge(G, i, j);
    }
    printGraph(outfile, G);
    List paths = newList();
    fprintf(outfile, "\n");
    while(1) {
        int i = 0, j = 0;
        fscanf(infile, "%d %d", &i, &j);
        if (i == 0 && j == 0) {
            break;
        }
        if (i > v || j > v || i < 1 || j < 1) {
            fprintf(stderr, "Error: malformed edge.\n");
            return -1;
        }
        BFS(G, i);
        getPath(paths, G, j);
        fprintf(outfile, "The distance from %d to %d is ", i, j);
        if (getDist(G, j) < 0) {
            fprintf(outfile, "infinity\n");
            fprintf(outfile, "No %d-%d path exists\n\n", i, j);
            clear(paths);
            continue;
        } else {
            fprintf(outfile, "%d\n", getDist(G, j));
        }
        fprintf(outfile, "A shortest %d-%d path is: ", i, j);
        printList(outfile, paths);
        fprintf(outfile, "\n\n");
        clear(paths);
    }
    freeList(&paths);
    freeGraph(&G);
    fclose(outfile);
    fclose(infile);
    return 0;
}
