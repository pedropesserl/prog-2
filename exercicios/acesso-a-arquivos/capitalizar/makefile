CFLAGS=-Wall -g -std=c99 -Wextra

all: capitalizar

capitalizar: capitalizar.o
	gcc -o capitalizar capitalizar.o $(CFLAGS)

capitalizar.o: capitalizar.c
	gcc -c capitalizar.c $(CFLAGS)

clean:
	rm *.o

purge:
	rm *.o capitalizar
