#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "codificacao.h"

int main(int argc, char **argv) {
    srand(time(0));

    if (argc != 4) {
        fprintf(stderr, "Uso: %s <livro_cifra> <msg_original> <msg_codificada>\n", argv[0]);
        exit(1);
    }

    char *livro_cifra = argv[1];
    char *msg_original = argv[2];
    char *msg_codificada = argv[3];
    
    L_lista *lista_de_chaves = cria_l_lista();

    int e = codifica_msg(livro_cifra, msg_original, msg_codificada, lista_de_chaves);
    if (e != 0) {
        fprintf(stderr, "erro na função codifica_msg() (código: %d)\n", e);
        exit(e);
    }
    
    lista_de_chaves = destroi_l_lista(lista_de_chaves);

    return 0;
}
