//-----------------------------------------------------------------------------
// Dmitrius Agoston
// dagoston
// pa1
//
// GraphTest.c
// Test Harness for Graph ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

int main() {
    int v = 100;
    Graph G = newGraph(v);
    List L = newList();
    for (int i = 1; i < v - 3; i++) {
        addEdge(G, i, i + 3);
        addEdge(G, i, i + 1);
        if (i % 5 == 0) {
            addEdge(G, 1, i);
        }
    }
    addArc(G, 1, 100);
    printGraph(stdout, G);
    BFS(G, 1);
    printf("Order: %d\n", getOrder(G));
    printf("Size: %d\n", getSize(G));
    printf("Source: %d\n", getSource(G));
    printf("Distance from 1 to 73: %d\n", getDist(G, 73));
    printf("Distance from 1 to 75: %d\n", getDist(G, 75));
    printf("Distance from 1 to 1: %d\n", getDist(G, 1));
    printf("Parent of 3: %d\n", getParent(G, 3));
    getPath(L, G, 79);
    printList(stdout, L);
    printf("\n");
    makeNull(G);
    printf("Order: %d\n", getOrder(G));
    printf("Size: %d\n", getSize(G));
    printf("Source: %d\n", getSource(G));
    freeList(&L);
    freeGraph(&G);
    return 0;
}
