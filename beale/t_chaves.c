#include <stdio.h>
#include <stdlib.h>
#include "chaves.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso: ./t_chaves <arquivo>");
        exit(1);
    }
    L_int **chaves = (L_int**)calloc(127, sizeof(L_int*));

    char *livro_cifra = argv[1];
    char *output = "chaves_geradas.txt";

    for (size_t i = 0; i < 127; i++) {
        chaves[i] = cria_l_int();
    }

    cria_chaves(livro_cifra, chaves);

    exporta_chaves(output, chaves, 127);
    
    for (size_t i = 0; i < 127; i++) {
        chaves[i] = destroi_l_int(chaves[i]);
    }

    return 0;
}
