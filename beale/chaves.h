#ifndef CHAVES_H_
#define CHAVES_H_

#include "lista.h"

#define MAX_WRD_LEN 128

/* Retorna em chaves uma lista de listas de inteiros contendo as chaves
 * geradas a partir do arquivo arq_chaves. O formato esperado para cada
 * linha é:
 * chave: elemento elemento elemento (...)
 * em que chave é um char e elemento é um int. Se houver erro de alocação de
 * memória, retorna 1. Se houver erro ao abrir o arquivo, retorna 2.
 * CC, retorna 0.                                                             */
int arq_cria_chaves(char *arq_chaves, L_lista *chaves);

/* Retorna em chaves uma lista de listas de inteiros contendo as chaves
 * geradas a partir do arquivo livro_cifra. Se encontrar um caracter não
 * ASCII, ignora. Se houver erro de alocação de memória, retorna 1. Se
 * houver erro ao abrir o arquivo, retorna 2. CC, retorna 0.                  */
int livro_cria_chaves(char *livro_cifra, L_lista *chaves);

/* Cria um arquivo e imprime nele as chaves armazenadas na lista de chaves.
 * Se houver erro ao abrir o arquivo, retorna 2. Se um arquivo com o mesmo
 * nome já existir, retorna 4. CC, retorna 0.                                 */
int exporta_chaves(char *output, L_lista *chaves);

#endif /* CHAVES_H_ */
