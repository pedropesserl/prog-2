CFLAGS = -Wall -Wextra -g

all: rle

rle: rle.o
	gcc -o rle rle.o

rle.o: rle.c
	gcc -c rle.c $(CFLAGS)

clean:
	rm -f *.o

purge:
	rm -f *.o rle
