#ifndef LIBBIN_H_
#define LIBBIN_H_

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

#define MEM_ERR(err, where) do {                                                    \
        fprintf(stderr, "Erro na alocação de memória.\n");                          \
        fprintf(stderr, "Em: %s.\n", where);                                        \
        exit(err);                                                                  \
    } while (0)

#define OPEN_ERR(err, filename) do {                                                \
        fprintf(stderr, "Erro ao abrir/escrever arquivo/diretório %s.\n", filename);\
        exit(err);                                                                  \
    } while (0)

#define DNE_ERR(err, filename) do {                                                 \
        fprintf(stderr, "Erro: arquivo %s não existe.\n", filename);                \
        exit(err);                                                                  \
    } while (0)

#define DNE_WARN(filename)                                                          \
        printf("Aviso: arquivo %s não existe. Ignorado.\n", filename);

#define EXISTS_WARN(filename) do {                                                  \
        fprintf(stderr, "Erro: arquivo ou diretório %s já existe, e ", filename);   \
        fprintf(stderr, "não é possível sobrescrevê-lo. Ignorado.\n");              \
    } while (0)

// Retorna o tamanho do arquivo f em bytes.
size_t get_size(FILE *f);

// Retorna o user id do arquivo de nome path.
int get_uid(char *path);

// Retorna o group id do arquivo de nome path.
int get_gid(char *path);

// Retorna o modo e permissões do arquivo de nome path, em um
// int (campo st_mode da struct stat).
int get_perm(char *path);

// Retorna o tempo da última modificação do arquivo de nome path, em um tipo time_t.
time_t get_modtime(char *path);

// Abre um espaço de space bytes no arquivo f, a partir da posição pos.
// Preenche o espaço com bytes nulos ou cópias dos bytes já existentes.
void open_space(FILE *f, size_t space, size_t pos);

// Remove um bloco de (no máximo) space bytes no arquivo f, a partir da posição
// pos. Trunca o tamanho do arquivo e o rebobina.
void remove_space(FILE *f, size_t space, size_t pos);

// Checa se o arquivo de nome path é um diretório. Se for, retorna o número de
// arquivos-filhos e preenche o vetor de strings apontado por childv com os seus
// nomes. Supõe que esse vetor pode conter strings de tamanho máximo MAX_FNAME_LEN.
size_t peek_dir(char *path, char ***childv);

#endif // LIBBIN_H_
