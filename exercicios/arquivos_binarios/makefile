CFLAGS=-Wall -Wextra -g -std=c90

all: escrever ler print

escrever: escrever.o
	gcc -o escrever escrever.o $(CFLAGS)

ler: ler.o
	gcc -o ler ler.o $(CFLAGS)

print: print.o
	gcc -o print print.o $(CFLAGS)

escrever.o: escrever.c
	gcc -c escrever.c $(CFLAGS)

ler.o: ler.c
	gcc -c ler.c $(CFLAGS)

print.o: print.c
	gcc -c print.c $(CFLAGS)

clean:
	rm *.o

purge:
	rm *.o escrever ler print
