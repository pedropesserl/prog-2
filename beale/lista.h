#ifndef LISTA_H_
#define LISTA_H_

typedef struct no {
    struct no *prox;
    int dado;
} No;

typedef struct lista {
    No *ini;
    size_t tamanho;
} Lista;

/* Cria uma lista vazia e a retorna; se falhar retorna NULL.              */
Lista *cria_lista();

/* Remove todos os elementos da lista, libera espaço e retorna NULL.      */
Lista *destroi_lista(Lista *lista);

/* Retorna 1 se a lista está vazia e 0 caso contrário.                    */
int lista_vazia(Lista *lista);

/* Retorna o número de elementos da lista.                                */
size_t tamanho_lista(Lista *lista);

/* As funções para inserir na fila respeitam ordens diferentes.          
 * Não é aconselhável usar mais de uma dessas funções no mesmo programa.  */

/* Insere o elemento elem no início da lista, independente da ordem.
 * Retorna 1 se a operação foi bem-sucedida e 0 caso contrário.           */
int insere_lista_ini(Lista *lista, int elem);

/* Atribui ao inteiro apontado por elem o elemento da posição pos da
 * lista (0-indexed). Se pos >= tamanho_lista(lista), retorna 0.             
 * Se a operação for bem-sucedida, retorna 1.                             */
int elem_lista(Lista *lista, size_t pos, int *elem);

/* Imprime os elementos da lista, para stdout, na ordem armazenada.       */
void imprime_lista(Lista *lista);

/* Imprime os elementos da lista, no arquivo especificado por stream,
 * na ordem armazenada.                                                   */
void f_imprime_lista(FILE *stream, Lista *lista);

#endif /* LISTA_H_ */
