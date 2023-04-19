#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chaves.h"
#include "codificacao.h"

int codifica_msg(char *livro_cifra, char *original, char *codificada, L_lista *chaves) {
    srand(time(0));

    int e = livro_cria_chaves(livro_cifra, chaves);
    if (e != 0)
        return e;

    FILE *in = fopen(original, "r");
    if (!in)
        return 3;

    FILE *out = fopen(codificada, "r");
    if (out) {
        fclose(out);
        return 4;
    }
    out = fopen(codificada, "w");
    if (!out)
        return 5;

    L_int *atual;
    int *r;
    char c = fgetc(in);
    while (c != EOF) {
        if (c == '\n')
            fprintf(out, "-3 ");
        else if (c == ' ')
            fprintf(out, "-1 ");
        else if (33 <= c && c <= 126) {
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
        c = fgetc(in);
    }
    fputc('\n', out);

    fclose(in);
    fclose(out);

    return 0;
}
