CFLAGS=-Wall -Wextra -g -std=c90

all: escrever ler imprimir

escrever: escrever.o
	gcc -o escrever escrever.o $(CFLAGS)

ler: ler.o quicksort.o libpilha.o
	gcc -o ler ler.o quicksort.o libpilha.o $(CFLAGS)

imprimir: imprimir.o
	gcc -o imprimir imprimir.o $(CFLAGS)

escrever.o: escrever.c
	gcc -c escrever.c $(CFLAGS)

ler.o: ler.c
	gcc -c ler.c $(CFLAGS)

imprimir.o: imprimir.c
	gcc -c imprimir.c $(CFLAGS)

quicksort.o: quicksort.c
	gcc -c quicksort.c $(CFLAGS)

libpilha.o: libpilha.c
	gcc -c libpilha.c $(CFLAGS)

clean:
	rm *.o

purge:
	rm *.o escrever ler imprimir *.dat
