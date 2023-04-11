#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

L_int *cria_l_int() {
    L_int *lista = (L_int*)calloc(1, sizeof(L_int));
    if (!lista)
        return NULL;
    
    lista->ini = NULL;
    lista->tamanho = 0;

    return lista;
}

L_int *destroi_l_int(L_int *lista) {
    No_int *no_aux = lista->ini;

    while (!l_int_vazia(lista)) {
        lista->ini = lista->ini->prox;
        free(no_aux);
        no_aux = lista->ini;
    }

    free(lista);

    return NULL;
}

int l_int_vazia(L_int *lista) {
    return lista->ini == NULL;
}

size_t tamanho_l_int(L_int *lista) {
    return lista->tamanho;
}

int insere_l_int_ini(L_int *lista, int elem) {
    No_int *novo = (No_int*)calloc(1, sizeof(No_int));
    if (!novo)
        return 0;

    novo->elem = elem;
    novo->prox = lista->ini;
    lista->ini = novo;

    (lista->tamanho)++;

    return 1;
}

int insere_l_int_ord(L_int *lista, int elem) {
    No_int *novo = (No_int*)calloc(1, sizeof(No_int));
    if (!novo)
        return 0;

    novo->elem = elem;
    novo->prox = lista->ini;
    
    No_int *atual = lista->ini;
    No_int *aux = NULL;

    while (atual && atual->elem < novo->elem) {
        aux = atual;
        atual = atual->prox;
    }

    if (!aux) {
        novo->prox = lista->ini;
        lista->ini = novo;
    } else {
        novo->prox = atual;
        aux->prox = novo;
    }

    (lista->tamanho)++;

    return 1;
}

int *elem_l_int(L_int *lista, size_t pos) {
    if (pos >= tamanho_l_int(lista))
        return NULL;
    
    No_int *no = lista->ini;
    for (size_t i = 0; i < pos; i++)
        no = no->prox;

    return &no->elem;
}

void imprime_l_int(L_int *lista) {
    if (l_int_vazia(lista))
        return;

    No_int *no = lista->ini;
    for (size_t i = 0; i < tamanho_l_int(lista) - 1; i++) {
        printf("%d ", no->elem);
        no = no->prox;
    }
    printf("%d\n", no->elem);
}

void f_imprime_l_int(FILE *stream, L_int *lista) {
    if (l_int_vazia(lista))
        return;

    No_int *no = lista->ini;
    for (size_t i = 0; i < tamanho_l_int(lista) - 1; i++) {
        fprintf(stream, "%d ", no->elem);
        no = no->prox;
    }
    fprintf(stream, "%d\n", no->elem);
}

L_lista *cria_l_lista() {
    L_lista *lista = (L_lista*)calloc(1, sizeof(L_lista));
    if (!lista)
        return NULL;
    
    lista->ini = NULL;
    lista->tamanho = 0;

    return lista;
}

L_lista *destroi_l_lista(L_lista *lista) {
    No_lista *no_aux = lista->ini;

    while (!l_lista_vazia(lista)) {
        lista->ini = lista->ini->prox;
        no_aux->elem = destroi_l_int(no_aux->elem);
        free(no_aux);
        no_aux = lista->ini;
    }

    free(lista);

    return NULL;
}

int l_lista_vazia(L_lista *lista) {
    return lista->ini == NULL;
}

size_t tamanho_l_lista(L_lista *lista) {
    return lista->tamanho;
}

int insere_l_lista_ini(L_lista *lista, char chave, L_int *elem) {
    No_lista *novo = (No_lista*)calloc(1, sizeof(No_lista));
    if (!novo)
        return 0;

    novo->elem = elem;
    novo->chave = chave;
    novo->prox = lista->ini;
    lista->ini = novo;

    (lista->tamanho)++;

    return 1;
}

int insere_l_lista_ord(L_lista *lista, char chave, L_int *elem) {
    No_lista *novo = (No_lista*)calloc(1, sizeof(No_lista));
    if (!novo)
        return 0;

    novo->elem = elem;
    novo->chave = chave;

    No_lista *atual = lista->ini;
    No_lista *aux = NULL;

    while (atual && (int)atual->chave < (int)novo->chave) {
        aux = atual;
        atual = atual->prox;
    }

    if (!aux) {
        novo->prox = lista->ini;
        lista->ini = novo;
    } else {
        novo->prox = atual;
        aux->prox = novo;
    }

    (lista->tamanho)++;

    return 1;
}

L_int *elem_l_lista(L_lista *lista, size_t pos) {
    if (pos >= tamanho_l_lista(lista))
        return NULL;
    
    No_lista *no = lista->ini;
    for (size_t i = 0; i < pos; i++)
        no = no->prox;

    return no->elem;
}

void imprime_l_lista(L_lista *lista) {
    if (l_lista_vazia(lista))
        return;

    No_lista *no = lista->ini;
    for (size_t i = 0; i < tamanho_l_lista(lista); i++) {
        printf("%c: ", no->chave);
        if (l_int_vazia(no->elem))
            printf("\n");
        else
            imprime_l_int(no->elem);
        no = no->prox;
    }
}

void f_imprime_l_lista(FILE *stream, L_lista *lista) {
    if (l_lista_vazia(lista))
        return;

    No_lista *no = lista->ini;
    for (size_t i = 0; i < tamanho_l_lista(lista); i++) {
        fprintf(stream, "%c: ", no->chave);
        f_imprime_l_int(stream, no->elem);
        no = no->prox;
    }
}
