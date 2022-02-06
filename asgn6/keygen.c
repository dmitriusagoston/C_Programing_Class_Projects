#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"
#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <getopt.h>
#include <sys/stat.h>

#define OPTIONS "-hvb:i:n:d:s:"

// prints help statement
// returns nothing
void help() {
    printf("SYNOPSIS\n");
    printf("  Generates an RSA public/private key pair.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./keygen [-hv] [-b bits] -n pbfile -d pvfile\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -h             Display program help and usage.\n");
    printf("  -v             Display verbose program output.\n");
    printf("  -b bits        Minimum bits needed for public key n (default: 256).\n");
    printf("  -i confidence  Miller-Rabin iterations for testing primes (default: 50).\n");
    printf("  -n pbfile      Public key file (default: rsa.pub).\n");
    printf("  -d pvfile      Private key file (default: rsa.priv).\n");
    printf("  -s seed        Random seed for testing.\n");
}

int main(int argc, char **argv) {
    // variables for cases
    int opt = 0;
    FILE *pbfile = NULL;
    FILE *pvfile = NULL;
    bool verbose = false;
    bool defaultpb = true;
    bool defaultpv = true;
    uint64_t iters = 50;
    uint64_t seed = time(NULL);
    uint64_t nbits = 256;
    // parse through command line
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        // help statement
        case 'h': help(); return 0;
        // minimum number of bits
        case 'b': nbits = atoi(optarg);
        // verbose printing
        case 'v': verbose = true; break;
        // number of iterations
        case 'i': iters = atoi(optarg); break;
        // seed for random state
        case 's': seed = atoi(optarg); break;
        // specify pbfile
        case 'n':
            if ((pbfile = fopen(optarg, "w")) == NULL) {
                printf("Error: failed to open pbfile\n");
                return -1;
            } else {
                defaultpb = false;
                pbfile = fopen(optarg, "w");
                break;
            }
        // specify pvfile
        case 'd':
            if ((pvfile = fopen(optarg, "w")) == NULL) {
                printf("Error: failed to open pvfile\n");
                return -1;
            } else {
                defaultpv = false;
                pvfile = fopen(optarg, "w");
                break;
            }
        }
    }
    // check for default pbfile
    if (defaultpb) {
        pbfile = fopen("rsa.pub", "w");
    }
    // check for default pvfile
    if (defaultpv) {
        pvfile = fopen("rsa.priv", "w");
    }
    // get permission
    int perm = fileno(pvfile);
    fchmod(perm, 0600);
    randstate_init(seed);
    mpz_t p, q, n, e, d, m, s;
    mpz_inits(p, q, n, e, d, m, s, NULL);
    rsa_make_pub(p, q, n, e, nbits, iters);
    rsa_make_priv(d, e, p, q);
    // get username
    char *username = getenv("USER");
    mpz_set_str(m, username, 62);
    rsa_sign(s, m, d, n);
    rsa_write_pub(n, e, s, username, pbfile);
    rsa_write_priv(n, d, pvfile);
    // verbose printing
    if (verbose) {
        gmp_printf("user = %s\n", username);
        gmp_printf("s (%d bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("p (%d bits) = %Zd\n", mpz_sizeinbase(p, 2), p);
        gmp_printf("q (%d bits) = %Zd\n", mpz_sizeinbase(q, 2), q);
        gmp_printf("n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%d bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
        gmp_printf("d (%d bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }
    fclose(pbfile);
    fclose(pvfile);
    randstate_clear();
    mpz_clears(p, q, n, e, d, m, s, NULL);
    return 0;
}
