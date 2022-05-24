//-----------------------------------------------------------------------------
// Dmitrius Agoston
// dagoston
// pa3
//
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------
#ifndef Graph_H_INCLUDE_
#define Graph_H_INCLUDE_

#include<stdbool.h>
#include"List.h"

#define UNDEF -1
#define NIL 0
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

// getParent()
// Returns the parent vertex of u in the Depth First tree or NIL.
// Pre: 1 <= u <= n = getOrder(G)
int getParent(Graph G, int u);

// getDiscover()
// Returns the discovery time of u in the Depth First tree or NIL.
// Pre: 1 <= u <= n = getOrder(G)
int getDiscover(Graph G, int u);

// getFinish()
// Returns the finish time of u in the Depth First tree or NIL.
// Pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u);

// Manipulation procedures ----------------------------------------------------

// makeNull()
// deletes all edges of G and restores G to original state.
void makeNull(Graph G);

// addEdge()
// inserts a new edge joining u to v.
// Pre: 1 <= u <= n = getOrder(G), 1 <= v <= n
void addEdge(Graph G, int u, int v);

// addArc()
// inserts a new directed edge from u to v.
// Pre: 1 <= u <= n = getOrder(G), 1 <= v <= n
void addArc(Graph G, int u, int v);

// DFS()
// runs the DFS algorithm on the Graph G.
// Pre: length(S) == getOrder(G)
void DFS(Graph G, List S);

// Other operations ------------------------------------------------------------

// transpose()
// returns a reference to a new graph that is a copy of G
Graph transpose(Graph G);

// copyGraph()
// returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G);

// printGraph()
// prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);
#endif
