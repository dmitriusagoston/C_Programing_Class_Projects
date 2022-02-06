CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: sorting

sorting: sorting.o insert.o shell.o heap.o quick.o stats.o
	$(CC) -o sorting sorting.o insert.o shell.o heap.o quick.o stats.o -lm

stats.o: stats.c
	$(CC) $(CFLAGS) -c stats.c

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

insert.o: insert.c
	$(CC) $(CFLAGS) -c insert.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

clean:
	rm -f sorting *.o

format:
	clang-format -i -style=file *.c *.h
