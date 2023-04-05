CFLAGS=-Wall -g -std=c90

all: poemabin

poemabin: poemabin.o
	gcc -o poemabin poemabin.o $(CFLAGS)

poemabin.o: poemabin.c
	gcc -c poemabin.c $(CFLAGS)

clean:
	rm *.o

purge:
	rm *.o poemabin
