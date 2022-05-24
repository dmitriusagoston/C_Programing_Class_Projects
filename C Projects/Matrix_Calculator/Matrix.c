//-----------------------------------------------------------------------------
// Dmitrius Agoston
// dagoston
// pa4
//
// Matrix.c
// Implementaion file for Matrix ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include "List.h"
#include "Matrix.h"

// Structs -------------------------------------------------------------------

// private Entry type
typedef struct EntryObj* Entry;

// private EntryObj type
typedef struct EntryObj{
    int col;
    double val;
} EntryObj;

// private MatrixObj type
typedef struct MatrixObj{
    List *entry;
    int size;
    int NNZ;
} MatrixObj;

// Constructors-Destructors ---------------------------------------------------

// newEntry()
// Returns reference to new empty Entry object.
Entry newEntry(int c, double v) {
    Entry E;
    E = malloc(sizeof(EntryObj));
    E->col = c;
    E->val = v;
    return E;
}

// newMatrix()
// Returns reference to new empty Matrix object. 
Matrix newMatrix(int n) {
    Matrix M;
    M = malloc(sizeof(MatrixObj));
    M->size = n;
    M->NNZ = 0;
    M->entry = malloc(sizeof(List) * (n + 1));
    for (int i = 1; i <= M->size; i++) {
        M->entry[i] = newList();
    }
    return M;
}

// freeEntry()
// Frees all heap memory associated with Entry *pE, and set *pE to NULL.
void freeEntry(Entry* pE) {
    if (pE != NULL && *pE != NULL) {
        free(*pE);
        *pE = NULL;
    }
    return;
}

// freeMatrix()
// Frees all heap memory associated with Matrix *pM, and sets *pM to NULL.
void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        for (int i = 1; i <= (*pM)->size; i++) {
            moveFront((*pM)->entry[i]);
            for (int j = 0; j < length((*pM)->entry[i]); j++) {
                Entry cur = get((*pM)->entry[i]);
                freeEntry(&cur);
                moveNext((*pM)->entry[i]);
            }
            freeList(&(*pM)->entry[i]);
        }
        free((*pM)->entry);
        free(*pM);
        *pM = NULL;
    }
    return;
}

// Access functions -----------------------------------------------------------

