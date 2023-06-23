#ifndef REMOVE_H_
#define REMOVE_H_

// Remove nmemb membros, dados por membv, do arquivo de nome archive_path.
// Se for passado um diretório, remove todos os seus filhos.
void remove_from_archive(char *archive_path, int nmemb, char **membv);

#endif // REMOVE_H_
