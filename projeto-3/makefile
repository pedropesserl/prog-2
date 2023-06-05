CFLAGS = -Wall -Wextra -g

all: rle

rle: main.o
	gcc -o rle main.o

main.o: main.c
	gcc -c main.c $(CFLAGS)

clean:
	rm -f *.o

purge:
	rm -f *.o rle
