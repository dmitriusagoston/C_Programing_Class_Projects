//-----------------------------------------------------------------------------
//  MatrixClient.c 
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){
    int n = 100000;
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    Matrix C, D, E, F, G, H;

    for (int i = 1; i <= 100; i++) {
        for (int j = 1; j <= 100; j++) {
            changeEntry(A, i, j, i + j);
            changeEntry(B, j, i, i + j);
        }
    }

    printf("%d\n", NNZ(A));
    printMatrix(stdout, A);
    printf("\n");
    printf("%d\n", NNZ(B));
    printMatrix(stdout, B);
    printf("\n");
    C = scalarMult(.5, A);
    printf("%d\n", NNZ(C));
    printMatrix(stdout, C);
    printf("\n");
    C = scalarMult(-2.5, A);
    printf("%d\n", NNZ(C));
    printMatrix(stdout, C);
    printf("\n");
    D = sum(A, B);
    printf("%d\n", NNZ(D));
    printMatrix(stdout, D);
    printf("\n");
    D = sum(A, A);
    printf("%d\n", NNZ(D));
    printMatrix(stdout, D);
    printf("\n");
    E = diff(B, A);
    printf("%d\n", NNZ(E));
    printMatrix(stdout, E);
    printf("\n");
    E = diff(A, A);
    printf("%d\n", NNZ(E));
    printMatrix(stdout, E);
    printf("\n");
    F = transpose(B);
    printf("%d\n", NNZ(F));
    printMatrix(stdout, F);
    printf("\n");
    G = product(B, B);
    printf("%d\n", NNZ(G));
    printMatrix(stdout, G);
    printf("\n");
    G = product(B, C);
    printf("%d\n", NNZ(G));
    printMatrix(stdout, G);
    printf("\n");
    H = copy(A);
    printf("%d\n", NNZ(H));
    printMatrix(stdout, H);
    printf("\n");
    printf("%s\n", equals(A, H)?"true":"false" );
    printf("%s\n", equals(A, B)?"true":"false" );
    printf("%s\n", equals(A, A)?"true":"false" );
    makeZero(A);
    printf("%d\n", NNZ(A));
    printMatrix(stdout, A);
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
}
