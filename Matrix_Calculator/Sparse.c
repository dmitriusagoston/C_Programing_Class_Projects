//-----------------------------------------------------------------------------
// Dmitrius Agoston
// dagoston
// pa4
//
// Sparse.c
// File for preofrming matrix operations
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"
#include "Matrix.h"

int main(int argc, char** argv) {
    FILE *infile = NULL;
    FILE *outfile = NULL;
    if (argc != 3) {
        fprintf(stderr, "USAGE: ./Sparse [infile] [outfile]\n");
        return -1;
    }
    if ((infile = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error: failed to open infile\n");
        return -1;
    }
    if ((outfile = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "Error: failed to open outfile\n");
        fclose(infile);
        return -1;
    }
    int n = 0, a = 0, b = 0;
    fscanf(infile, "%d %d %d", &n, &a, &b);
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    fgetc(infile);
    for (int i = 0; i < a; i++) {
        int i = 0, j = 0;
        double x = 0;
        fscanf(infile, "%d %d %lf", &i, &j, &x);
        if (i > n || j > n || i < 1 || j < 1) {
            fprintf(stderr, "Error: malformed matrix element.\n");
            return -1;
        }
        changeEntry(A, i, j, x);
    }
    fgetc(infile);
    for (int i = 0; i < b; i++) {
        int i = 0, j = 0;
        double x = 0;
        fscanf(infile, "%d %d %lf", &i, &j, &x);
        if (i > n || j > n || i < 1 || j < 1) {
            fprintf(stderr, "Error: malformed matrix element.\n");
            return -1;
        }
        changeEntry(B, i, j, x);
    }
    fprintf(outfile, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(outfile, A);
    fprintf(outfile, "\n");

    fprintf(outfile, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(outfile, B);
    fprintf(outfile, "\n");

    fprintf(outfile, "(1.5)*A =\n");
    Matrix SM = scalarMult(1.5, A);
    printMatrix(outfile, SM);
    fprintf(outfile, "\n");

    fprintf(outfile, "A+B =\n");
    Matrix APB = sum(A, B);
    printMatrix(outfile, APB);
    fprintf(outfile, "\n");

    fprintf(outfile, "A+A =\n");
    Matrix APA = sum(A, A);
    printMatrix(outfile, APA);
    fprintf(outfile, "\n");

    fprintf(outfile, "B-A =\n");
    Matrix BMA = diff(B, A);
    printMatrix(outfile, BMA);
    fprintf(outfile, "\n");

    fprintf(outfile, "A-A =\n");
    Matrix AMA = diff(A, A);
    printMatrix(outfile, AMA);
    fprintf(outfile, "\n");

    fprintf(outfile, "Transpose(A) =\n");
    Matrix AT = transpose(A);
    printMatrix(outfile, AT);
    fprintf(outfile, "\n");

    fprintf(outfile, "A*B =\n");
    Matrix ADB = product(A, B);
    printMatrix(outfile, ADB);
    fprintf(outfile, "\n");

    fprintf(outfile, "B*B =\n");
    Matrix BDB = product(B, B);
    printMatrix(outfile, BDB);
    fprintf(outfile, "\n");

    freeMatrix(&BDB);
    freeMatrix(&ADB);
    freeMatrix(&AT);
    freeMatrix(&AMA);
    freeMatrix(&BMA);
    freeMatrix(&APA);
    freeMatrix(&APB);
    freeMatrix(&SM);
    freeMatrix(&B);
    freeMatrix(&A);

    fclose(outfile);
    fclose(infile);
    return 0;
}
