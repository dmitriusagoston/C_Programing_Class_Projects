//-----------------------------------------------------------------------------
// Dmitrius Agoston
// dagoston
// pa2
//
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------
#ifndef Graph_H_INCLUDE_
#define Graph_H_INCLUDE_

#include<stdbool.h>
#include"List.h"

#define INF -8
#define NIL -1
#define WHITE 0
#define GREY 1
#define BLACK 2
// Exported type --------------------------------------------------------------
typedef struct GraphObj* Graph;


// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns reference to new empty Graph object. 
Graph newGraph(int n);

// freeGraph()
// Frees all heap memory associated with Graph *pG, and sets *pG to NULL.
void freeGraph(Graph* pG);


// Access functions -----------------------------------------------------------

// getOrder()
// Returns the order of G
int getOrder(Graph G);

// getSize()
// Returns the size of G.
int getSize(Graph G);

// getSource()
// Returns the source vertex most recently used in BFS() or NIL.
int getSource(Graph G);

// getParent()
// Returns the parent vertex of u in the Breadth First tree or NIL.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

// getDist()
// Returns the distance from the most recent BFS() vertex u or INF.
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u);

// getPath()
// appends to the List L the shortest path in g from source to u or NIL.
// Pre: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u);

// Manipulation procedures ----------------------------------------------------

// makeNull()
// deletes all edges of G and restores G to original state.
void makeNull(Graph G);

// addEdge()
// inserts a new edge joining u to v.
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v);

// addArc()
// inserts a new directed edge from u to v.
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v);

// BFS()
// runs the BFS algorithm on the Graph G with source s, 
// setting the color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s);

// Other operations ------------------------------------------------------------

// printGraph()
// prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);
#endif
