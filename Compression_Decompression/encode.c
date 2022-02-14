#include "header.h"
#include "node.h"
#include "pq.h"
#include "io.h"
#include "code.h"
#include "stack.h"
#include "huffman.h"
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define OPTIONS "-hvi:o:"

// prints the help statement
// returns nothing
void help() {
    printf("SYNOPSIS\n");
    printf("  A Huffman encoder.\n");
    printf("  Decompresses a file using the Huffman coding algorithm.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./encode [-h] [-i infile] [-o outfile]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -h             Program usage and help.\n");
    printf("  -v             Print compression statistics.\n");
    printf("  -i infile      Input file to compress.\n");
    printf("  -o outfile     Output of compressed data.\n");
}

int main(int argc, char **argv) {
    struct stat sb;
    // variables for cases
    int opt = 0;
    int infile = 0;
    int outfile = 1;
    bool stats = false;
    // parse through command line
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        // help statement
        case 'h': help(); return 0;
        // statistic printing
        case 'v': stats = true; break;
        // infile to read from
        case 'i':
            if ((infile = open(optarg, O_RDONLY)) == -1) {
                printf("Error: failed to open infile\n");
                return -1;
            }
            break;
        // outfile to write to
        case 'o': outfile = open(optarg, O_WRONLY | O_CREAT); break;
        }
    }
    Header header;
    fstat(infile, &sb);
    // creating histogram
    uint64_t hist[ALPHABET] = { 0 };
    hist[0]++;
    hist[255]++;
    uint8_t buf = 0;
    while (read_bytes(infile, &buf, 1)) {
        hist[(uint32_t) buf]++;
    }
    // building tree and codes
    Node *root = build_tree(hist);
    Code table[ALPHABET];
    build_codes(root, table);
    int unique = 0;
    // counting unique numbers
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            unique++;
        }
    }
    // making header and values
    header.magic = MAGIC;
    header.permissions = sb.st_mode;
    fchmod(outfile, sb.st_mode);
    header.tree_size = (3 * unique) - 1;
    header.file_size = sb.st_size;
    write_bytes(outfile, (uint8_t *) &header, 16);
    dump_tree(outfile, root);
    lseek(infile, 0, SEEK_SET);
    // re read through file and write code
    for (int64_t i = 0; i < sb.st_size; i++) {
        read_bytes(infile, &buf, 1);
        write_code(outfile, &table[(uint32_t) buf]);
    }
    // get any leftover
    flush_codes(outfile);
    // statistics printing
    if (stats) {
        fstat(outfile, &sb);
        fprintf(stdout, "Uncompressed file size: %lu bytes\n", header.file_size);
        fprintf(stdout, "Compressed file size: %lu bytes\n", bytes_written);
        fprintf(stdout, "Space saving: %.2f%%\n",
            100 * (1 - (bytes_written / (float) header.file_size)));
    }
    // free memory
    delete_tree(&root);
    close(infile);
    close(outfile);
    return 0;
}
