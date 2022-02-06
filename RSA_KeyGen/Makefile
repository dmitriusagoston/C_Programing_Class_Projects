CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lgmp -lm

all: encrypt decrypt keygen

encrypt: encrypt.o randstate.o numtheory.o rsa.o
	$(CC) -o encrypt encrypt.o randstate.o numtheory.o rsa.o $(LFLAGS)

encrypt.o: encrypt.c
	$(CC) $(CFLAGS) -c encrypt.c

decrypt: decrypt.o randstate.o numtheory.o rsa.o
	$(CC) -o decrypt decrypt.o randstate.o numtheory.o rsa.o $(LFLAGS)

decrypt.o: decrypt.c
	$(CC) $(CFLAGS) -c decrypt.c

keygen: keygen.o randstate.o numtheory.o rsa.o
	$(CC) -o keygen keygen.o randstate.o numtheory.o rsa.o $(LFLAGS)

keygen.o: keygen.c
	$(CC) $(CFLAGS) -c keygen.c

randstate.o: randstate.c
	$(CC) $(CFLAGS) -c randstate.c

numtheory.o: numtheory.c randstate.c
	$(CC) $(CFLAGS) -c numtheory.c randstate.c

rsa.o: rsa.c numtheory.c randstate.c
	$(CC) $(CFLAGS) -c rsa.c numtheory.c randstate.c

clean:
	rm -f encrypt decrypt keygen *.o

format:
	clang-format -i -style=file *.c *.h
