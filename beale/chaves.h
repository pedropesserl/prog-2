#ifndef CHAVES_H_
#define CHAVES_H_

#include "lista.h"

#define MAX_WRD_LEN 150

/* Insere um valor acompanhado de uma chave na lista de listas. Se a lista
 * correspondente à chave inserida já existir, insere o valor nessa lista.
 * Se não, cria uma lista de inteiros com a chave nova.
 * Se houver erro de alocação de memória, retorna 0. CC, retorna 1.          */
int insere_valor_com_chave(L_lista *chaves, char chave, int valor);

/* Retorna em chaves uma lista de listas de inteiros contendo as chaves
 * geradas a partir do arquivo livro_cifra. Se encontrar um caracter não
 * ASCII, ignora. Se houver erro de alocação de memória, retorna 1. Se
 * houver erro ao abrir o arquivo, retorna 2. CC, retorna 0.                 */
int cria_chaves(char *livro_cifra, L_lista *chaves);

/* Cria um arquivo e imprime nele as chaves armazenadas na lista de chaves.
 * Se houver erro ao abrir o arquivo, retorna 1. CC, retorna 0.              */
int exporta_chaves(char *output, L_lista *chaves);

#endif /* CHAVES_H_ */
