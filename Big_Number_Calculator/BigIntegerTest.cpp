//-----------------------------------------------------------------------------
//  BigIntegerClient.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){
    BigInteger A = BigInteger("-111122223333");
    BigInteger B = BigInteger("111122223334");
    BigInteger C = A-A;
    BigInteger D = A-B;
    BigInteger E = B-A;
    BigInteger F = A*B;
    BigInteger G = F;
    BigInteger G += A*A;
    BigInteger H = B*A;
    BigInteger I = A*B*G+D-C+F*H;

    std::cout << A << endl;
    std::cout << B << endl;
    std::cout << C << endl;
    std::cout << D << endl;
    std::cout << E << endl;
    std::cout << F << endl;
    std::cout << G << endl;
    std::cout << H << endl;
    std::cout << I << endl;
    return 0;
}
