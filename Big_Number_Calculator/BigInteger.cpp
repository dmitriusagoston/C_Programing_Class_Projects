//-----------------------------------------------------------------------------
// BigInteger.cpp
// Header file for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"
#include"BigInteger.h"

// Global Constants --------------------------------------------------------
const int power = 9;
const long base = 1000000000;

// Helper ------------------------------------------------------------------
// normalize()
// carries from right to left and returns sig fig
int normalize(List &L) {
    L.moveFront();
    while (L.position() < L.length()) {
        if (L.peekNext() == 0) {
            L.eraseAfter();
        } else {
            break;
        }
    }
    L.moveBack();
    while (L.position() > 0) {
        if (L.peekPrev() >= base || (L.peekPrev() < 0)) {
            int sig = 1;
            if (L.peekPrev() < 0) {
                sig = -1;
            }
            int carry = L.peekPrev() / base;
            if (sig == -1) {
                carry++;
            }
            // remove carry
            while (L.peekPrev() >= base || L.peekPrev() < 0) {
                int temp = L.peekPrev() % base;
                if (temp < 0) {
                    if (L.position() <= 1) {
                        return -1;
                    }
                    temp += base;
                }
                L.setBefore(temp);
            }
            L.movePrev();
            // front saftey
            if (L.position() <= 0) {
                L.insertAfter(carry * sig);
                L.moveNext();
            } else {
                L.setBefore(L.peekPrev() + carry * sig);
            }
            L.moveNext();
        }
        L.movePrev();
    }
    L.moveFront();
    if (L.length() == 0) {
        return 0;
    }
    int sig = L.peekNext();
    if (sig > 0) {
        return 1;
    } else if (sig < 0) {
        return -1;
    } else {
        return 0;
    }
}

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
    signum = 0;
    digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    if (s.empty() || (s.substr(0,1) == "0" && s.size() == 1)) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    digits = List();
    signum = 1;
    if (s[0] == '-') {
        signum = -1;
        s.erase(0,1);
    } else if (s[0] == '+') {
        s.erase(0,1);
    }
    if (s.empty() == 1) {
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }
    for (int i = 0; i < (int) s.size(); i++) {
        if (std::isdigit(s[i]) == 0) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }
    for (int i = s.size() - power; i >= 1 - power; i -= power) {
        std::string str = "";
        // normal case
        if (i > 0) {
            str = s.substr (i, power);
            digits.insertAfter(std::stol (str));
        // front case
        } else {
            str = s.substr(0, i + power);
            digits.insertAfter(std::stol (str));
        }
    }
    normalize(digits);
    if (digits.front() > 0 && signum == -1) {
        digits.moveFront();
        digits.setAfter(digits.peekNext() * -1);
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    signum = N.signum;
    digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const {
    return signum;
}
// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    if (signum < N.signum) {
        return -1;
    }
    if (signum > N.signum) {
        return 1;
    }
    if (signum == 0 && N.signum == 0) {
        return 0;
    }
    List A = digits;
    List B = N.digits;
    for (int i = 0; i < A.length(); i++) {
        if (A.peekNext() < B.peekNext()) {
            if (signum == -1) {
                return 1;
            }
            return -1;
        } else if (A.peekNext() > B.peekNext()) {
            if (signum == -1) {
                return -1;
            }
            return 1;
        } else {
            A.moveNext();
            B.moveNext();
        }
    }
    return 0;
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
    if (signum == 0) {
        return;
    } else if (signum == 1) {
        signum = -1;
        digits.moveFront();
        digits.setAfter(digits.peekNext() * -1);
    } else {
        signum = 1;
        digits.setAfter(digits.peekNext() * -1);
    }
}

// BigInteger Arithmetic operations ----------------------------------------

// negateList()
// changes the sign of each int
void negateList(List &L) {
    L.moveFront();
    for (int i = 0; i < L.length(); i++) {
        if (L.position() == 0 && L.peekNext() < 0) {
            continue;
        }
        L.setAfter(L.peekNext() * -1);
        L.moveNext();
    }
}

