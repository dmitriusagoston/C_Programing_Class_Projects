//-----------------------------------------------------------------------------
// Dmitrius Agoston
// dagoston
// pa5
//
// LestTest.cpp
// Test harness for List ADT.
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main() {
    int n = 20;
    List A, B, C, D;
    for (int i = 0; i <= n; i++) {
        A.insertBefore(i);
        B.insertAfter(i);
        C.insertBefore(n - i);
        D.insertAfter(n - i);
    }

    cout << "A:\n" << A << endl; 
    cout << "B:\n" << B << endl; 
    cout << "C:\n" << C << endl; 
    cout << "D:\n" << D << endl; 

    A.moveFront();
    C.moveFront();
    B.moveBack();
    D.moveBack();
    for (int i = 0; i < 5; i++) {
        A.moveNext();
        C.moveNext();
        B.movePrev();
        D.movePrev();
    }

    A.eraseBefore();
    A.setBefore(-2);
    A.insertAfter(-1);
    B.eraseBefore();
    B.setBefore(-2);
    B.insertAfter(-1);
    C.eraseAfter();
    C.setAfter(-2);
    C.insertBefore(-1);
    D.eraseAfter();
    D.setAfter(-2);
    D.insertBefore(-1);

    cout << "A: " << A.position() << " B: " << B.position() << " C: " << C.position() << " D: " << D.position();
    cout << endl;
    cout << "A:\n" << A << endl; 
    cout << "B:\n" << B << endl; 
    cout << "C:\n" << C << endl; 
    cout << "D:\n" << D << endl; 

    A.moveFront();
    B.moveFront();
    C.moveBack();
    D.moveBack();
    cout << "A: " << A.findNext(-1) << " B: " << B.findNext(-1) << " C: " << C.findPrev(-1) << " D: " << D.findPrev(-1);
    cout << endl;

    List E = A;
    E.moveFront();
    for (int i = 0; i < E.length(); i++) {
        if (i % 3 == 0) {
            E.insertAfter(3);
        }
        E.moveNext();
    }
    cout << "E:\n" << E << endl; 
    A.concat(E);
    E.cleanup();
    cout << "A:\n" << A << endl; 
    cout << "E:\n" << E << endl; 

    if (E == A) {
        cout << "E equals A";
    } else {
        cout << "E does not equal A";
    }
    cout << endl;

    A.moveFront();
    E.moveBack();
    cout << "Peek next A: " << A.peekNext() << " Peek prev E: " << E.peekPrev() << endl;
    return 0;
}
