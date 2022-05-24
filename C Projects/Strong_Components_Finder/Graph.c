//-----------------------------------------------------------------------------
// Dmitrius Agoston
// dagoston
// pa3
//
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"
#include "Graph.h"

// structs --------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj{
	List *vertices;
	int *colors;
	int *parents;
	int *discoveries;
    int *finishes;
	int order;
	int size;
} GraphObj;

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns reference to new empty Graph object. 
Graph newGraph(int n) {
	Graph G;
	G = malloc(sizeof(GraphObj));
    G->order = n;
    G->size = 0;
    G->vertices = malloc(sizeof(List) * (n + 1));
    G->colors = malloc(sizeof(int) * (n + 1));
    G->parents = malloc(sizeof(int) * (n + 1));
    G->discoveries = malloc(sizeof(int) * (n + 1));
    G->finishes = malloc(sizeof(int) * (n + 1));
    for (int i = 1; i <= G->order; i++) {
        G->vertices[i] = newList();
    }
    for (int i = 1; i <= G->order; i++) {
        G->parents[i] = NIL;
    }
    for (int i = 1; i <= G->order; i++) {
        G->discoveries[i] = UNDEF;
    }
    for (int i = 1; i <= G->order; i++) {
        G->finishes[i] = UNDEF;
    }
	return G;
}

// freeGraph()
// Frees all heap memory associated with Graph *pG, and sets *pG to NULL.
void freeGraph(Graph* pG) {
	if (pG != NULL && *pG != NULL) {
		// don't make list for 0
		for (int i = 1; i <= (*pG)->order; i++) {
			freeList(&(*pG)->vertices[i]);
		}
        free((*pG)->finishes);
        free((*pG)->discoveries);
        free((*pG)->parents);
        free((*pG)->colors);
        free((*pG)->vertices);
		free(*pG);
		*pG = NULL;
	}
	return;
}


// Access functions -----------------------------------------------------------

