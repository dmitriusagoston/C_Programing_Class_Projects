//-----------------------------------------------------------------------------
// Dmitrius Agoston
// dagoston
// pa6
//
// Arithmetic.cpp
// File for preforming big integer arithemtic
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include"List.h"
#include"BigInteger.h"
using namespace std;

int main(int argc, char * argv[]) {
    ifstream in;
    ofstream out;
    string line;
    // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    } 
    getline(in, line);
    BigInteger A = BigInteger(line);
    getline(in,line);
    getline(in,line);
    BigInteger B = BigInteger(line);

    BigInteger C = A+B;
    BigInteger D = A-B;
    BigInteger E = A-A;
    BigInteger F = (A + A + A) - (B + B);
    BigInteger G = A*B;
    BigInteger H = A*A;
    BigInteger I = B*B;
    BigInteger J = (A * A * A * A);
    J = J+J+J+J+J+J+J+J+J;
    BigInteger K = (B * B * B * B * B);
    K = K+K+K+K+K+K+K+K+K+K+K+K+K+K+K+K;
    BigInteger L = J + K;

    out << A << "\n" << endl;
    out << B << "\n" << endl;
    out << C << "\n" << endl;
    out << D << "\n" << endl;
    out << E << "\n" << endl;
    out << F << "\n" << endl;
    out << G << "\n" << endl;
    out << H << "\n" << endl;
    out << I << "\n" << endl;
    out << L << "\n" << endl;

    in.close();
    out.close();
    return 0;
}
