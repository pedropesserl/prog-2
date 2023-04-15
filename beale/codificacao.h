#ifndef CODIFICACAO_H_
#define CODIFICACAO_H_

/* Codifica a mensagem no arquivo com o nome original usando o livro_cifra
 * e salva em um arquivo com o nome de codificada. Se houver erro de alocação
 * de memória, retorna 1. Se houver erro ao abrir o arquivo em livro_cifra,
 * retorna 2. Se houver erro ao abrir o arquivo em original, retorna 3.
 * Se o arquivo codificada já existir, retorna 4.                             */
int codifica_msg(char *livro_cifra, char *original, char *codificada);

#endif /* CODIFICACAO_H_ */
