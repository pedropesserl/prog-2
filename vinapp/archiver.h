#ifndef ARCHIVER_H_
#define ARCHIVER_H_

struct File_info {
    char *name, *uid, *gid, *perms;
    char *td; // td: time + date. Formato: YYYY-MM-DD hh:mm
    size_t size;
    size_t ord; // 1-indexed. Ordem do arquivo no diretório.
    size_t pos; // 0-indexed. Byte a partir do qual o arquivo começa no archive.
};

// Lê a área de diretório do archive e retorna as informações sobre os arquivos.
// Retorna em dirnmemb o número de structs lidas.
struct File_info *le_dir(FILE *archive, size_t *dirnmemb);

// Retorna uma string com o tempo e data atuais formatados como descrito acima.
char *get_td_f();

// Retorna uma string com o modo do arquivo f e suas permissões, similar à primeira
// coluna da saída do comando tar tvf.
char *get_perms(FILE *f);

// Retorna uma string com o nome do usuário ao qual o arquivo f pertence.
char *get_uid(FILE *f);

// Retorna uma string com o nome do grupo ao qual o arquivo f pertence.
char *get_git(FILE *f);

// Se houver um arquivo no diretório dir com o nome member_name, retorna
// sua ordem no diretório. Se não, retorna 0.
size_t get_ord(struct File_info *dir, size_t dirnmemb, char *member_name);

// Dada a ordem ord do arquivo no diretório dir, retorna o byte a partir do qual
// o arquivo dessa posição começa no archive.
size_t get_curr_pos(struct File_info *dir, size_t ord);

#endif // ARCHIVER_H_
