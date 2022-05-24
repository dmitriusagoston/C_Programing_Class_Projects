//-----------------------------------------------------------------------------
// Dmitrius Agoston
// dagoston
// pa5
//
// Shuffle.cpp
// File for preforming the perfect shuffle
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include"List.h"
using namespace std;

    void shuffle(List& D) {
        List A, B;
        D.moveFront();
        int n = D.length();
        for (int i = 0; i < (n / 2); i++) {
            A.insertBefore(D.peekNext());
            D.moveNext();
        }
        for (int i = (n / 2); i < n; i++) {
            B.insertBefore(D.peekNext());
            D.moveNext();
        }
        D.clear();
        A.moveFront();
        B.moveFront();
        for (int i = 0; i < A.length(); i++) {
            D.insertBefore(B.peekNext());
            D.insertBefore(A.peekNext());
            A.moveNext();
            B.moveNext();
        }
        if (n % 2 == 1) {
            D.insertBefore(B.peekNext());
        }
    }


int main(int argc, char * argv[]) {
    // check command line for correct number of arguments
    if( argc != 2 ){
    cerr << "Usage: " << argv[0] << " Number of Decks" << endl;
    return(EXIT_FAILURE);
    }
    int n = atoi(argv[1]);

    std::cout << "deck size       shuffle count" << endl;
    std::cout << "------------------------------" << endl;

    List D, C;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            D.insertBefore(j);
        }
        C = D;
        int count = 1;
        shuffle(C);
        while ((C == D) != true) {
            shuffle(C);
            count++;
        }
        int nn = i;
        int min = 0;
        while (nn >= 10) {
            nn /= 10;
            min++;
        }
        std::cout << std::setw(1) << ' ' << i;
        std::cout << std::setw(15 - min) << ' ' << left << count;
        if (i < n) {
            std::cout << '\n';
        }
        D.clear();
    }
    return 0;
}
