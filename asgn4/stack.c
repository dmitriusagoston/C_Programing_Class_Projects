// Some code was taken from asgn4.pdf
// Written by Darrell Long
// code used: Stack, stack_create(), stack_delete(), stack_print()

#include "stack.h"

#include "vertices.h"

#include <stdio.h>
#include <stdlib.h>

// Definition of struct Stack, a stack for storing variables
//
// top: position of the top of the stack (free space)
// capacity: how much the graph can hold
// items: stores the elements of the stack
struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

// creates a new stack
// returns newly created stack
//
// capacity: how big the stack can be
// stack: current stack
Stack *stack_create(uint32_t capacity) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (stack) {
        stack->top = 0;
        stack->capacity = capacity;
        stack->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!stack->items) {
            free(stack);
            stack = NULL;
        }
    }
    return stack;
}

// deletes given stack
// returns nothing
//
// stack: current stack
void stack_delete(Stack **stack) {
    if (*stack && (*stack)->items) {
        free((*stack)->items);
        free(*stack);
        *stack = NULL;
    }
    return;
}

// empties given stack
// returns true or false if successful
//
// stack: current stack
bool stack_empty(Stack *stack) {
    if (stack->top == 0) {
        return true;
    }
    return false;
}

// checks if stack given is full
// returns true or false if successful
//
// stack: current stack
bool stack_full(Stack *stack) {
    if (stack->top >= stack->capacity) {
        return true;
    }
    return false;
}

// gives the size of the stack
// returns size of the stack
//
// stack: current stack
uint32_t stack_size(Stack *stack) {
    return stack->top;
}

// pushes given element to top of stack
// returns true or false if successful
//
// x: variable being pushed to top
// stack: current stack
bool stack_push(Stack *stack, uint32_t x) {
    if (stack_full(stack) != true) {
        stack->items[stack->top] = x;
        stack->top++;
        return true;
    }
    return false;
}

// pops element from top of stack
// returns true or false if successful
//
// x: where to give variable being poped from top
// stack: current stack
bool stack_pop(Stack *stack, uint32_t *x) {
    if (stack_empty(stack) != true) {
        stack->top--;
        *x = stack->items[stack->top];
        return true;
    }
    return false;
}

// gives element from top of stack
// returns true or false if successful
//
// x: where to give variable data from peek
// stack: current stack
bool stack_peek(Stack *stack, uint32_t *x) {
    if (stack_empty(stack) != true) {
        *x = stack->items[stack->top - 1];
        return true;
    }
    return false;
}

// copies all attributes and elements from one stack to anoter
// returns nothing
//
// dst: stack being copied onto
// src: stack being copied
// i: index
void stack_copy(Stack *dst, Stack *src) {
    dst->top = src->top;
    for (uint32_t i = 0; i < src->top; i++) {
        dst->items[i] = src->items[i];
    }
}

// prints the given stack to the outfile
// returns nothing
//
// stack: current stack
// outfile: file being printed to
// cities: names of elements on stack
// i: index
void stack_print(Stack *stack, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < stack->top; i += 1) {
        fprintf(outfile, "%s", cities[stack->items[i]]);
        if (i + 1 != stack->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
