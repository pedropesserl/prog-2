#include <stdio.h>
#include <stdlib.h>
#include "chaves.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Uso: ./t_chaves <livro_cifra> <output>\n");
        exit(1);
    }

    char *livro_cifra = argv[1];
    char *output = argv[2];

    L_lista *chaves = cria_l_lista();

    if (cria_chaves(livro_cifra, chaves) != 0) {
        fprintf(stderr, "AAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
        exit(1);
    }

    if (exporta_chaves(output, chaves) != 0) {
        fprintf(stderr, "AAAAAAAAAAAAAAAAAAAAAAAAAAB\n");
        exit(1);
    }

    chaves = destroi_l_lista(chaves);

    return 0;
}
