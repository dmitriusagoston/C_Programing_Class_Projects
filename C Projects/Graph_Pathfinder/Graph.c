//-----------------------------------------------------------------------------
// Dmitrius Agoston
// dagoston
// pa1
//
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Graph.h"
#include "List.h"

// structs --------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj{
	List *vertices;
	int *colors;
	int *parents;
	int *distance;
	int order;
	int size;
	int source;
} GraphObj;

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns reference to new empty Graph object. 
Graph newGraph(int n) {
	Graph G;
	G = malloc(sizeof(GraphObj));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    G->vertices = malloc(sizeof(List) * (n + 1));
    G->colors = malloc(sizeof(int) * (n + 1));
    G->parents = malloc(sizeof(int) * (n + 1));
    G->distance = malloc(sizeof(int) * (n + 1));
    for (int i = 1; i <= G->order; i++) {
        G->vertices[i] = newList();
    }
    for (int i = 1; i <= G->order; i++) {
        G->parents[i] = NIL;
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
        free((*pG)->distance);
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

// getSource()
// Returns the source vertex most recently used in BFS() or NIL.
int getSource(Graph G) {
    if(G == NULL) {
        printf("Graph Error: calling getSource() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
	return G->source;
}

// getParent()
// Returns the parent vertex of u in the Breadth First tree or NIL.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
    if(G == NULL) {
        printf("Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
	if(u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getParent() on invalid Graph index\n");
        exit(EXIT_FAILURE);
    }
	return G->parents[u];
}

// getDist()
// Returns the distance from the most recent BFS() vertex u or INF.
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
    if(G == NULL) {
        printf("Graph Error: calling getDist() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
	if(u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getDist() on invalid Graph index\n");
        exit(EXIT_FAILURE);
    }
    if(getSource(G) == NIL) {
        return INF;
    }
	return G->distance[u];
}

// getPath()
// appends to the List L the shortest path in G from source to u or NIL.
// Pre: getSource(G) != NIL
void getPath(List L, Graph G, int u) {
    if(G == NULL) {
        printf("Graph Error: calling getPath() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
	if(u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getPath() on invalid Graph index\n");
        exit(EXIT_FAILURE);
    }
	if(getSource(G) == NIL) {
        printf("Graph Error: calling getPath() on invalid Graph source\n");
        exit(EXIT_FAILURE);
    }
    if (u == getSource(G)) {
        append(L, getSource(G));
    } else if (G->parents[u] == NIL) {
        append(L, NIL);
    } else {
        getPath(L, G, G->parents[u]);
        append(L, u);
    }
    return;
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
    G->source = NIL;
	return;
}

// addEdge()
// inserts a new edge joining u to v.
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v) {
    if(G == NULL) {
        printf("Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
	if(u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling addEdge() on invalid Graph index(u)\n");
        exit(EXIT_FAILURE);
    }
	if(v < 1 || v > getOrder(G)) {
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
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v) {
    if(G == NULL) {
        printf("Graph Error: calling addArc() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }	
	if(u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling addArc() on invalid Graph index(u)\n");
        exit(EXIT_FAILURE);
    }
	if(v < 1 || v > getOrder(G)) {
        printf("Graph Error: calling addArc() on invalid Graph index(v)\n");
        exit(EXIT_FAILURE);
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
        if (v <= get(G->vertices[u])) {
            insertBefore(G->vertices[u], v);
            return;
        }
        moveNext(G->vertices[u]);
    }
	return;
}

// BFS()
// runs the BFS algorithm on the Graph G with source s, 
// setting the color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s) {
    if(G == NULL) {
        printf("Graph Error: calling BFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
	if (s < 1 || s > getOrder(G)) {
		printf("Graph Error: calling BFS() on invalid Graph index(s)\n");
        exit(EXIT_FAILURE);
	}
    for (int i = 1; i <= getOrder(G); i++) {
        G->colors[i] = WHITE;
        G->parents[i] = NIL;
        G->distance[i] = INF;
    }
	G->source = s;
    G->colors[s] = GREY;
    // G->parents[s] = NIL; unnecessary!
    G->distance[s] = 0;
    List Q = newList();
    append(Q, s);
    while (length(Q) > 0) {
        moveFront(Q);
        int v = get(Q);
        deleteFront(Q);
        moveFront(G->vertices[v]);
        for (int i = 0; i < length(G->vertices[v]); i++) {
            int t = get(G->vertices[v]);
            if (G->colors[t] == WHITE) {
                G->colors[t] = GREY;
                G->distance[t] = G->distance[v] + 1;
                G->parents[t] = v;
                append(Q, t);
            }
            moveNext(G->vertices[v]);
        }
        G->colors[v] = BLACK;
    }
    freeList(&Q);
    return;
}

// Other operations ------------------------------------------------------------

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
