#ifndef LISTA_H_
#define LISTA_H_

typedef struct no_int {
    struct no_int *prox;
    int elem;
} No_int;

typedef struct lista_int {
    No_int *ini;
    size_t tamanho;
} L_int;

typedef struct no_lista {
    struct no_lista *prox;
    char chave;
    L_int *elem;
} No_lista;

typedef struct lista_lista {    
    No_lista *ini;
    size_t tamanho;
} L_lista;

/* Cria uma lista vazia e a retorna; se falhar retorna NULL.              */
L_int *cria_l_int();

/* Remove todos os elementos da lista, libera espaço e retorna NULL.      */
L_int *destroi_l_int(L_int *lista);

/* Retorna 1 se a lista está vazia e 0 caso contrário.                    */
int l_int_vazia(L_int *lista);

/* Retorna o número de elementos da lista.                                */
size_t tamanho_l_int(L_int *lista);

/* Insere o elemento elem no início da lista.
 * Retorna 1 se a operação foi bem-sucedida e 0 caso contrário.           */
int insere_l_int_ini(L_int *lista, int elem);

/* Insere o elemento elem em ordem crescente na lista.
 * Retorna 1 se a operação foi bem-sucedida e 0 caso contrário.           */
int insere_l_int_ord(L_int *lista, int elem);

/* Retorna um ponteiro que aponta para o elemento da posição pos
 * (0-indexed) da lista. Se pos >= tamanho_l_int(lista), retorna NULL.    */
int *elem_l_int(L_int *lista, size_t pos);

/* Imprime os elementos da lista, para stdout, na ordem armazenada.       */
void imprime_l_int(L_int *lista);

/* Imprime os elementos da lista, no arquivo especificado por stream,
 * na ordem armazenada.                                                   */
void f_imprime_l_int(FILE *stream, L_int *lista);


/* Mesmas funções acima, mas para listas de listas de inteiros.           */

L_lista *cria_l_lista();

L_lista *destroi_l_lista(L_lista *lista);

int l_lista_vazia(L_lista *lista);

size_t tamanho_l_lista(L_lista *lista);

/* Essa função não checa se já existe uma lista com a mesma chave.        */
int insere_l_lista_ini(L_lista *lista, char chave, L_int *elem);

/* Insere em ordem alfanumérica da chave. Não checa se já existe uma
 * lista com a mesma chave.                                               */
int insere_l_lista_ord(L_lista *lista, char chave, L_int *elem);

L_int *elem_l_lista(L_lista *lista, size_t pos);

/* Retorna um ponteiro que aponta para a chave da lista da posição pos
 * (0-indexed) da lista. Se pos >= tamanho_l_int(lista), retorna NULL.    */
char *chave_l_lista(L_lista *lista, size_t pos);

/* Imprimem recursivamente os elementos de todas as listas armazenadas.   */
void imprime_l_lista(L_lista *lista);

void f_imprime_l_lista(FILE *stream, L_lista *lista);

#endif /* LISTA_H_ */
