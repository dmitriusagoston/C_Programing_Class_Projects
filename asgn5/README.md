# asignment 5
The purpose of this program is to serve two main functions. Those functions being both encoding and decoding a file. The encoding of this program will first read an input file to be encoded. It will then find the Huffman encoding of its contents in order to compress the contents of the file. The decoding of this program has to receive a compressed file first that it is tasked with decoding. Once received, the decoder will take the file and decompress it, returning the file to its original size.

# building
To build this program:
- clone this repo
- cd into cse13s/asgn5/
- make

# running
To run this program:

USAGE
./encode [-v] [-h] [-i infile] [-o outfile]

OPTIONS
- -v             Print compression statistics.
- -h             Program usage and help.
- -i infile      Input file to compress.
- -o outfile     Output of compressed data.

USAGE
./decode [-v] [-h] [-i infile] [-o outfile]

OPTIONS
- -v             Print compression statistics.
- -h             Program usage and help.
- -i infile      Input file to decompress.
- -o outfile     Output of decompressed data.
