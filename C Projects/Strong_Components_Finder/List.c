//-----------------------------------------------------------------------------
// Dmitrius Agoston
// dagoston
// pa3
//
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   int data;
   Node previous;
   Node next;
} NodeObj;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->previous = NULL;
   N->next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while((*pL)->length > 0) {
          deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
      return;
   }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L) {
    if(L == NULL) {
        printf("List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}


// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
    if(L == NULL) {
        printf("List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->index;
}

// front()
// Returns front element of L.
// Pre: length()>0
int front(List L) {
    if (L == NULL) {
        printf("List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: calling front() on empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

// back()
// Returns back element of L.
// Pre: length()>0
int back(List L) {
    if (L == NULL) {
        printf("List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: calling back() on empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

// get()
// Returns cursor element of L.
// Pre: length()>0, index()>=0
int get(List L) {
    if (L == NULL) {
        printf("List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: calling get() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        printf("List Error: calling get() on invalid List index\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

// equals()
// Returns true if Lists A and B are in same state, and returns false otherwise.
bool equals(List A, List B) {
    if (A == NULL || B == NULL) {
        printf("List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    int eq = 0;
    Node N = NULL;
    Node M = NULL;

    eq = (A->length == B->length);
    N = A->front;
    M = B->front;
    while (eq && N != NULL) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L) {
    if (L == NULL) {
        printf("List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    while(L->length > 0) {
        deleteFront(L); 
    }
    L->index = -1;
    L->length = 0;
    return;
}

// set()
// Overwrites the cursor element's data with x.
// Pre: length()>0, index()>=0
void set(List L, int x) {
    if (L == NULL) {
        printf("List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: calling set() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        printf("List Error: calling set() on invalid List index\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
    return;
}

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
    if (L == NULL) {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) != 0) {
        L->index = 0;
        L->cursor = L->front;
    }
    return;
}

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
    if (L == NULL) {
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) != 0) {
        L->index = L->length - 1;
        L->cursor = L->back;
    }
    return;
}

// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing.
void movePrev(List L) {
    if (L == NULL) {
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL && index(L) == 0) {
        L->index = -1;
        L->cursor = NULL;
    }
    if (L->cursor != NULL && index(L) > 0) {
        L->index -= 1;
        L->cursor = L->cursor->previous;
    }
    return;
}

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
    if (L == NULL) {
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL && index(L) == length(L) - 1) {
        L->index = -1;
        L->cursor = NULL;
    }
    if (L->cursor != NULL && index(L) < length(L) - 1) {
        L->index += 1;
        L->cursor = L->cursor->next;
    }
    return;
}

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int x) {
    if (L == NULL) {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (length(L) != 0) {
        N->next = L->front;
        L->front->previous = N;
        L->front = N;
        L->length += 1;
        if (L->index != -1) {
            L->index++;
        }
    }
    if (length(L) == 0) {
        L->front = N;
        L->back = N;
        L->length += 1;
    }  
    return;
}

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int x) {
    if (L == NULL) {
        printf("List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (length(L) != 0) {
        N->previous = L->back;
        L->back->next = N;
        L->back = N;
        L->length += 1;
    }
    if (length(L) == 0) {
        L->front = N;
        L->back = N;
        L->length += 1;
    } 
    return;
}


// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
    if (L == NULL) {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: calling insertBefore() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        printf("List Error: calling insertBefore() on invalid List index\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < length(L)) {
        Node N = newNode(x);
        N->previous = L->cursor->previous;
        L->cursor->previous = N;
        N->next = L->cursor;
        if (L->cursor == L->front) {
            L->front = N;
        } else {
            N->previous->next = N;
        }
        L->length += 1;
        L->index += 1;
    }
    return;
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
    if (L == NULL) {
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: calling insertAfter() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        printf("List Error: calling insertAfter() on invalid List index\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < length(L)) {
        Node N = newNode(x);
        N->next = L->cursor->next;
        L->cursor->next = N;
        N->previous = L->cursor;
        if (L->cursor == L->back) {
            L->back = N;
        } else {
            N->next->previous = N;
        }
        L->length += 1;
    }
    return;
}

// deleteFront()
// Delete the front element.
// Pre: length()>0
void deleteFront(List L) {
    if (L == NULL) {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: calling deleteFront() on empty List\n");
        exit(EXIT_FAILURE);
    }
    Node N = L->front;
    if (length(L) > 1) {
        if (L->cursor != NULL) {
            L->index--;
            if (L->cursor == L->front) {
                L->cursor = NULL;
            }
        }
        L->front = L->front->next;
        L->front->previous = NULL;
    }
    L->length -= 1;
    freeNode(&N);
    return;
}

// deleteBack()
// Delete the back element.
// Pre: length()>0
void deleteBack(List L) {
    if (L == NULL) {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: calling deleteBack() on empty List\n");
        exit(EXIT_FAILURE);
    }
    Node N = L->back;
    if (length(L) > 1) {
        if (L->cursor == L->back) {
            L->cursor = NULL;
            L->index = -1;
        }
        L->back = L->back->previous;
        L->back->next = NULL;
    }
    L->length -= 1;
    freeNode(&N);
    return;
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
    if (L == NULL) {
        printf("List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: calling delete() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        printf("List Error: calling delete() on invalid List index\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 1) {
        clear(L);
        L->index = 0;
        return;
    }
    Node N = L->cursor;
    if (L->cursor == L->back) {
        L->back = L->cursor->previous;
        L->back->next = NULL;
        L->cursor = NULL;
        L->index = -1;
        L->length -= 1;
        freeNode(&N);
        return;
    }
    if (L->cursor == L->front) {
        L->front = L->cursor->next;
        L->front->previous = NULL;
        L->cursor = NULL;
        L->index = -1;
        L->length -= 1;
        freeNode(&N);
        return;
    }
    L->cursor->previous->next = L->cursor->next;
    L->cursor = L->cursor->next;
    L->cursor->previous = L->cursor->previous->previous;
    L->length -= 1;
    freeNode(&N);
    return;
}

// Other operations ------------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L) {
    if (L == NULL) {
        printf("List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = NULL;
    for (N = L->front; N != NULL; N = N->next) {
        fprintf(out, "%d ", N->data);
    }
    return;
} 
// copyList()
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) {
    if (L == NULL) {
        printf("List Error: calling copyList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    List copy = newList();
    int count = 0;
    Node N = NULL;
    for (N = L->front; N != NULL; N = N->next) {
        append(copy, N->data);
        count++;
    }
    copy->length = count;
    return copy;
}
 
// concatList()
// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B) {
    if (A == NULL || B == NULL) {
        printf("List Error: calling concatList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    List cat = copyList(A);
    Node N = NULL;
    for (N = B->front; N != NULL; N = N->next) {
        append(cat, N->data);
    }
    return cat;
}
