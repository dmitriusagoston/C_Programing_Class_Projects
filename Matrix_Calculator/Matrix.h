//-----------------------------------------------------------------------------
// Dmitrius Agoston
// dagoston
// pa4
//
// Matrix.h
// Header file for Matrix ADT
//-----------------------------------------------------------------------------
#ifndef MATRIX_H_INCLUDE_
#define MATRIX_H_INCLUDE_

#include<stdbool.h>


// Exported type --------------------------------------------------------------
typedef struct MatrixObj* Matrix;


// Constructors-Destructors ---------------------------------------------------

// newMatrix()
// Returns reference to new empty List object. 
Matrix newMatrix(int n);

// freeList()
// Frees all heap memory associated with Matrix *pM, and sets *pM to NULL.
void freeMatrix(Matrix* pM);


// Access functions -----------------------------------------------------------

// size()
// Returns the size of square Matrix M..
int size(Matrix M);

// NNZ()
// Returns the number of non-zero elements in M..
int NNZ(Matrix M);

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B);

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M);

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 0<=i<size(M), 0<=j<size(M)
void changeEntry(Matrix M, int i, int j, double x);

// Matrix Arithmetic operations -----------------------------------------------

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A);

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A);

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A);

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B);

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B);

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B);

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M);

#endif
