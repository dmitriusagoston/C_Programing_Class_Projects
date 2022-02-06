#include "rsa.h"
#include "randstate.h"
#include "numtheory.h"
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <math.h>

// creates a public key
// returns nothing
//
// p: variable to store first prime
// q: variable to store second prime
// n: variable to store the product of the two primes
// e: the public exponent
// nbits: the number of bits to use when making the primes
// iters: number of iterations to preform to check if prime
void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    mpz_t range, coprime, totient, rand;
    mpz_inits(range, coprime, totient, rand, NULL);
    mpz_set_ui(range, ((3 * nbits) / 4) - (nbits / 4));
    mpz_urandomm(p, state, range);
    mpz_add_ui(p, p, nbits / 4);
    mpz_ui_sub(q, nbits, p);
    make_prime(p, mpz_get_ui(p), iters);
    make_prime(q, mpz_get_ui(q), iters);
    mpz_mul(n, p, q);
    // remove 1 for p - 1 and q - 1
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(totient, p, q);
    // add back 1 to p and q to restore original value
    mpz_add_ui(p, p, 1);
    mpz_add_ui(q, q, 1);
    do {
        mpz_urandomb(rand, state, nbits);
        gcd(coprime, rand, totient);
        if (mpz_cmp_ui(coprime, 1) == 0) {
            break;
        }
    } while (1);
    mpz_set(e, rand);
    mpz_clears(range, coprime, totient, rand, NULL);
    return;
}

// write the public key to the pbfile
// returns nothing
//
// n: the product of the two primes
// e: the public exponent
// s: the signature of the key
// username: user's name for public key
// pbfile: file to write the public key to
void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);
    fprintf(pbfile, "%s\n", username);
    return;
}

// reads the public key from the pbfile
// returns nothing
//
// n: the product of the two primes
// e: the public exponent
// s: the signature of the key
// username: user's name for public key
// pbfile: file to read the public key from
void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n", n);
    gmp_fscanf(pbfile, "%Zx\n", e);
    gmp_fscanf(pbfile, "%Zx\n", s);
    fscanf(pbfile, "%s\n", username);
    return;
}

// creates a private key
// returns nothing
//
// d: variable that holds the private key
// e: the public exponent
// p: the first prime value
// q: the second prime value
void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t totient;
    mpz_init(totient);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(totient, p, q);
    mpz_add_ui(p, p, 1);
    mpz_add_ui(q, q, 1);
    mod_inverse(d, e, totient);
    mpz_clear(totient);
    return;
}

// write the private key to the pvfile
// returns nothing
//
// n: the product of the two primes
// d: the private key
// pvfile: file to write the private key to
void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
    return;
}

// read the private key to the pvfile
// returns nothing
//
// n: the product of the two primes
// d: the private key
// pvfile: file to read the private key from
void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n", n);
    gmp_fscanf(pvfile, "%Zx\n", d);
    return;
}

// preforms RSA encryption
// returns nothing
//
// c: ciphertext to be computed
// m: message to be encrypted
// e: the public exponent
// n: value to mod by
void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
    return;
}

// preforms RSA encryption on a given file
// returns nothing
//
// infile: file to be encrypted
// outfile: newly encrypted file
// n: value to mod by
// e: the public exponent
void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    mpz_t c, m;
    mpz_inits(c, m, NULL);
    uint32_t k = mpz_sizeinbase(n, 2);
    k--;
    k /= 8;
    uint8_t *block = (uint8_t *) calloc(k, sizeof(uint8_t));
    block[0] = 0xFF;
    uint64_t j = 1;
    do {
        if (j == 0) {
            break;
        }
        j = fread(block + 1, 1, k - 1, infile);
        mpz_import(m, j + 1, 1, 1, 1, 0, block);
        rsa_encrypt(c, m, e, n);
        gmp_fprintf(outfile, "%Zx\n", c);
    } while (1);
    mpz_clears(c, m, NULL);
    free(block);
    return;
}

// preforms RSA decryption
// returns nothing
//
// m: message to be decrypted
// c: ciphertext to be computed
// d: the priavte key
// n: value to mod by
void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
    return;
}

// preforms RSA decryption on a given encrypted file
// returns nothing
//
// infile: file to be decrypted
// outfile: newly decrypted file
// n: value to mod by
// d: the private key
void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    mpz_t c;
    mpz_init(c);
    uint32_t k = mpz_sizeinbase(n, 2);
    k--;
    k /= 8;
    uint8_t *block = (uint8_t *) calloc(k, sizeof(uint8_t));
    uint64_t j = 0;
    do {
        mpz_set_ui(c, 0);
        gmp_fscanf(infile, "%Zx\n", c);
        rsa_decrypt(c, c, d, n);
        mpz_export(block, &j, 1, 1, 1, 0, c);
        if (j == 0) {
            break;
        }
        for (uint32_t i = 1; i < j; i++) {
            fprintf(outfile, "%c", block[i]);
        }
    } while (1);
    mpz_clear(c);
    free(block);
    return;
}

// preforms RSA signing
// returns nothing
//
// s: the rsa signature
// m: the signing message
// d: the private key
// n: value to mod by
void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
    return;
}

// preforms RSA verification
// returns nothing
//
// m: the expected message
// s: the rsa signature
// e: the public exponent
// n: value to mod by
bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_init(t);
    pow_mod(t, s, e, n);
    if (mpz_cmp(t, m) == 0) {
        mpz_clear(t);
        return true;
    }
    mpz_clear(t);
    return false;
}
