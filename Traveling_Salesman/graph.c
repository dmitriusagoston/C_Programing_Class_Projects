// Some code was taken from asgn4.pdf
// Written by Darrell Long
// code used: Graph, graph_create(), graph_delete()

#include "graph.h"

#include "vertices.h"

#include <stdio.h>
#include <stdlib.h>

// Definition of struct Graph, a graph for housing vertices
//
// vertices: the number of vertices in the graph
// undirected: determines if graph is undirected or not
// visited: stores if vertices are visitied or not
// matrix: stores the edge weight of the vertices
struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

// creates a new graph
// returns newly created graph
//
// vertices: amount of vertices in graph
// undirected: determine if graph is undirected
// graph: the directed graph
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *graph = (Graph *) calloc(1, sizeof(Graph));
    graph->vertices = vertices;
    graph->undirected = undirected;
    return graph;
}

// deletes given graph and frees the space taken
// returns nothing
//
// graph: the directed graph
void graph_delete(Graph **graph) {
    free(*graph);
    *graph = NULL;
}

// gives the number of vertices in the graph
// returns ther number of vertices
//
// graph: the directed graph
uint32_t graph_vertices(Graph *graph) {
    return graph->vertices;
}

// adds an edge to the given graph
// returns true or false if successful
//
// i: first vertex
// j: second vertex
// k: weight of edge
// graph: the directed graph
bool graph_add_edge(Graph *graph, uint32_t i, uint32_t j, uint32_t k) {
    if (i <= graph->vertices && j <= graph->vertices && k > 0) {
        graph->matrix[i][j] = k;
        if (graph->undirected == true) {
            graph->matrix[j][i] = k;
        }
        return true;
    }
    return false;
}

// checks if given graph has an edge
// returns true or false if there is an edge
//
// i: first vertex
// j: second vertex
// graph: the directed graph
bool graph_has_edge(Graph *graph, uint32_t i, uint32_t j) {
    if (i < graph->vertices && j < graph->vertices) {
        if (graph->matrix[i][j] > 0) {
            return true;
        }
    }
    return false;
}

// gives the weight of an edge
// returns the edge weight
//
// i: first vertex
// j: second vertex
// graph: the directed graph
uint32_t graph_edge_weight(Graph *graph, uint32_t i, uint32_t j) {
    if (graph_has_edge(graph, i, j) == true) {
        return graph->matrix[i][j];
    }
    return 0;
}

// check if a vertex has been visited
// returns true or false if visited
//
// v: vertex being checked
// graph: the directed graph
bool graph_visited(Graph *graph, uint32_t v) {
    return graph->visited[v];
}

// marks a vertex as visited
// returns nothing
//
// v: vertex being checked
// graph: the directed graph
void graph_mark_visited(Graph *graph, uint32_t v) {
    if (v <= graph->vertices) {
        graph->visited[v] = true;
    }
}

// unmarks a vertex as visited
// returns nothing
//
// v: vertex being checked
// graph: the directed graph
void graph_mark_unvisited(Graph *graph, uint32_t v) {
    if (v <= graph->vertices) {
        graph->visited[v] = false;
    }
}

// prints the graph
// returns nothing
//
// i: index 1
// j: index 2
// graph: the directed graph
void graph_print(Graph *graph) {
    for (int i = 0; i < VERTICES; i++) {
        for (int j = 0; j < VERTICES; j++) {
            printf("%u ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}
