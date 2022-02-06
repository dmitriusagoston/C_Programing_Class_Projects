// Some code was taken from asgn4.pdf
// Written by Darrell Long
// code used: Path

#include "path.h"

#include "stack.h"
#include "vertices.h"

#include <stdio.h>
#include <stdlib.h>

// Definition of struct Path, a path for storing edge weights from vertices
//
// vertices: a stack of the vertices on the path
// length: the length of the path
struct Path {
    Stack *vertices;
    uint32_t length;
};

// creates a new path
// returns newly created path
//
// path: current path
Path *path_create() {
    Path *path = (Path *) calloc(1, sizeof(Path));
    path->length = 0;
    path->vertices = stack_create(VERTICES);
    return path;
}

// deletes given path
// returns nothing
//
// path: current path
void path_delete(Path **path) {
    // have to free stack memory too
    stack_delete(&(*path)->vertices);
    free(*path);
    *path = NULL;
    return;
}

// pushes vertex onto path
// returns true or false if successful
//
// path: current path
// v: vertex
// graph: current graph
bool path_push_vertex(Path *path, uint32_t v, Graph *graph) {
    // check if no vertices on the path yet
    if (v == 0 && path_length(path) == 0) {
        stack_push(path->vertices, 0);
        return true;
    }
    uint32_t peek = 0;
    // path works only if there is an edge
    stack_peek(path->vertices, &peek);
    if (graph_has_edge(graph, peek, v) == true) {
        if (stack_push(path->vertices, v) == true) {
            path->length += graph_edge_weight(graph, peek, v);
            return true;
        }
    }
    return false;
}

// pops vertex from path
// returns true or false if successful
//
// path: current path
// v: vertex
// graph: current graph
bool path_pop_vertex(Path *path, uint32_t *v, Graph *graph) {
    if (stack_pop(path->vertices, v) == true) {
        uint32_t peek = 0;
        stack_peek(path->vertices, &peek);
        path->length -= graph_edge_weight(graph, peek, *v);
        return true;
    }
    return false;
}

// gives the number of vertices of the path
// returns number of vertices
//
// path: current path
uint32_t path_vertices(Path *path) {
    return stack_size(path->vertices);
}

// gives the length of the path
// returns length of the path
//
// path: current path
uint32_t path_length(Path *path) {
    return path->length;
}

// copies the given path onto another path
// returns nothing
//
// dst: path to be copied onto
// src: path to copy from
void path_copy(Path *dst, Path *src) {
    dst->length = src->length;
    stack_copy(dst->vertices, src->vertices);
}

// prints the given path to the outfile
// returns nothing
//
// path: current path
// outfile: file to be printed to
// cities: names of vertices
void path_print(Path *path, FILE *outfile, char *cities[]) {
    printf("Path length: %u\n", path_length(path));
    printf("Path: ");
    stack_print(path->vertices, outfile, cities);
}
