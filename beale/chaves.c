#include <stdio.h>
#include <stdlib.h>
#include "chaves.h"

/* Insere um valor acompanhado de uma chave na lista de listas. Se a lista
 * correspondente à chave inserida já existir, insere o valor nessa lista.
 * Se não, cria uma lista de inteiros com a chave nova.
 * Se houver erro de alocação de memória, retorna 1. CC, retorna 0.           */
static int insere_valor_com_chave(L_lista *chaves, char chave, int valor) {
    L_int *lista_de_valores = NULL;
    
    int i;
    if ((i = busca_l_lista(chaves, chave)) != -1) {
        lista_de_valores = elem_l_lista(chaves, i);
        if (!insere_l_int_ini(lista_de_valores, valor))
            return 1;
    } else {
        lista_de_valores = cria_l_int();
        if (!lista_de_valores)
            return 1;
        if (!insere_l_int_ini(lista_de_valores, valor))
            return 1;
        if (!insere_l_lista_ord(chaves, chave, lista_de_valores))
            return 1;
        lista_de_valores = destroi_l_int(lista_de_valores);
    }

    return 0;
}

int arq_cria_chaves(char *arq_chaves, L_lista *chaves) {
    FILE *arq = fopen(arq_chaves, "r");
    if (!arq)
        return 2;

    char *buffer = (char*)calloc(MAX_WRD_LEN, sizeof(char));
    if (!buffer) {
        fclose(arq);
        return 1;
    }

    L_int *lista_de_valores = NULL;

    char c = '\0';

    fscanf(arq, "%s", buffer);
    while (!feof(arq)) {
        c = buffer[0];

        lista_de_valores = cria_l_int();
        if (!lista_de_valores) {
            fclose(arq);
            return 1;
        }

        int valor;
        while (fscanf(arq, "%s", buffer) != EOF && buffer[1] != ':') {
            sscanf(buffer, "%d", &valor);
            if (!insere_l_int_ini(lista_de_valores, valor)) {
                fclose(arq);
                return 1;
            }
        }
        
        if (!insere_l_lista_ord(chaves, c, lista_de_valores)) {
            fclose(arq);
            return 1;
        }
        lista_de_valores = destroi_l_int(lista_de_valores);
    }

    free(buffer);
    fclose(arq);

    return 0;
}

int livro_cria_chaves(char *livro_cifra, L_lista *chaves) {
    FILE *arq = fopen(livro_cifra, "r");
    if (!arq)
        return 2;

    char c;
    int i = 0;
    char *buffer = (char*)calloc(MAX_WRD_LEN, sizeof(char));
    while (fscanf(arq, "%s", buffer) != EOF) {
        c = buffer[0];
        if (33 <= c && c <= 126) {
            if ('A' <= c && c <= 'Z')
                c += 32;
            if (insere_valor_com_chave(chaves, c, i++) != 0) {
                fclose(arq);
                return 1;
            }
        }
    }

    free(buffer);
    fclose(arq);
    
    return 0;
}

int exporta_chaves(char *output, L_lista *chaves) {
    FILE *arq = fopen(output, "r");
    if (arq) {
        fclose(arq);
        return 4;
    }
    arq = fopen(output, "w");
    if (!arq)
        return 2;
    
    f_imprime_l_lista(arq, chaves);

    fclose(arq);

    return 0;
}
