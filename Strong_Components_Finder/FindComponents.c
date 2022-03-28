//-----------------------------------------------------------------------------
// Dmitrius Agoston
// dagoston
// pa3
//
// FindComponents.c
// File for finding strong components
//-----------------------------------------------------------------------------
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
            fprintf(stderr, "Error: malformed arc.\n");
            return -1;
        }
        addArc(G, i, j);
    }
    List S = newList();
    for (int i = 1; i <= v; i++) {
        append(S, i);
    }
    fprintf(outfile, "Adjacency list representation of G:\n");
    printGraph(outfile, G);
    fprintf(outfile, "\n");
    Graph T = transpose(G);
    DFS(G, S);
    DFS(T, S);
    int count = 0;
    for (int i = 1; i <= getOrder(T); i++) {
        if (getParent(T, i) == 0) {
            count++;
        }
    }
    List temp = newList();
    moveBack(S);
    fprintf(outfile, "G contains %d strongly connected components:\n", count);
    for (int i = 1; i <= count; i++) {
        fprintf(outfile, "Component %d: ", i);
        while(1) {
            if (getParent(T, get(S)) == 0) {
                prepend(temp, get(S));
                movePrev(S);
                break;
            }
            prepend(temp, get(S));
            movePrev(S);
        }
        moveFront(temp);
        for (int i = 0; i < length(temp); i++) {
            fprintf(outfile, "%d ", get(temp));
            moveNext(temp);
        }
        clear(temp);
        fprintf(outfile, "\n");
    }
    freeList(&temp);
    freeGraph(&T);
    freeList(&S);
    freeGraph(&G);
    fclose(outfile);
    fclose(infile);
    return 0;
}
