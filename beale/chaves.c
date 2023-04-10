#include <stdio.h>
#include <stdlib.h>
#include "chaves.h"

#if 0
int cria_chaves(char *livro_cifra, L_int **chaves) {
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
            if (!insere_l_int_ini(chaves[(int)c], i++))
                return 2;
        }
    }

    fclose(arq);

    return 0;
}

int exporta_chaves(char *output, L_int **chaves, size_t nchaves) {
    FILE *arq = fopen(output, "r");
    if (arq) {
        fprintf(stderr, "Erro: arquivo %s já existe.\n", output);
        exit(1);
    }

    arq = fopen(output, "w");
    if (!arq)
        return 1;

    for (size_t i = 0; i < nchaves; i++)
        if (!l_int_vazia(chaves[i])) {
            fprintf(arq, "%c: ", (char)i);
            f_imprime_l_int(arq, chaves[i]);
        }

    fclose(arq);

    return 0;
}

#else

int insere_valor_com_chave(L_lista *chaves, char chave, int valor) {


}

int cria_chaves(char *livro_cifra, L_lista *chaves) {
    FILE *arq = fopen(livro_cifra, "r");
    if (!arq)
        return 1;

    

}

#endif
