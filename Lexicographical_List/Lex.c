#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"

int main(int argc, char** argv) {
    FILE *infile = NULL;
    FILE *outfile = NULL;
    if (argc != 3) {
        fprintf(stderr, "USAGE: ./Lex [infile] [outfile]\n");
        return -1;
    }
    if ((infile = fopen(argv[1], "r")) == NULL) {
        printf("Error: failed to open infile\n");
        return -1;
    }
    if ((outfile = fopen(argv[2], "w")) == NULL) {
        printf("Error: failed to open outfile\n");
        fclose(infile);
        return -1;
    }
    int numLines = 0;
    char cur;
    while ((cur = fgetc(infile)) != EOF) {
        if (cur == '\n') {
            numLines++;
        }
    }
    // reset file index
    fseek(infile, 0, SEEK_SET);
    char **lines = malloc(numLines * sizeof(char*));
    for (int i = 0; i < numLines; i++) {
        int start = ftell(infile);
        int len = 0;
        // get len of each line
        while (1) {
            cur = fgetc(infile);
            if (cur == EOF || cur == '\n') {
                break;
            }
            len++;
        }
        // allocate memory for line buffer
        lines[i] = malloc((len + 1) * sizeof(char));
        // read string into memory from previous start position
        fseek(infile, start, SEEK_SET);
        fread(lines[i], 1, len, infile);
        // Null terminated char
        lines[i][len] = 0;
        // compensate for new line
        fseek(infile, ftell(infile) + 1, SEEK_SET);
    }
    // list of indecies
    List sorted = newList();
    append(sorted, 0);
    for (int i = 1; i < numLines; i++) {
        moveFront(sorted);
        int cmp = 0;
        while((cmp = strcmp(lines[i], lines[get(sorted)])) > 0 && index(sorted) < length(sorted) - 1) {
            moveNext(sorted);
        }
        if (cmp <= 0) {
            insertBefore(sorted, i);
        } else {
            insertAfter(sorted, i);
        }
    }
    moveFront(sorted);
    int curIndex = 0;
    while ((curIndex = index(sorted)) != -1) {
        fprintf(outfile, "%s\n", lines[get(sorted)]);
        moveNext(sorted);
    }
    fclose(infile);
    fclose(outfile);
    freeList(&sorted);
    for (int i = 0; i < numLines; i++) {
        free(lines[i]);
    }
    free(lines);
    return 0;
}
