CFLAGS=-Wall -Wextra -g -std=c90

all: num_caracteres

num_caracteres: num_caracteres.o
	gcc -o num_caracteres num_caracteres.o $(CFLAGS)

num_caracteres.o: num_caracteres.c
	gcc -c num_caracteres.c $(CFLAGS)

clean:
	rm *.o

purge:
	rm *.o num_caracteres