// getOrder()
// Returns the order of G
int getOrder(Graph G){
    if(G == NULL) {
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

// getSize()
// Returns the size of G.
int getSize(Graph G) {
    if(G == NULL) {
        printf("Graph Error: calling getSize() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
	return G->size;
}

// getParent()
// Returns the parent vertex of u in the Depth First tree or NIL.
// Pre: 1 <= u <= n = getOrder(G)
int getParent(Graph G, int u) {
    if(G == NULL) {
        printf("Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    int n = getOrder(G);
	if(u < 1 || u > n) {
        printf("Graph Error: calling getParent() on invalid Graph index\n");
        exit(EXIT_FAILURE);
    }
	return G->parents[u];
}

// getDiscover()
// Returns the discovery time of u in the Depth First tree or NIL.
// Pre: 1 <= u <= n = getOrder(G)
int getDiscover(Graph G, int u) {
    if(G == NULL) {
        printf("Graph Error: calling getDiscovery() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    int n = getOrder(G);
	if(u < 1 || u > n) {
        printf("Graph Error: calling getDiscovery() on invalid Graph index\n");
        exit(EXIT_FAILURE);
    }
	return G->discoveries[u];
}

// getFinish()
// Returns the finish time of u in the Depth First tree or NIL.
// Pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u) {
    if(G == NULL) {
        printf("Graph Error: calling getFinish() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    int n = getOrder(G);
	if(u < 1 || u > n) {
        printf("Graph Error: calling getFinish() on invalid Graph index\n");
        exit(EXIT_FAILURE);
    }
	return G->finishes[u];
}

// Manipulation procedures ----------------------------------------------------

// makeNull()
// deletes all edges of G and restores G to original state.
void makeNull(Graph G) {
    if(G == NULL) {
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
	for (int i = 1; i <= G->order; i++) {
		clear(G->vertices[i]);
	}
    G->size = 0;
	return;
}

// addEdge()
// inserts a new edge joining u to v.
// Pre: 1 <= u <= n = getOrder(G), 1 <= v <= n
void addEdge(Graph G, int u, int v) {
    if(G == NULL) {
        printf("Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    int n = getOrder(G);
	if(u < 1 || u > n) {
        printf("Graph Error: calling addEdge() on invalid Graph index(u)\n");
        exit(EXIT_FAILURE);
    }
	if(v < 1 || v > n) {
        printf("Graph Error: calling addEdge() on invalid Graph index(v)\n");
        exit(EXIT_FAILURE);
    }
	addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
	return;
}

// addArc()
// inserts a new directed edge from u to v.
// Pre: 1 <= u <= n = getOrder(G), 1 <= v <= n
void addArc(Graph G, int u, int v) {
    if(G == NULL) {
        printf("Graph Error: calling addArc() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    int n = getOrder(G);
	if(u < 1 || u > n) {
        printf("Graph Error: calling addArc() on invalid Graph index(u)\n");
        exit(EXIT_FAILURE);
    }
	if(v < 1 || v > n) {
        printf("Graph Error: calling addArc() on invalid Graph index(v)\n");
        exit(EXIT_FAILURE);
    }
    // repeats
    moveFront(G->vertices[u]);
    for (int i = 0; i < length(G->vertices[u]); i++) {
        if (v == get(G->vertices[u])) {
            return;
        }
        moveNext(G->vertices[u]);
    }
    G->size++;
    if(length(G->vertices[u]) == 0) {
        append(G->vertices[u], v);
        return;
    }
    moveBack(G->vertices[u]);
    if (v >= get(G->vertices[u])) {
        append(G->vertices[u], v);
        return;
    }
    moveFront(G->vertices[u]);
    for (int i = 0; i < length(G->vertices[u]); i++) {
        if (v < get(G->vertices[u])) {
            insertBefore(G->vertices[u], v);
            return;
        }
        moveNext(G->vertices[u]);
    }
	return;
}

// visit()
// visit function for DFS algorithm
void visit(Graph G, List S, int i, int *time) {
    G->discoveries[i] = ++(*time);
    G->colors[i] = GREY;
    moveFront(G->vertices[i]);
    for (int j = 0; j < length(G->vertices[i]); j++) {
        int adj = get(G->vertices[i]);
        if (G->colors[adj] == WHITE) {
            G->parents[adj] = i;
            visit(G, S, adj, time);
        }
        moveNext(G->vertices[i]);
    }
    G->colors[i] = BLACK;
    G->finishes[i] = ++(*time);
    prepend(S, i);
    return;
}

// DFS()
// runs the DFS algorithm on the Graph G.
// Pre: length(S) == getOrder(G)
void DFS(Graph G, List S) {
    if (G == NULL) {
        printf("Graph Error: calling DFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(S) != getOrder(G)) {
        printf("Graph Error: calling DFS() with invalid preconditions\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i++) {
        G->colors[i] = WHITE;
        G->parents[i] = NIL;
        G->discoveries[i] = UNDEF;
        G->finishes[i] = UNDEF;
    }
    List copy = copyList(S);
    clear(S);
    int time = 0;
    moveFront(copy);
    for (int i = 0; i < length(copy); i++) {
        int cur = get(copy);
        if (G->colors[cur] == WHITE) {
            visit(G, S, cur, &time);
        }
        moveNext(copy);
    }
    freeList(&copy);
    return;
}

// Other operations ------------------------------------------------------------

// transpose()
// returns a reference to a new graph that is a copy of G transposed.
Graph transpose(Graph G) {
    if(G == NULL) {
        printf("Graph Error: calling transpose() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    Graph copy = newGraph(getOrder(G));
	for (int i = 1; i <= G->order; i++) {
        moveFront(G->vertices[i]);
        for (int j = 0; j < length(G->vertices[i]); j++) {
            addArc(copy, get(G->vertices[i]), i);
            moveNext(G->vertices[i]);
        }
	}
	return copy;
}

// copyGraph()
// returns a reference to a new graph that is a copy of G.
Graph copyGraph(Graph G) {
    if(G == NULL) {
        printf("Graph Error: calling copyGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    Graph copy = newGraph(getOrder(G));
	for (int i = 1; i <= G->order; i++) {
        moveFront(G->vertices[i]);
        for (int j = 0; j < length(G->vertices[i]); j++) {
            addArc(copy, i, get(G->vertices[i]));
            moveNext(G->vertices[i]);
        }
	}
	return copy;
}

// printGraph()
// prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G) {
    if(G == NULL) {
        printf("Graph Error: calling printGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
	for (int i = 1; i <= G->order; i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->vertices[i]); 
		fprintf(out, "\n");
	}
	return;
}
