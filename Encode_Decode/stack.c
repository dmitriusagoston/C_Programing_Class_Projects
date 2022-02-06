#include "stack.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Stack Stack;

// Definition of struct Stack, a stack for storing nodes
//
// top: position of the top of the stack (free space)
// capacity: how much the stack can hold
// items: stores the nodes of the stack
struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
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
        stack->items = (Node **) calloc(capacity, sizeof(Node *));
        if (!stack->items) {
            free(stack);
            stack = NULL;
        }
    }
    return stack;
}

// deletes a stack
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

// checks if a stack is empty
// returns true or false if stack is empty
//
// stack: current stack
bool stack_empty(Stack *stack) {
    if (stack->top == 0) {
        return true;
    }
    return false;
}

// checks if a stack is full
// returns true or false if stack is full
//
// stack: current stack
bool stack_full(Stack *stack) {
    if (stack->top >= stack->capacity) {
        return true;
    }
    return false;
}

// gets the size of a stack
// returns stack size
//
// stack: current stack
uint32_t stack_size(Stack *stack) {
    return stack->top;
}

// pushes a node onto the stack
// returns true or false if pushed
//
// stack: current stack
// x: node being pushed
bool stack_push(Stack *stack, Node *x) {
    if (stack_full(stack) != true) {
        stack->items[stack->top] = x;
        stack->top++;
        return true;
    }
    return false;
}

// pops a node off the stack
// returns true or false if popped
//
// stack: current stack
// x: node being popped
bool stack_pop(Stack *stack, Node **x) {
    if (stack_empty(stack) != true) {
        stack->top--;
        *x = stack->items[stack->top];
        return true;
    }
    return false;
}

// prints out a given stack
// returns nothing
//
// stack: current stack
void stack_print(Stack *stack) {
    for (uint32_t i = 0; i < stack->top; i += 1) {
        printf("%hhu", stack->items[i]->symbol);
    }
    printf("\n");
}
