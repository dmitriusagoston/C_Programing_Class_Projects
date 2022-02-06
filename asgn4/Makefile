CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: tsp

tsp: tsp.o graph.o stack.o path.o
	$(CC) -o tsp tsp.o graph.o stack.o path.o -lm

tsp.o: tsp.c
	$(CC) $(CFLAGS) -c tsp.c

graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

path.o: path.c stack.c
	$(CC) $(CFLAGS) -c path.c stack.c

clean:
	rm -f tsp *.o

format:
	clang-format -i -style=file *.c *.h
