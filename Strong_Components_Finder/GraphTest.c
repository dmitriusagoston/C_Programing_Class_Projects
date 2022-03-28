//-----------------------------------------------------------------------------
// Dmitrius Agoston
// dagoston
// pa3
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
    List S = newList();
    for (int i = 1; i <= v; i++) {
        append(S, i);
    }
    for (int i = 1; i < v - 3; i++) {
        addEdge(G, i, i + 3);
        addEdge(G, i, i + 1);
        addArc(G, i + 3, i + 1);
        if (i % 5 == 0) {
            addEdge(G, 1, i);
        }
    }
    addArc(G, 1, 100);
    printGraph(stdout, G);
    DFS(G, S);
    printf("Order: %d\n", getOrder(G));
    printf("Size: %d\n", getSize(G));
    for (int i = 1; i <= v; i++) {
        printf("Parent of %d: %d\n", i, getParent(G, i));
    }
    for (int i = 1; i <= v; i++) {
        printf("Discover of %d: %d\n", i, getDiscover(G, i));
    }
    for (int i = 1; i <= v; i++) {
        printf("Finish of %d: %d\n", i, getFinish(G, i));
    }
    printList(stdout, S);
    Graph T = transpose(G);
    Graph C = copyGraph(G);
    printGraph(stdout, G);
    DFS(C, S);
    DFS(T, S);
    printf("Order: %d\n", getOrder(G));
    printf("Size: %d\n", getSize(G));
    for (int i = 1; i <= v; i++) {
        printf("Parent of %d: %d\n", i, getParent(C, i));
    }
    for (int i = 1; i <= v; i++) {
        printf("Discover of %d: %d\n", i, getDiscover(C, i));
    }
    for (int i = 1; i <= v; i++) {
        printf("Finish of %d: %d\n", i, getFinish(C, i));
    } 
    printGraph(stdout, G);
    printf("Order: %d\n", getOrder(G));
    printf("Size: %d\n", getSize(G));
    for (int i = 1; i <= v; i++) {
        printf("Parent of %d: %d\n", i, getParent(T, i));
    }
    for (int i = 1; i <= v; i++) {
        printf("Discover of %d: %d\n", i, getDiscover(T, i));
    }
    for (int i = 1; i <= v; i++) {
        printf("Finish of %d: %d\n", i, getFinish(T, i));
    } 
    printList(stdout, S);
    printf("\n");
    makeNull(G);
    printf("Order: %d\n", getOrder(G));
    printf("Size: %d\n", getSize(G));
    freeGraph(&C);
    freeGraph(&T);
    freeList(&S);
    freeGraph(&G);
    return 0;
}
