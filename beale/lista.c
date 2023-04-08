#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Lista *cria_lista() {
    Lista *lista = (Lista*)calloc(1, sizeof(Lista));
    if (!lista)
        return NULL;
    
    lista->ini = NULL;

    return lista;
}

Lista *destroi_lista(Lista *lista) {
    No *no_aux = lista->ini;

    while (!lista_vazia(lista)) {
        lista->ini = lista->ini->prox;
        free(no_aux);
        no_aux = lista->ini;
    }

    free(lista);

    return NULL;
}

int lista_vazia(Lista *lista) {
    return lista->ini == NULL;
}

size_t tamanho_lista(Lista *lista) {
    return lista->tamanho;
}

int insere_lista_ini(Lista *lista, int elem) {
    No *no = (No*)calloc(1, sizeof(No));
    if (!no)
        return 0;

    no->dado = elem;
    no->prox = lista->ini;
    lista->ini = no;

    (lista->tamanho)++;

    return 1;
}

int elem_lista(Lista *lista, size_t n, int *elem) {
    if (n >= tamanho_lista(lista))
        return 0;
    
    No *no = lista->ini;
    for (size_t i = 0; i < n; i++)
        no = no->prox;

    *elem = no->dado;

    return 1;
}

void imprime_lista(Lista *lista) {
    if (lista_vazia(lista))
        return;

    No *no = lista->ini;
    for (size_t i = 0; i < tamanho_lista(lista) - 1; i++) {
        printf("%d ", no->dado);
        no = no->prox;
    }
    printf("%d\n", no->dado);
}

void f_imprime_lista(FILE *stream, Lista *lista) {
    if (lista_vazia(lista))
        return;

    No *no = lista->ini;
    for (size_t i = 0; i < tamanho_lista(lista) - 1; i++) {
        fprintf(stream, "%d ", no->dado);
        no = no->prox;
    }
    fprintf(stream, "%d\n", no->dado);
}
