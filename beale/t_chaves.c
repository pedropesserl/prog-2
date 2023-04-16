#include <stdio.h>
#include <stdlib.h>
#include "chaves.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arq_chaves> <output>\n", argv[0]);
        exit(1);
    }

    char *arq_chaves = argv[1];
    char *output = argv[2];

    L_lista *chaves = cria_l_lista();

    if (arq_cria_chaves(arq_chaves, chaves) != 0) {
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
