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

/* Cria uma lista vazia e a retorna; se falhar retorna NULL.                  */
L_int *cria_l_int();

/* Remove todos os elementos da lista, libera espaço e retorna NULL.          */
L_int *destroi_l_int(L_int *lista);

/* Retorna 1 se a lista está vazia e 0 caso contrário.                        */
int l_int_vazia(L_int *lista);

/* Retorna o número de elementos da lista.                                    */
size_t tamanho_l_int(L_int *lista);

/* Insere o elemento elem no início da lista.
 * Retorna 1 se a operação foi bem-sucedida e 0 caso contrário.               */
int insere_l_int_ini(L_int *lista, int elem);

/* Insere o elemento elem em ordem crescente na lista.
 * Retorna 1 se a operação foi bem-sucedida e 0 caso contrário.               */
int insere_l_int_ord(L_int *lista, int elem);

/* Retorna um ponteiro para um elemento aleatório da lista. Se a lista
 * estiver vazia, retorna NULL.                                               */
int *rand_l_int(L_int *lista);

/* Retorna um ponteiro para o elemento da posição pos (0-indexed) da
 * lista. Se pos >= tamanho_l_int(lista), retorna NULL.                       */
int *elem_l_int(L_int *lista, size_t pos);

/* Retorna 1 se o elemento elem está na lista e 0 caso contrário.             */
int pertence_l_int(L_int *lista, int elem);

/* Imprime os elementos da lista, para stdout, na ordem armazenada.           */
void imprime_l_int(L_int *lista);

/* Imprime os elementos da lista, no arquivo especificado por stream,
 * na ordem armazenada.                                                       */
void f_imprime_l_int(FILE *stream, L_int *lista);


/* Cria uma lista vazia e a retorna; se falhar retorna NULL.                  */
L_lista *cria_l_lista();

/* Remove recursivamente todos os elementos da lista, libera espaço e
 * retorna NULL.                                                              */
L_lista *destroi_l_lista(L_lista *lista);

/* Retorna 1 se a lista está vazia e 0 caso contrário.                        */
int l_lista_vazia(L_lista *lista);

/* Retorna o número de elementos da lista.                                    */
size_t tamanho_l_lista(L_lista *lista);

/* Insere o elemento elem no início da lista. Uma cópia do elemento elem
 * será feita, mas com os elementos na ordem inversa. Retorna 1 se a operação
 * foi bem-sucedida e 0 caso contrário. Esta função não checa se já existe
 * uma lista com a mesma chave.                                               */
int insere_l_lista_ini(L_lista *lista, char chave, L_int *elem);

/* Insere em ordem alfanumérica da chave. Uma cópia do elemento elem será
 * feita. Não checa se já existe uma lista com a mesma chave.                 */
int insere_l_lista_ord(L_lista *lista, char chave, L_int *elem);

/* Retorna um ponteiro para o elemento da posição pos (0-indexed) da
 * lista. Se pos >= tamanho_l_lista(lista), retorna NULL.                     */
L_int *elem_l_lista(L_lista *lista, size_t pos);

/* Retorna a posição (0-indexed) da lista que contém uma lista com a chave
 * chave. Se não houver, retorna -1.                                          */
int busca_l_lista(L_lista *lista, char chave);

/* Retorna a chave do nodo da posição pos (0-indexed) da lista. Se
 * pos >= tamanho_l_int(lista), retorna '\0'.                                 */
char chave_l_lista(L_lista *lista, size_t pos);

/* Retorna um ponteiro para a lista de inteiros correspondente à chave
 * chave da lista de listas. Se a chave não existir, retorna NULL.            */
L_int *elem_chave_l_lista(L_lista *lista, char chave);

/* Retorna a chave associada à lista de inteiros que contém o elemento elem.
 * Se não houver, retorna '\0'.                                               */
char chave_elem_l_lista(L_lista *lista, int elem);

/* Imprime recursivamente os elementos de todas as listas armazenadas.        */
void imprime_l_lista(L_lista *lista);

/* Imprime recursivamente os elementos de todas as listas armazenadas,
 * no arquivo especificado por stream.                                        */
void f_imprime_l_lista(FILE *stream, L_lista *lista);

#endif /* LISTA_H_ */
