#ifndef DECODIFICACAO_H_
#define DECODIFICACAO_H_

#include "lista.h"

/* Decodifica a mensagem original a partir de um arquivo de chaves arq_chaves,
 * e escreve no arquivo decodificada. Se houver erro de alocação de memória,
 * retorna 1. Se houver erro ao abrir o arquivo arq_chaves, retorna 2. Se
 * houver erro ao abrir o arquivo original, retorna 3. Se o arquivo
 * decodificada já existir, retorna 4. CC, retorna 0.                         */
int decodifica_com_chaves(char *arq_chaves, char *original,
                          char *decodificada, L_lista *chaves);

/* Decodifica a mensagem original a partir de um livro de cifras livro_cifra,
 * e escreve no arquivo decodificada. Se houver erro de alocação de memória,
 * retorna 1. Se houver erro ao abrir o arquivo livro_cifra, retorna 2. Se
 * houver erro ao abrir o arquivo original, retorna 3. Se o arquivo
 * decodificada já existir, retorna 4. CC, retorna 0.                         */
int decodifica_com_livro(char *livro_cifra, char *original,
                         char *decodificada, L_lista *chaves);

#endif /* DECODIFICACAO_H_ */
