#include <stdio.h>
#include "chaves.h"
#include "decodificacao.h"

static int decodifica(char *original, char *decodificada, L_lista *chaves) {
    FILE *in = fopen(original, "r");
    if (!in)
        return 3;

    FILE *out = fopen(decodificada, "r");
    if (out) {
        fclose(in);
        fclose(out);
        return 4;
    }
    out = fopen(decodificada, "w");
    if (!out) {
        fclose(in);
        return 5;
    }

    char chave = '\0';
    int valor;
    while (fscanf(in, "%d", &valor) != EOF) {
        if (valor == -1)
            fputc(' ', out);
        else if (valor == -3)
            fputc('\n', out);
        else {
            chave = chave_elem_l_lista(chaves, valor);
            fputc(chave, out);
        }
    }

    fclose(in);
    fclose(out);

    return 0;
}

int decodifica_com_chaves(char *arq_chaves, char *original,
                          char *decodificada, L_lista *chaves) {
    int erro = arq_cria_chaves(arq_chaves, chaves);
    if (erro)
        return erro;

    erro = decodifica(original, decodificada, chaves);
    if (erro)
        return erro;
    
    return 0;
}

int decodifica_com_livro(char *arq_chaves, char *original,
                         char *decodificada, L_lista *chaves) {
    int erro = livro_cria_chaves(arq_chaves, chaves);
    if (erro)
        return erro;

    erro = decodifica(original, decodificada, chaves);
    if (erro)
        return erro;
    
    return 0;
}
