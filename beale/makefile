CFLAGS=-Wall -g -std=c90

all: beale

beale: beale.o
	gcc -o beale beale.o $(CFLAGS)

beale.o: beale.c
	gcc -c beale.c $(CFLAGS)

clean:
	rm *.o

purge:
	rm *.o beale
