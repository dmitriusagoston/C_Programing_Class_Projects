#include "numtheory.h"
#include "randstate.h"
#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Finds the greatest common denominator
// returns nothing
//
// d: stored value of greatest common denominator
// a: first number for greatest common denominator
// b: second number for greatest common denominator
void gcd(mpz_t d, mpz_t a, mpz_t b) {
    mpz_t t, ta, tb;
    mpz_inits(t, ta, tb, NULL);
    mpz_set(ta, a);
    mpz_set(tb, b);
    while (mpz_cmp_ui(tb, 0) > 0) {
        mpz_set(t, tb);
        mpz_mod(tb, ta, tb);
        mpz_set(ta, t);
    }
    mpz_set(d, ta);
    mpz_clears(t, ta, tb, NULL);
    return;
}

// computes the inverse of the modulo of two variables
// returns nothing
//
// i: variable where the inverse is stored
// a: number that i being modded
// n: amount number is being modded by
void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
    mpz_t r, rr, t, tt;
    mpz_inits(r, rr, t, tt, NULL);
    mpz_set(r, n);
    mpz_set(rr, a);
    mpz_set_si(tt, 1);
    while (mpz_cmp_si(rr, 0) != 0) {
        mpz_t q, temp, tempo;
        mpz_inits(q, temp, tempo, NULL);
        mpz_fdiv_q(q, r, rr);
        mpz_set(temp, rr);
        mpz_set(tempo, tt);
        mpz_submul(r, q, rr);
        mpz_submul(t, q, tt);
        mpz_set(rr, r);
        mpz_set(tt, t);
        mpz_set(r, temp);
        mpz_set(t, tempo);
        mpz_clears(q, temp, tempo, NULL);
    }
    mpz_set(i, t);
    // check for no modular inverse
    if (mpz_cmp_si(r, 1) > 0) {
        mpz_set_si(i, 0);
    }
    if (mpz_cmp_si(t, 0) < 0) {
        mpz_add(i, t, n);
    }
    mpz_clears(r, t, rr, tt, NULL);
    return;
}

// compues modular exponentiation
// returns nothing
//
// out: variable where the result of the modular exponentiation is stored
// base: the base that will be raised
// exponent: amount to raise the base by
// modulus: amount to mod the expression
void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    mpz_t p, is_odd, e, v;
    mpz_inits(p, is_odd, e, v, NULL);
    mpz_set_ui(v, 1);
    mpz_set(p, base);
    mpz_set(e, exponent);
    while (mpz_cmp_ui(e, 0) > 0) {
        mpz_mod_ui(is_odd, e, 2);
        // check if odd
        if (mpz_cmp_ui(is_odd, 0) > 0) {
            mpz_mul(v, v, p);
            mpz_mod(v, v, modulus);
        }
        mpz_mul(p, p, p);
        mpz_mod(p, p, modulus);
        mpz_fdiv_q_ui(e, e, 2);
    }
    mpz_set(out, v);
    mpz_clears(p, is_odd, e, v, NULL);
    return;
}

// conducts Miller-Rabin primality test to determine whether a number is prime or not
// returns true or false if value given is prime
//
// n: value to be determined prime or not
// iters: number of iterations to preform to check if prime
bool is_prime(mpz_t n, uint64_t iters) {
    // case for 0 and 1
    if (mpz_cmp_ui(n, 2) < 0) {
        return false;
    }
    // case for 2 and 3
    if (mpz_cmp_ui(n, 4) < 0) {
        return true;
    }
    mpz_t s, r, t, m, a, y, dec, decr, two;
    mpz_inits(s, r, t, m, a, y, dec, decr, two, NULL);
    mpz_sub_ui(t, n, 1);
    mpz_set_ui(two, 2);
    // determine eveness of the number
    while (1) {
        mpz_mod_ui(m, t, 2);
        if (mpz_cmp_ui(m, 0) > 0) {
            // odd
            mpz_set(r, t);
            break;
        } else {
            // even
            mpz_add_ui(s, s, 1);
            mpz_fdiv_q_ui(t, t, 2);
        }
    }
    // preform test
    for (uint64_t i = 0; i < iters; i++) {
        mpz_sub_ui(a, n, 3);
        mpz_urandomm(a, state, a);
        mpz_add_ui(a, a, 2);
        pow_mod(y, a, r, n);
        mpz_sub_ui(dec, n, 1);
        if (mpz_cmp_ui(y, 1) != 0 && mpz_cmp(y, dec) != 0) {
            mpz_set_ui(t, 1);
            mpz_sub_ui(decr, s, 1);
            while (mpz_cmp(t, decr) <= 0 && mpz_cmp(y, dec) != 0) {
                pow_mod(y, y, two, n);
                if (mpz_cmp_ui(y, 1) == 0) {
                    mpz_clears(s, r, t, m, a, y, dec, decr, two, NULL);
                    return false;
                }
                mpz_add_ui(t, t, 1);
            }
            if (mpz_cmp(y, dec) != 0) {
                mpz_clears(s, r, t, m, a, y, dec, decr, two, NULL);
                return false;
            }
        }
    }
    mpz_clears(s, r, t, m, a, y, dec, decr, two, NULL);
    return true;
}

// creates a prime number
// returns nothing
//
// p: variable to store newly created prime number
// bits: the minimum number of bits the prime number can be
// iters: number of iterations to preform to check if prime
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    while (1) {
        mpz_urandomb(p, state, bits + 2);
        if (mpz_sizeinbase(p, 2) >= bits && is_prime(p, iters)) {
            break;
        }
    }
    return;
}
