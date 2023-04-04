#include <stdlib.h>
#include <stdio.h>
#include "quicksort.h"
#include "libpilha.h"

#define MAXPILHA 15000000

void troca(long *a, long *b) {
    long temp = *a;
    *a = *b;
    *b = temp;
}

long particiona(long vetor[], long a, long b, long pivo) {
    long m = a - 1;
    
    long i;
    for (i = a; i <= b; i++)
        if (vetor[i] <= pivo) {
            m++;
            troca(&vetor[m], &vetor[i]);
        }

    return m;
}

void quicksort(long vetor[], long tam) {
    long a = 0, b = tam - 1, m;

    t_pilha *p;
    p = cria_pilha(MAXPILHA);

    empilha(a, p);
    empilha(b, p);

    while (!pilha_vazia(p)) {
        desempilha(&b, p);
        desempilha(&a, p);

        if (a < b) {
            m = particiona(vetor, a, b, vetor[b]);
            empilha(a, p);
            empilha(m-1, p);
            empilha(m+1, p);
            empilha(b, p);
        }
    }

    p = destroi_pilha(p);
}