// size()
// Returns the size of square Matrix M..
int size(Matrix M) {
    if(M == NULL) {
        printf("Matrix Error: calling size() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    return M->size;
}

// NNZ()
// Returns the number of non-zero elements in M..
int NNZ(Matrix M) {
    if(M == NULL) {
        printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    return M->NNZ;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
    if(A == NULL || B == NULL) {
        printf("Matrix Error: calling equals() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    int eq = 0;
    Entry N = NULL;
    Entry M = NULL;

    eq = (A->size == B->size);
    if (eq == 0) {
        return eq;
    }
    for (int i = 1; i < A->size; i++) {
        List a = A->entry[i];
        List b = B->entry[i];
        moveFront(a);
        moveFront(b);
        if (length(a) != length(b)) {
            return 0;
        }
        while (eq && N != NULL) {
            N = get(a);
            M = get(b);
            eq = (N->col == M->col && N->val == M->val);
            moveNext(a);
            moveNext(b);
        }
        if (eq == 0) {
            return eq;
        }
    }
    return eq;
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
    if(M == NULL) {
        printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= M->size; i++) {
        moveFront(M->entry[i]);
        for (int j = 0; j < length(M->entry[i]); j++) {
            Entry cur = get(M->entry[i]);
            freeEntry(&cur);
            moveNext(M->entry[i]);
        }
        freeList(&(M->entry[i]));
    }
    for (int i = 1; i <= M->size; i++) {
        M->entry[i] = newList();
    }
    M->NNZ = 0;
    return;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
    if(M == NULL) {
        printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(i < 1 || i > size(M)) {
        printf("Matrix Error: calling changeEntry() with invalid row size\n");
        exit(EXIT_FAILURE);
    }
    if(j < 1 || j > size(M)) {
        printf("Matrix Error: calling changeEntry() with invalid column size\n");
        exit(EXIT_FAILURE);
    }
    if (x == 0.0) {
        int ind = index(M->entry[i]);
        moveFront(M->entry[i]);
        for (int lcv = 0; lcv < length(M->entry[i]); lcv++) {
            Entry cur = get(M->entry[i]);
            if (cur->col == j) {
                freeEntry(&cur);
                delete(M->entry[i]);
                M->NNZ--;
                break;
            }
            moveNext(M->entry[i]);
        }
        moveFront(M->entry[i]);
        for (int lcv = 0; lcv <= length(M->entry[i]); lcv++) {
            if (ind == index(M->entry[i])) {
                return;
            }
            moveNext(M->entry[i]);
        }
        return;
    }
    Entry E = NULL;
    if (length(M->entry[i]) <= 0) {
        E = newEntry(j, x);
        append(M->entry[i], E);
        M->NNZ++;
        return;
    }
    moveBack(M->entry[i]);
    E = get(M->entry[i]);
    if (E->col <= j) {
        if (E->col == j) {
            E->val = x;
            return;
        } else {
            E = newEntry(j, x);
            append(M->entry[i], E);
            M->NNZ++;
            return;
        }
    }
    moveFront(M->entry[i]);
    while (E != NULL) {
        E = get(M->entry[i]);
        if (E->col >= j) {
            if (E->col == j) {
                E->val = x;
            } else {
                E = newEntry(j, x);
                insertBefore(M->entry[i], E);
                M->NNZ++;
                return;
            }
        }
        moveNext(M->entry[i]);
    }
    return;
}

// Matrix Arithmetic operations -----------------------------------------------

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
    if(A == NULL) {
        printf("Matrix Error: calling copy() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);

    }
    Matrix C = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->entry[i]);
        for (int j = 0; j < length(A->entry[i]); j++) {
            Entry cur = get(A->entry[i]);
            changeEntry(C, i, cur->col, cur->val);
            moveNext(A->entry[i]);
        }
    }
    return C;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
    if(A == NULL) {
        printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix T = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->entry[i]);
        for (int j = 0; j < length(A->entry[i]); j++) {
            Entry cur = get(A->entry[i]);
            changeEntry(T, cur->col, i, cur->val);
            moveNext(A->entry[i]);
        }
    }
    return T;
}
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
    if(A == NULL) {
        printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix SM = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->entry[i]);
        for (int j = 0; j < length(A->entry[i]); j++) {
            Entry cur = get(A->entry[i]);
            changeEntry(SM, i, cur->col, cur->val * x);
            moveNext(A->entry[i]);
        }
    }
    return SM;
}


// comboList()
// Returns new List after combining two
List comboList(List A, List B, bool combo) {
    List C = newList();
    Entry a = NULL;
    Entry b = NULL;
    int cola = 0;
    int colb = 0;
    moveFront(A);
    moveFront(B);
    while(index(A) != -1 || index(B) != -1) {
        if (index(A) != -1) {
            a = get(A);
            cola = a->col;
        }
        if (index(B) != -1) {
            b = get(B);
            colb = b->col;
        }
        if (cola == colb) {
            if (combo) {
                Entry sum = newEntry(cola, a->val + b->val);
                append(C, sum);
            } else {
                Entry diff = newEntry(cola, a->val - b->val);
                append(C, diff);
            }
            moveNext(A);
            moveNext(B);
        } else if (index(A) == -1) {
            if (combo) {
                Entry sum = newEntry(colb, 0 + b->val);
                append(C, sum);
            } else {
                Entry diff = newEntry(colb, 0 - b->val);
                append(C, diff);
            }
            moveNext(B);
        } else if (index(B) == -1) {
             if (combo) {
                Entry sum = newEntry(cola, a->val + 0);
                append(C, sum);
            } else {
                Entry diff = newEntry(cola, a->val - 0);
                append(C, diff);
            }
           moveNext(A);          
        } else if (cola < colb && cola > 0) {
            if (combo) {
                Entry sum = newEntry(cola, a->val + 0);
                append(C, sum);
            } else {
                Entry diff = newEntry(cola, a->val - 0);
                append(C, diff);
            }
            moveNext(A);
        } else if (colb < cola && colb > 0) {
            if (combo) {
                Entry sum = newEntry(colb, 0 + b->val);
                append(C, sum);
            } else {
                Entry diff = newEntry(colb, 0 - b->val);
                append(C, diff);
            }
            moveNext(B);
        }
    }
    return C;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
    if(A == NULL || B == NULL) {
        printf("Matrix Error: calling sum() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(size(A) != size(B)) {
        printf("Matrix Error: calling sum() on unequally sized matricies\n");
        exit(EXIT_FAILURE);
    }   
    if (equals(A, B)) {
        return scalarMult(2, A);
    }
    Matrix S = newMatrix(size(A));
    for (int i = 1; i <= size(S); i++) {
        List a = A->entry[i];
        List b = B->entry[i];
        List s = comboList(a, b, true);
        moveFront(s);
        for (int j = 1; j <= length(s); j++) {
            Entry cur = get(s);
            changeEntry(S, i, cur->col, cur->val);
            moveNext(s);
        }
        moveFront(s);
        for (int j = 0; j < length(s); j++) {
            Entry cur = get(s);
            freeEntry(&cur);
            moveNext(s);
        }
        freeList(&s);
    }
    return S;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
    if(A == NULL || B == NULL) {
        printf("Matrix Error: calling diff() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(size(A) != size(B)) {
        printf("Matrix Error: calling diff() on unequally sized matricies\n");
        exit(EXIT_FAILURE);
    }
    Matrix D = newMatrix(size(A));
    for (int i = 1; i <= size(D); i++) {
        List a = A->entry[i];
        List b = B->entry[i];
        List d = comboList(a, b, false);
        moveFront(d);
        for (int j = 1; j <= length(d); j++) {
            Entry cur = get(d);
            changeEntry(D, i, cur->col, cur->val);
            moveNext(d);
        }
        moveFront(d);
        for (int j = 0; j < length(d); j++) {
            Entry cur = get(d);
            freeEntry(&cur);
            moveNext(d);
        }
        freeList(&d);
    }
    return D;
}

// vectorDot()
// Returns dot product of two lists
double vectorDot(List P, List Q, int size) {
    double total = 0;
    moveFront(P);
    moveFront(Q);
    Entry p = NULL;
    Entry q = NULL;
    for (int i = 1; i <= size; i++) {
        int colp = 0;
        int colq = 0;
        if (index(P) >= 0) {
            p = get(P);
            colp = p->col;
        }
        if (index(Q) >= 0) {
            q = get(Q);
            colq = q->col;
        }
        if (colp == i && colq == i && colp == colq) {
            total += p->val * q->val;
            moveNext(P);
            moveNext(Q);
        } else if (colp == i) {
            moveNext(P);
        } else if (colq == i) {
            moveNext(Q);
        }
    }
    return total;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    if(A == NULL || B == NULL) {
        printf("Matrix Error: calling product() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(size(A) != size(B)) {
        printf("Matrix Error: calling product() on unequally sized matricies\n");
        exit(EXIT_FAILURE);
    }
    Matrix BB = transpose(B);
    Matrix P = newMatrix(size(A));
    for (int i = 1; i <= size(P); i++) {
        if (length(A->entry[i]) == 0) {
            continue;
        }
        double cur = 0;
        for (int j = 1; j <= size(P); j++) {
            if (length(BB->entry[j]) == 0) {
                continue;
            }
            cur += vectorDot(A->entry[i], BB->entry[j], size(P));
            changeEntry(P, i, j, cur);
            cur = 0;
        }
    }
    freeMatrix(&BB);
    return P;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
    if(M == NULL) {
        printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= size(M); i++) {
        if (length(M->entry[i]) < 1) {
            continue;
        }
        fprintf(out, "%d: ", i);
        moveFront(M->entry[i]);
        for (int j = 0; j < length(M->entry[i]); j++) {
            Entry m = get(M->entry[i]);
            fprintf(out, "(%d, %.1f) ", m->col, m->val);
            moveNext(M->entry[i]);
        }
        fprintf(out, "\n");
    }
    return;
}
