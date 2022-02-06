CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: mathlib-test

mathlib-test: mathlib-test.o bbp.o e.o euler.o madhava.o newton.o viete.o
	$(CC) -o mathlib-test mathlib-test.o e.o madhava.o newton.o euler.o bbp.o viete.o -lm

bbp.o: bbp.c
	$(CC) $(CFLAGS) -c bbp.c

e.o: e.c
	$(CC) $(CFLAGS) -c e.c

euler.o: euler.c
	$(CC) $(CFLAGS) -c euler.c newton.c

madhava.o: madhava.c
	$(CC) $(CFLAGS) -c madhava.c newton.c

mathlib-test.o: mathlib-test.c
	$(CC) $(CFLAGS) -c mathlib-test.c

newton.o: newton.c
	$(CC) $(CFLAGS) -c newton.c

viete.o: viete.c
	$(CC) $(CFLAGS) -c viete.c newton.c

clean:
	rm -f mathlib-test mathlib.h.gch *.o

format:
	clang-format -i -style=file *.c *.h
