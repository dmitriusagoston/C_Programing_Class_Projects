#include "io.h"
#include "code.h"
#include "defines.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

uint64_t bytes_read = 0;
uint64_t bytes_written = 0;
static uint8_t buf_read[BLOCK] = { 0 };
static uint64_t index_read = BLOCK * 8;
static uint8_t buf_written[BLOCK] = { 0 };
static uint64_t index_written = 0;
static uint64_t bytes = 0;

// reads the bytes given an infile, buffer and an amount of bytes
// returns the amount of bytes read
//
// infile: file to be read from
// buf: buffer to store the bytes
// nbytes: amount of bytes to be read
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int reads = 0;
    for (int i = 0; i < nbytes; i++) {
        if (!read(infile, buf + reads, 1)) {
            break;
        }
        reads++;
    }
    bytes_read += reads;
    return reads;
}

// writes the bytes to a given outfile, buffer and an amount of bytes
// returns the amount of bytes read
//
// infile: file to be read from
// buf: buffer to store the bytes
// nbytes: amount of bytes to be read
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int written = 0;
    for (int i = 0; i < nbytes; i++) {
        if (!write(outfile, buf + written, 1)) {
            break;
        }
        written++;
    }
    bytes_written += written;
    return written;
}

// reads a bit from the infile
// returns if bit was read or not
//
// infile: file to be read from
// bit: for value of reading the bit
bool read_bit(int infile, uint8_t *bit) {
    if (index_read >= BLOCK * 8) {
        bytes = read_bytes(infile, buf_read, BLOCK);
        index_read = 0;
    }
    if (index_read <= bytes * 8) {
        uint8_t curbit = 1;
        int byte = index_read / 8;
        curbit = curbit << (index_read % 8);
        curbit = curbit & buf_read[byte];
        *bit = curbit;
        index_read++;
        return true;
    } else {
        return false;
    }
    return true;
}

// writes code given an outfile and code
// returns nothing
//
// outfile: file to write codes to
// c: codes for writing
void write_code(int outfile, Code *c) {
    uint64_t beg = index_written;
    for (uint64_t i = beg; i < beg + code_size(c); i++) {
        // code block full, write and reset
        if (index_written >= BLOCK * 8) {
            write_bytes(outfile, buf_written, BLOCK);
            index_written = 0;
            for (int j = 0; j < BLOCK; j++) {
                buf_written[j] = 0;
            }
        }
        // add to written buffer
        uint64_t index = (i % (BLOCK * 8)) / 8;
        if (code_get_bit(c, i - beg)) {
            buf_written[index] |= 1 << i % 8;
        } else {
            buf_written[index] &= ~(1 << i % 8);
        }
        index_written++;
    }
    return;
}

// writes the leftover content of the buffer
// returns nothing
//
// outfile: file to write to
void flush_codes(int outfile) {
    uint64_t mod_eight = index_written % 8;
    buf_written[index_written / 8] &= ~((ALPHABET - 1) << (mod_eight + !(mod_eight) *8));
    write_bytes(outfile, buf_written, index_written / 8 + !!(mod_eight));
    return;
}
