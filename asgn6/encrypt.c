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
// prints help message
// returns nothing
void help() {
    printf("SYNOPSIS\n");
    printf("  Encrypts data using RSA encryption.\n");
    printf("  Encrypted data is decrypted by the decrypt program.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./encrypt [-hv] [-i infile] [-o outfile] -n pubkey\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -h             Display program help and usage.\n");
    printf("  -v             Display verbose program output.\n");
    printf("  -i infile      Input file of data to encrypt (default: stdin).\n");
    printf("  -o outfile     Output file for encrypted data (default: stdout).\n");
    printf("  -n pbfile      Public key file (default: rsa.pub).\n");
}

int main(int argc, char **argv) {
    // variables for cases
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    bool verbose = false;
    FILE *pbfile = NULL;
    bool defaultpb = true;
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
        // specify pbfile
        case 'n':
            if ((pbfile = fopen(optarg, "r")) == NULL) {
                printf("Error: failed to open pbfile\n");
                return -1;
            } else {
                defaultpb = false;
                pbfile = fopen(optarg, "r");
                break;
            }
        }
    }
    // case for default pbfile
    if (defaultpb) {
        pbfile = fopen("rsa.pub", "r");
    }
    mpz_t n, e, s, m;
    mpz_inits(n, e, s, m, NULL);
    char username[256] = { 0 };
    rsa_read_pub(n, e, s, username, pbfile);
    // verbose printing
    if (verbose) {
        gmp_printf("user = %s\n", username);
        gmp_printf("s (%d bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%d bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
    }
    mpz_set_str(m, username, 62);
    // verify signature
    if (!rsa_verify(m, s, e, n)) {
        printf("Error: signature could not be verified\n");
        return -1;
    }
    rsa_encrypt_file(infile, outfile, n, e);
    fclose(pbfile);
    fclose(infile);
    fclose(outfile);
    mpz_clears(n, e, s, m, NULL);
    return 0;
}
