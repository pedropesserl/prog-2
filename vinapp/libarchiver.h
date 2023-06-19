#ifndef ARCHIVER_H_
#define ARCHIVER_H_

/* #include <stdio.h> */
/* #include <stdlib.h> */

struct File_info {
    char *name, *uid, *gid, *perms;
    char *td; // Data da última modificação no arquivo. Formato: YYYY-MM-DD hh:mm
    size_t size;
    size_t ord; // 1-indexed. Ordem do arquivo no diretório.
    size_t pos; // 0-indexed. Byte a partir do qual o arquivo começa no archive.
};

// Lê a área de diretório do archive e retorna as informações sobre os arquivos.
// Retorna em dirnmemb o número de structs lidas.
struct File_info *read_dir(FILE *archive, size_t *dirnmemb);

// Retorna uma string com o nome do usuário ao qual o arquivo de nome path pertence.
char *get_uid(char *path);

// Retorna uma string com o nome do grupo ao qual o arquivo de nome path pertence.
char *get_git(char *path);

// Retorna uma string com o modo do arquivo de nome path e suas permissões,
// similar à primeira coluna da saída do comando tar tvf.
char *get_perm(char *path);

// Retorna uma string com o tempo e data de modificação do arquivo de nome path,
// formatada como descrito acima.
char *get_modtime(char *path);

// Se houver um arquivo no diretório dir com o nome member_name, retorna
// sua ordem no diretório. Se não, retorna 0.
size_t get_ord(struct File_info *dir, size_t dirnmemb, char *member_name);

// Dada a ordem ord do arquivo no diretório dir, retorna o byte a partir do qual
// o arquivo dessa posição começa no archive (0-indexed).
size_t get_pos_from_ord(struct File_info *dir, size_t ord);

#endif // ARCHIVER_H_
