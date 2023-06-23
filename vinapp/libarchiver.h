#ifndef ARCHIVER_H_
#define ARCHIVER_H_

#include <stdio.h>
#include <stdlib.h>
#include "libbin.h"

#define BUFFERSIZE 1024

#define NOT_IN_ARCH_WARN(member) do {                                            \
        printf("Aviso: o membro %s não está no archive especificado. ", member); \
        printf("Ignorado.\n");                                                   \
    } while (0)

struct File_info {
    char name[MAX_FNAME_LEN], uid[MAX_UNAME_LEN], gid[MAX_GNAME_LEN];
    int perm;    // Modo e permissões do arquivo.
    time_t td;   // Momento da última modificação no arquivo.
    size_t size; // Tamanho do arquivo.
    size_t ord;  // 1-indexed. Ordem do arquivo no diretório.
    size_t pos;  // 0-indexed. Byte a partir do qual o arquivo começa no archive.
};

// Lê a área de diretório do archive e retorna as informações sobre os arquivos.
// Retorna em dirnmemb o número de structs lidas.
struct File_info *read_dir(FILE *archive, size_t *dirnmemb);

// Escreve a nova posição de um archivo dir de dirnmemb membros nos primeiros
// bytes do archive, e o seu conteúdo na posição destinada (após o último membro).
void write_dir(FILE *archive, struct File_info *dir, size_t dirnmemb);

// Escreve em buffer uma string com o nome do usuário ao qual o arquivo de nome
// path pertence.
void get_uid(char *buffer, char *path);

// Escreve em buffer uma string com o nome do grupo ao qual o arquivo de nome
// path pertence.
void get_gid(char *buffer, char *path);

// Dado um modo mode, escreve em buffer uma string no formato: drwxrwxrwx.
void format_perm(char *buffer, int mode);

// Dado um tempo time, escreve em buffer uma string no formato: YYYY-MM-DD hh:mm
void format_modtime(char *buffer, time_t time);

// Se houver um arquivo no diretório dir com o nome member_name, retorna
// sua ordem no diretório. Se não, retorna 0.
size_t get_ord(struct File_info *dir, size_t dirnmemb, char *member_name);

// Dada a ordem ord do arquivo no diretório dir, retorna o byte a partir do qual
// o arquivo dessa ordem começa no archive (0-indexed).
size_t get_pos(struct File_info *dir, size_t ord);

// Dado um nome de arquivo membname, escreve em buffer sua versão relativizada,
// se já não for.
void standardize_name(char *membname, char *buffer);

// Dado um nome de arquivo membname, escreve em buffer "std_name/", em que std_name
// é a versão relativizada de membname.
size_t make_dir_name(char *membname, char *buffer);

#endif // ARCHIVER_H_
