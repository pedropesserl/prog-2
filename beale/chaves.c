#include <stdio.h>
#include <stdlib.h>
#include "chaves.h"

int insere_valor_com_chave(L_lista *chaves, char chave, int valor) {
    int chave_ja_existe = 0;
    char c_aux;
    L_int *lista_de_valores = NULL;
    size_t i = 0;
    for (; i < tamanho_l_lista(chaves); i++) {
        c_aux = chave_l_lista(chaves, i);
        if (c_aux == chave) {
            chave_ja_existe = 1;
            break;
        }
    }

    if (chave_ja_existe)
        lista_de_valores = elem_l_lista(chaves, i);
    else {
        lista_de_valores = (L_int*)calloc(1, sizeof(L_int));
        if (!insere_l_lista_ord(chaves, chave, lista_de_valores))
            return 0;
    }
    if (!insere_l_int_ini(lista_de_valores, valor))
        return 0;

    return 1;
}

int cria_chaves(char *livro_cifra, L_lista *chaves) {
    FILE *arq = fopen(livro_cifra, "r");
    if (!arq)
        return 1;

    char c;
    int i = 0;
    char *palavra = (char*)calloc(MAX_WRD_LEN, sizeof(char));
    while (fscanf(arq, "%s", palavra) != EOF) {
        c = palavra[0];
        if (21 <= c && c <= 126) {
            if ('A' <= c && c <= 'Z')
                c += 32;
            if (!insere_valor_com_chave(chaves, c, i++))
                return 2;
        }
    }

    fclose(arq);
    
    return 0;
}

int exporta_chaves(char *output, L_lista *chaves) {
    FILE *arq = fopen(output, "r");
    if (arq) {
        fprintf(stderr, "Erro: arquivo %s já existe.\n", output);
        exit(1);
    }

    arq = fopen(output, "w");
    if (!arq)
        return 1;
    
    f_imprime_l_lista(arq, chaves);

    return 0;
}
