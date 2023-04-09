CFLAGS = -Wall -g -std=c99

all: beale

beale: beale.o chaves.o codificacao.o decodificacao.o
	gcc -o beale beale.o chaves.o codificacao.o decodificacao.o

beale.o: beale.c
	gcc -c beale.c $(CFLAGS)

chaves.o: chaves.c
	gcc -c chaves.c $(CFLAGS)

codificacao.o: codificacao.c
	gcc -c codificacao.c $(CFLAGS)

decodificacao.o: decodificacao.c
	gcc -c decodificacao.c $(CFLAGS)

lista.o: lista.c
	gcc -c lista.c $(CFLAGS)

t_codificacao: t_codificacao.o codificacao.o
	gcc -o t_codificacao t_codificacao.o codificacao.o

t_decodificacao: t_decodificacao.o decodificacao.o
	gcc -o t_decodificacao t_decodificacao.o decodificacao.o

clean:
	rm *.o

purge:
	rm *.o beale
