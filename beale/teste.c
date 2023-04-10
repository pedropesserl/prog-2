#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main() {
    srand(0);

    L_lista *lista_de_listas = cria_l_lista();

    L_int *l_int_0 = cria_l_int();
    for (int i = 0; i < 5; i++) {
        insere_l_int_ini(l_int_0, rand() % 10);
    }

    L_int *l_int_1 = cria_l_int();
    for (int i = 0; i < 5; i++) {
        insere_l_int_ini(l_int_1, rand() % 10);
    }

    L_int *l_int_2 = cria_l_int();
    for (int i = 0; i < 5; i++) {
        insere_l_int_ini(l_int_2, rand() % 10);
    }

    L_int *l_int_3 = cria_l_int();
    for (int i = 0; i < 5; i++) {
        insere_l_int_ini(l_int_3, rand() % 10);
    }

    L_int *l_int_4 = cria_l_int();

    if (!insere_l_lista_ord(lista_de_listas, 'a', l_int_0)) {
        fprintf(stderr, "AAAAAAAAAAAAAAAAAAA\n");
        exit(1);
    }

    if (!insere_l_lista_ord(lista_de_listas, 'b', l_int_1)) {
        fprintf(stderr, "AAAAAAAAAAAAAAAAAAA\n");
        exit(1);
    }

    if (!insere_l_lista_ord(lista_de_listas, 'a', l_int_2)) {
        fprintf(stderr, "AAAAAAAAAAAAAAAAAAA\n");
        exit(1);
    }

    if (!insere_l_lista_ord(lista_de_listas, 'f', l_int_3)) {
        fprintf(stderr, "AAAAAAAAAAAAAAAAAAA\n");
        exit(1);
    }

    if (!insere_l_lista_ord(lista_de_listas, 'c', l_int_4)) {
        fprintf(stderr, "AAAAAAAAAAAAAAAAAAA\n");
        exit(1);
    }

    imprime_l_lista(lista_de_listas);

    lista_de_listas = destroi_l_lista(lista_de_listas);

    return 0;
}