void sumList(List &S, List A, List B, int sig) {
    A.moveBack();
    B.moveBack();
    S.moveFront();
    int len = A.length();
    // case for B being bigger
    if (A.length() < B.length()) {
        len = B.length();
    }
    if (sig == -1) {
        negateList(B);
    }
    for (int i = 0; i < len; i++) {
        long Acur = 0;
        long Bcur = 0;
        if (A.position() > 0) {
            Acur = A.peekPrev();
            A.movePrev();
        }
        if (B.position() > 0) {
            Bcur = B.peekPrev();
            B.movePrev();
        }
        S.insertAfter(Acur + Bcur);
    }
    S.moveFront();
}

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger sum;
    List A = digits;
    List B = N.digits;
    if (signum == 0) {
        sum = N;
        return sum;
    }
    if (N.signum == 0) {
        sum.digits = digits;
        sum.signum = signum;
        return sum;
    }
    if (signum != N.signum) {
        if (N.signum == -1) {
            B.moveFront();
            B.setAfter(B.peekNext() * -1);
            sumList(sum.digits, A, B, -1);
        }
        if (signum == -1) {
            A.moveFront();
            A.setAfter(A.peekNext() * -1);
            sumList(sum.digits, A, B, -1);
        }
    } else {
        sumList(sum.digits, A, B, 1);
    }
    sum.digits.moveFront();
    sum.signum = normalize(sum.digits);
    return sum;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger dif;
    bool neg = false;
    List minus = N.digits;
    if (this->compare(N) < 0) {
        neg = true;
    }
    //negateList(neg);
    if (this->compare(N) == 0) {
        dif.makeZero();
    } else {
        if (neg) {
            sumList(dif.digits, minus, digits, -1);
        } else {
            sumList(dif.digits, digits, minus, -1);
        }
        dif.signum = normalize(dif.digits);
    }
    if (neg) {
        dif.negate();
    }
    return dif;
}

// scalarMultList()
// Multiplies L by m
void scalarMultList(List &L, ListElement m) {
    L.moveBack();
    for (int i = L.length(); i > 0; i--) {
        long cur = L.peekPrev();
        L.setBefore(cur * m);
        L.movePrev();
    }
}

// shiftList()
// shifts list by p
void shiftList(List &L, int p) {
    L.moveFront();
    List Copy = L;
    for (int i = 0; i < p; i ++) {
        L.insertAfter(0);
    }
    Copy.moveFront();
    for (int i = 0; i < L.length(); i++) {
        long cur = 0;
        if (Copy.position() < Copy.length()) {
            cur = Copy.peekNext();
            Copy.moveNext();
        }
        L.setAfter(cur);
        L.moveNext();
    }
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const { 
    BigInteger prod;
    if (signum == 0 || N.signum == 0) {
        prod.makeZero();
        return prod;
    }
    List big, small;
    // find larger
    if (compare(N) <= 0) {
        big = N.digits;
        small = digits;
    } else {
        big = digits;
        small = N.digits;
    }
    bool bigneg = false;
    bool smallneg = false;
    small.moveFront();
    big.moveFront();
    if (small.peekNext() < 0) {
        smallneg = true;
        small.setAfter(small.peekNext() * -1);
    }
    if (big.peekNext() < 0) {
        bigneg = true;
        big.setAfter(big.peekNext() * -1);
    }
    small.moveBack();
    big.moveBack();
    for (int i = 0; i < small.length(); i++) {
        long scalar = small.peekPrev();
        List tempsum;
        List temp = big;
        scalarMultList(temp, scalar);
        small.movePrev();
        shiftList(temp, i);
        sumList(tempsum, prod.digits, temp, 1);
        prod.digits = tempsum;
        prod.signum = normalize(prod.digits);
    }
    if (smallneg && bigneg) {
        prod.signum = normalize(prod.digits);
    } else if (smallneg || bigneg) {
        prod.negate();
        prod.signum = normalize(prod.digits);
    } else {
        prod.signum = normalize(prod.digits);
    }
    return prod;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    std::string s = "";

    if (signum == 0) {
        s = "0";
        return s;
    }
    digits.moveFront();
    for (int i = 0; i < digits.length(); i++) {
        if (digits.peekNext() < base && digits.position() != 0) {
            if (digits.peekNext() == 0) {
               for (int j = 0; j < power; j++) {
                    s.append("0");
                }
               digits.moveNext();
                continue;
            }
            int temp = base / 10;
            while (digits.peekNext() < temp) {
                s.append("0");
                temp /= 10;
            }
        }
        s.append(std::to_string(digits.peekNext()));
        digits.moveNext();
    }
    return s;
}

// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == 0) {
        return true;
    }
    return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == -1) {
        return true;
    }
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) <= 0) {
        return true;
    }
    return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == 1) {
        return true;
    }
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) >= 0) {
        return true;
    }
    return false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.BigInteger::add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.BigInteger::sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A.BigInteger::mult(B);
    return A;
}
