#ifndef BIN_FILES_H_
#define BIN_FILES_H_

#include <stdio.h>
#include <stdlib.h>

#define uchar unsigned char
#define MAX_FNAME_LEN 256 // Número máximo de caracteres no nome de um
                          // arquivo e seu caminho
// Mesmo para nome de usuário e nome de grupo
#define MAX_UNAME_LEN 9
#define MAX_GNAME_LEN 9

#ifndef BUFFERSIZE
#define BUFFERSIZE 1024
#endif

#define MEM_ERR(err) do {                                                           \
        fprintf(stderr, "[libbin] Erro na alocação de memória.\n");                 \
        exit(err);                                                                  \
    } while (0)                                                                     \

#define FOPEN_ERR(err, filename) do {                                               \
        fprintf(stderr, "[libbin] Erro ao abrir/escrever arquivo %s.\n", filename); \
        exit(err);                                                                  \
    } while (0)

#define FDNE_ERR(err, filename) do {                                                \
        fprintf(stderr, "[libbin] Erro: arquivo %s não existe.\n", filename);       \
        exit(err);                                                                  \
    } while (0)

#define FEXISTS_ERR(err, filename) do {                                             \
        fprintf(stderr, "[libbin] Erro: o arquivo %s já existe. ", filename);       \
        fprintf(stderr, "Não é possível sobrescrevê-lo.\n");                        \
        exit(err);                                                                  \
    } while (0);

// Retorna o tamanho do arquivo f em bytes.
size_t get_size(FILE *f);

// Abre um espaço de space bytes no arquivo f, a partir da posição pos.
// Preenche o espaço com bytes nulos ou cópias dos bytes já existentes.
void open_space(FILE *f, size_t space, size_t pos);

// Remove um bloco de (no máximo) space bytes no arquivo f, a partir da posição
// pos. Trunca o tamanho do arquivo e o rebobina.
void remove_space(FILE *f, size_t space, size_t pos);

#endif // BIN_FILES_H_
