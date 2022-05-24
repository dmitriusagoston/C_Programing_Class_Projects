#include "pq.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct PriorityQueue PriorityQueue;

// Definition of PriorityQueue, a queue with priorities for nodes
//
// nodes: all of the nodes in the queue
// capacity: how much the queue can hold
// tail: variable for tracking size of queue
struct PriorityQueue {
    Node **nodes;
    uint32_t capacity;
    uint32_t tail;
};

// swaps two nodes
// returns nothing
//
// x: first node being swapped
// y: second node being swapped
// t: temporary variable for holding node
void swap(Node **x, Node **y) {
    Node *t = *x;
    *x = *y;
    *y = t;
    return;
}

// gets the minimum child
// returns the minimum child
//
// A: current priority queue
// first: current position
uint32_t min_child(PriorityQueue *A, uint32_t first) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    if (right <= A->tail && A->nodes[right - 1]->frequency < A->nodes[left - 1]->frequency) {
        return right;
    }
    return left;
}

// fixes the heap for dequeueing nodes into the priority queue
// returns nothing
//
// A: current priority queue
void fix_heap_de(PriorityQueue *A) {
    if (A->tail < 2) {
        return;
    }
    bool found = false;
    uint32_t mother = 1;
    uint32_t min = min_child(A, mother);
    while (mother <= A->tail / 2 && found != true) {
        if (A->nodes[mother - 1]->frequency > A->nodes[min - 1]->frequency) {
            swap(&A->nodes[mother - 1], &A->nodes[min - 1]);
            mother = min;
            min = min_child(A, mother);
        } else {
            found = true;
        }
    }
    return;
}

// fixes the heap for enqueueing nodes into the priority queue
// returns nothing
//
// A: current priority queue
void fix_heap_en(PriorityQueue *A) {
    if (A->tail < 2) {
        return;
    }
    bool found = false;
    uint32_t child = A->tail;
    while (child > 1 && found != true) {
        if (A->nodes[child - 1]->frequency < A->nodes[child / 2 - 1]->frequency) {
            swap(&A->nodes[child - 1], &A->nodes[child / 2 - 1]);
            child = child / 2;
        } else {
            found = true;
        }
    }
    return;
}

// creates a new priority queue
// returns the newly created priority queue
//
// capacity: the size of the priority queue
PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (pq) {
        pq->capacity = capacity;
        pq->tail = 0;
        pq->nodes = (Node **) calloc(capacity, sizeof(Node *));
        if (!pq->nodes) {
            free(pq);
            pq = NULL;
        }
    }
    return pq;
}

// deletes a given priority queue
// returns nothing
//
// pq: current priority queue
void pq_delete(PriorityQueue **pq) {
    if ((*pq)->nodes) {
        free((*pq)->nodes);
    }
    if (*pq) {
        free(*pq);
        *pq = NULL;
    }
    return;
}

// determines if priority queue is empty
// returns true or false if the priority queue is empty
//
// pq: current priority queue
bool pq_empty(PriorityQueue *pq) {
    if (pq->tail == 0) {
        return true;
    }
    return false;
}

// determines if priority queue is full
// returns true or false if the priority queue is full
//
// pq: current priority queue
bool pq_full(PriorityQueue *pq) {
    if (pq->tail >= pq->capacity) {
        return true;
    }
    return false;
}

// gives the current size of the priority queue
// returns the size of the priority queue
//
// pq: current priority queue
uint32_t pq_size(PriorityQueue *pq) {
    return pq->tail;
}

// enqueues a given node into the priority queue
// returns true or false if enqueue was successful
//
// pq: current priority queue
// n: node being enqueued
bool enqueue(PriorityQueue *pq, Node *n) {
    if (pq_empty(pq)) {
        pq->nodes[pq->tail] = n;
        pq->tail++;
        return true;
    }
    if (!pq_full(pq)) {
        pq->nodes[pq->tail] = n;
        pq->tail++;
        fix_heap_en(pq);
        return true;
    }
    return false;
}

// dequeues a given from the priority queue
// returns true or false if dequeue was successful
//
// pq: current priority queue
// n: node being dequeued
bool dequeue(PriorityQueue *pq, Node **n) {
    if (!pq_empty(pq)) {
        pq->tail--;
        *n = pq->nodes[0];
        pq->nodes[0] = pq->nodes[pq->tail];
        fix_heap_de(pq);
        return true;
    }
    return false;
}

// prints the priority queue
// returns nothing
//
// pq: current priority queue
void pq_print(PriorityQueue *pq) {
    for (uint32_t i = 0; i < pq->tail; i++) {
        printf("index:%u Node: %hhu Frequency: %lu\n", i, pq->nodes[i]->symbol,
            pq->nodes[i]->frequency);
    }
    return;
}
