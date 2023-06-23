#ifndef EXTRACT_H_
#define EXTRACT_H_

// Extrai nmemb membros, dados por membv, do arquivo de nome archive_path.
// Se nmemb for 0, extrai todos os arquivos.
void extract_from_archive(char *archive_path, int nmemb, char **membv);

#endif // EXTRACT_H_
