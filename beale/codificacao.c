#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "chaves.h"
#include "codificacao.h"

int codifica_msg(char *livro_cifra, char *original, char *codificada) {
    L_lista *chaves = cria_l_lista();
    if (!chaves)
        return 0;
    int e = cria_chaves(livro_cifra, chaves);
    if (e != 0)
        return e;

    FILE *in = fopen(original, "r");
    if (!in)
        return 2;

    FILE *out = fopen(codificada, "r");
    if (out)
        return 3;
    out = fopen(codificada, "w");
    if (!out)
        return 2;

    L_int *atual;
    int *r;
    char c = fgetc(in);
    while (c != EOF) {
        if (32 <= c && c <= 126) {
            if (c == ' ')
                fprintf(out, "-1 ");
            else {
                if ('A' <= c && c <= 'Z')
                    c += 32;
                
                atual = elem_chave_l_lista(chaves, c);
                if (!atual) {
                    c = fgetc(in);
                    continue;
                }
                r = rand_l_int(atual);
                fprintf(out, "%d ", *r);
            }
        }
        c = fgetc(in);
    }
    fprintf(out, "\n");

    fclose(in);
    fclose(out);

    chaves = destroi_l_lista(chaves);

    return 0;
}
