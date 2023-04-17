CFLAGS = -Wall -g -std=c99

all: beale t_chaves t_codificacao t_decodificacao

beale: beale.o chaves.o codificacao.o decodificacao.o lista.o
	gcc -o beale beale.o chaves.o codificacao.o decodificacao.o lista.o

beale.o: beale.c chaves.h codificacao.h decodificacao.h 
	gcc -c beale.c $(CFLAGS)

chaves.o: chaves.c chaves.h
	gcc -c chaves.c $(CFLAGS)

codificacao.o: codificacao.c codificacao.h
	gcc -c codificacao.c $(CFLAGS)

decodificacao.o: decodificacao.c decodificacao.h
	gcc -c decodificacao.c $(CFLAGS)

lista.o: lista.c lista.h
	gcc -c lista.c $(CFLAGS)

clean:
	rm *.o

purge:
	rm *.o beale t_chaves t_codificacao t_decodificacao
