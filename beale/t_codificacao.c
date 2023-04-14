#include <stdio.h>
#include <stdlib.h>
#include "codificacao.h"

int main(int argc, char **argv) {
    srand(0);

    if (argc != 4) {
        fprintf(stderr, "Uso: %s <livro_cifra> <msg_original> <msg_codificada>\n", argv[0]);
        exit(1);
    }

    char *livro_cifra = argv[1];
    char *msg_original = argv[2];
    char *msg_codificada = argv[3];
    
    codifica_msg(livro_cifra, msg_original, msg_codificada);
    
    return 0;
}
