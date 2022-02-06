CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: encode decode

encode: encode.o node.o pq.o code.o io.o stack.o huffman.o
	$(CC) -o encode encode.o node.o pq.o code.o io.o stack.o huffman.o -lm

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode: decode.o node.o pq.o code.o io.o stack.o huffman.o
	$(CC) -o decode decode.o node.o pq.o code.o io.o stack.o huffman.o -lm

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

code.o: code.c
	$(CC) $(CFLAGS) -c code.c

io.o: io.c code.c
	$(CC) $(CFLAGS) -c io.c code.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

huffman.o: huffman.c
	$(CC) $(CFLAGS) -c huffman.c

clean:
	rm -f encode decode *.o

format:
	clang-format -i -style=file *.c *.h
