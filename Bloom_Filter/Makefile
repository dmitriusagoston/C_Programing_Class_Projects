CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: banhammer

banhammer: banhammer.o node.o bv.o bf.o speck.o parser.o bst.o ht.o
	$(CC) -o banhammer banhammer.o node.o bv.o bf.o speck.o parser.o bst.o ht.o -lm

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

bf.o: bf.c speck.c
	$(CC) $(CFLAGS) -c bf.c speck.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

bst.o: bst.c node.c
	$(CC) $(CFLAGS) -c bst.c node.c

ht.o: ht.c bst.c
	$(CC) $(CFLAGS) -c ht.c bst.c

clean:
	rm -f banhammer *.o

format:
	clang-format -i -style=file *.c *.h
