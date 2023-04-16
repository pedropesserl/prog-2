#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decodificacao.h"

int main(int argc, char **argv) {
    int decodificar_com_chaves = 0;

    if (argc != 5) {
        fprintf(stderr, "Uso: %s -[a|b] <arq_chaves>/<livro_cifra> <msg_original> <msg_decodificada>\n", argv[0]);
        exit(1);
    }
    char *arq_chaves = NULL;
    char *livro_cifra = NULL;
    if (strcmp(argv[1], "-a") == 0) {
        arq_chaves = argv[2];
        decodificar_com_chaves = 1;
    } else if (strcmp(argv[1], "-b") == 0)
        livro_cifra = argv[2];
    else {
        fprintf(stderr, "Uso: %s -[a|b] <arq_chaves>/<livro_cifra> <msg_original> <msg_decodificada>\n", argv[0]);
        exit(1);
    }
    char *original = argv[3];
    char *decodificada = argv[4];
    
    L_lista *lista_de_chaves = cria_l_lista();
   
    int e;

    if (decodificar_com_chaves) {
        e = decodifica_com_chaves(arq_chaves, original, decodificada, lista_de_chaves);
        if (e != 0) {
            fprintf(stderr, "erro na função decodifica_com_chaves() (código: %d)\n", e);
            exit(e);
        }
    } else {
        e = decodifica_com_livro(livro_cifra, original, decodificada, lista_de_chaves);
        if (e != 0) {
            fprintf(stderr, "erro na função decodifica_com_livro() (código: %d)\n", e);
            exit(e);
        }
    }

    return 0;
}
