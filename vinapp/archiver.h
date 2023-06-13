#ifndef ARCHIVER_H_
#define ARCHIVER_H_

struct File_info {
    char *name, *uid, *gid, *perms;
    char *td; // td: time + date. formato: YYYY-MM-DD hh:mm
    size_t size, ord, pos;
};

// lê a área de diretório do archive e retorna as informações sobre os arquivos.
struct Dir *le_dir(FILE *archive);

#endif // ARCHIVER_H_
