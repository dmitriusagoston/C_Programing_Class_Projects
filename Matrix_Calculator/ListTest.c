//-----------------------------------------------------------------------------
// ListTest.c
// Test harness for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]) {
    List A = newList();
    List B = newList();
    List C = newList();

    int X[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};

    for (int i = 0; i < 30; i++) {
        append(A, &X[i]);
        prepend(B, &X[i]);
        if (i % 5 == 0) {
            append(C, &X[i]);
        }
    }
    moveFront(C);
    insertAfter(C, &X[23]);
    insertAfter(C, &X[25]);
    insertBefore(C, &X[3]);

    printf("A Length:%d\n", length(A));
    printf("B Length:%d\n", length(B));
    printf("C Length:%d\n", length(C));
    printf("A Index:%d\n", index(A));
    printf("B Index:%d\n", index(B));
    printf("C Index:%d\n", index(C));

    printf("A Front:%d\n", front(A));
    printf("B Front:%d\n", front(B));
    printf("C Front:%d\n", front(C));
    printf("A Back:%d\n", back(A));
    printf("B Back:%d\n", back(B));
    printf("C Back:%d\n", back(C));

    moveFront(A);
    for (int i = 0; i < length(A); i++) {
        printf("A[%d]: %d\n)", i, get(A));
        moveNext(A);
    }

    moveFront(A);
    for (int i = 0; i < length(A); i++) {
        printf("A[%d]: %d\n)", i, get(A));
        set(A, &X[i + 1]);
        moveNext(A);
    }

    moveBack(B);
    for (int i = 0; i < length(B); i++) {
        printf("B[%d]: %d\n)", i, get(B));
        movePrev(B);
    }

    insertAfter(C, &X[23]);
    insertAfter(C, &X[25]);
    insertBefore(C, &X[3]);
    moveFront(C);
    for (int i = 0; i < length(C); i++) {
        printf("A[%d]: %d\n)", i, get(C));
        moveNext(C);
    }

    deleteFront(C);
    deleteBack(C);
    moveFront(C);
    for (int i = 0; i < length(C); i++) {
        printf("A[%d]: %d\n)", i, get(C));
        moveNext(C);
    }

    printf("A Length:%d\n", length(A));
    printf("B Length:%d\n", length(B));
    printf("C Length:%d\n", length(C));
    printf("A Index:%d\n", index(A));
    printf("B Index:%d\n", index(B));
    printf("C Index:%d\n", index(C));

    printf("A Front:%d\n", front(A));
    printf("B Front:%d\n", front(B));
    printf("C Front:%d\n", front(C));
    printf("A Back:%d\n", back(A));
    printf("B Back:%d\n", back(B));
    printf("C Back:%d\n", back(C));

    clear(A);
    clear(B);
    clear(C);

    printf("A Length:%d\n", length(A));
    printf("B Length:%d\n", length(B));
    printf("C Length:%d\n", length(C));
    printf("A Index:%d\n", index(A));
    printf("B Index:%d\n", index(B));
    printf("C Index:%d\n", index(C));

    freeList(&A);
    freeList(&B);
    freeList(&C);
}
