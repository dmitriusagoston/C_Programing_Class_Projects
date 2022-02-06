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

#define OPTIONS "-hvi:o:n:"

// prints help statement
void help() {
    printf("SYNOPSIS\n");
    printf("  Decrypts data using RSA decryption.\n");
    printf("  Encrypted data is encrypted by the encrypt program.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./encrypt [-hv] [-i infile] [-o outfile] -n privkey\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -h             Display program help and usage.\n");
    printf("  -v             Display verbose program output.\n");
    printf("  -i infile      Input file of data to encrypt (default: stdin).\n");
    printf("  -o outfile     Output file for encrypted data (default: stdout).\n");
    printf("  -n pbfile      Private key file (default: rsa.pub).\n");
}

int main(int argc, char **argv) {
    // variables for cases
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    bool verbose = false;
    FILE *pvfile = NULL;
    bool defaultpv = true;
    // parse through command line
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        // help statement
        case 'h': help(); return 0;
        // verbose printing
        case 'v': verbose = true; break;
        // specify infile
        case 'i':
            if ((infile = fopen(optarg, "r")) == NULL) {
                printf("Error: failed to open infile\n");
                return -1;
            } else {
                infile = fopen(optarg, "r");
                break;
            }
        // specify outfile
        case 'o':
            if ((outfile = fopen(optarg, "w")) == NULL) {
                printf("Error: failed to open outfile\n");
                return -1;
            } else {
                outfile = fopen(optarg, "w");
                break;
            }
        // specify pvfile
        case 'n':
            if ((pvfile = fopen(optarg, "r")) == NULL) {
                printf("Error: failed to open pvfile\n");
                return -1;
            } else {
                defaultpv = false;
                pvfile = fopen(optarg, "r");
                break;
            }
        }
    }
    // case for default pvfile
    if (defaultpv) {
        pvfile = fopen("rsa.priv", "r");
    }
    mpz_t n, d;
    mpz_inits(n, d, NULL);
    rsa_read_priv(n, d, pvfile);
    // verbose printing
    if (verbose) {
        gmp_printf("n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("d (%d bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }
    rsa_decrypt_file(infile, outfile, n, d);
    fclose(infile);
    fclose(outfile);
    fclose(pvfile);
    mpz_clears(n, d, NULL);
    return 0;
}
