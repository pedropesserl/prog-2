#ifndef INSERT_H_
#define INSERT_H_

// Insere nmemb membros, dados por membv, no arquivo de nome archive_path.
// Se houver membros repetidos, os sobrescreve. Se um dos membros for um
// diretório, insere recursivamente todos os arquivos dentro dele.
void insert_overwrite(char *archive_path, int nmemb, char **membv);

// Insere nmemb membros, dados por membv, no arquivo de nome archive_path.
// Se houver membros repetidos, apenas os sobrescreve se suas datas de
// modificação forem mais recentes que as de suas contrapartes no archive.
// Se um dos membros for um diretório, insere recursivamente todos os
// arquivos dentro dele.
void insert_soft(char *archive_path, int nmemb, char **membv);

#endif // INSERT_H_
