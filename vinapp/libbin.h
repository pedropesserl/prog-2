#ifndef BIN_FILES_H_
#define BIN_FILES_H_

#include <stdio.h>
#include <stdlib.h>

#define uchar unsigned char

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

// Abre um arquivo para leitura e escrita. O arquivo deve existir.
// Em casos de erro, termina o programa.
FILE *ME_read_and_write(const char *path);

#endif // BIN_FILES_H_
