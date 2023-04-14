CFLAGS = -Wall -g -std=c99

all: beale t_chaves t_codificacao t_decodificacao

beale: beale.o chaves.o codificacao.o decodificacao.o lista.o
	gcc -o beale beale.o chaves.o codificacao.o decodificacao.o lista.o

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

t_chaves: t_chaves.o chaves.o lista.o
	gcc -o t_chaves t_chaves.o chaves.o lista.o

t_codificacao: t_codificacao.o codificacao.o chaves.o lista.o
	gcc -o t_codificacao t_codificacao.o codificacao.o chaves.o lista.o

t_decodificacao: t_decodificacao.o decodificacao.o
	gcc -o t_decodificacao t_decodificacao.o decodificacao.o

clean:
	rm *.o

purge:
	rm *.o beale t_chaves t_codificacao t_decodificacao t_lista
