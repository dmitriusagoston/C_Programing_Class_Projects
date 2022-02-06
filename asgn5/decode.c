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
    printf("  A Huffman decoder.\n");
    printf("  Decompresses a file using the Huffman coding algorithm.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./decode [-h] [-i infile] [-o outfile]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -h             Program usage and help.\n");
    printf("  -v             Print compression statistics.\n");
    printf("  -i infile      Input file to decompress.\n");
    printf("  -o outfile     Output of decompressed data.\n");
}

int main(int argc, char **argv) {
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
    // header build
    Node *root;
    Header header;
    header.magic = 0;
    header.permissions = 0;
    header.tree_size = 0;
    header.file_size = 0;
    uint8_t buf = 0;
    // reading header
    for (uint32_t lcv = 0; lcv <= 15; lcv++) {
        read_bytes(infile, &buf, 1);
        if (lcv < 4) {
            header.magic |= buf << (lcv * 8);
        } else if (lcv < 6) {
            header.permissions |= buf << ((lcv - 4) * 8);
        } else if (lcv < 8) {
            header.tree_size |= buf << ((lcv - 6) * 8);
        } else {
            header.file_size |= buf << ((lcv - 8) * 8);
        }
    }
    // check for magic number
    if (header.magic != MAGIC) {
        printf("Invalid magic number.\n");
        return -1;
    }
    fchmod(outfile, header.permissions);
    uint8_t *tree = calloc(header.tree_size, sizeof(uint8_t));
    // fill tree
    for (uint64_t i = 0; i < header.tree_size; i++) {
        read_bytes(infile, &buf, 1);
        tree[i] = buf;
    }
    // rebuild tree
    root = rebuild_tree(header.tree_size, tree);
    Node *cur = root;
    uint64_t symbols = 0;
    uint8_t bit = 0;
    // decompress file
    while (symbols < header.file_size) {
        read_bit(infile, &bit);
        // right case
        if (bit) {
            cur = cur->right;
            // left case
        } else if (!bit) {
            cur = cur->left;
        }
        if (!cur->left && !cur->right) {
            write_bytes(outfile, &(cur->symbol), 1);
            cur = root;
            symbols++;
        }
    }
    // statistic printing
    if (stats) {
        struct stat sb;
        fstat(infile, &sb);
        fprintf(stdout, "Compressed file size: %lu bytes\n", sb.st_size);
        fprintf(stdout, "Decompressed file size: %lu bytes\n", header.file_size);
        fprintf(
            stdout, "Space saving: %.2f%%\n", 100 * (1 - (sb.st_size / (float) header.file_size)));
    }
    // free memory
    delete_tree(&root);
    free(tree);
    close(infile);
    close(outfile);
    return 0;
}
