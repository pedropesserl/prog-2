#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include "libbin.h"

size_t get_size(FILE *f) {
    struct stat info;
    fstat(fileno(f), &info);
    if ((info.st_mode & S_IFMT) == S_IFDIR) // se for um diretório, retorna tamanho 0
        return 0;
    size_t curr_pos = ftell(f);
    fseek(f, 0, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, curr_pos, SEEK_SET);
    return sz;
}

int get_perm(char *path) {
    struct stat info;
    stat(path, &info);
    return info.st_mode;
}

time_t get_modtime(char *path) {
    struct stat info;
    stat(path, &info);
    return info.st_mtim.tv_sec;
}

void open_space(FILE *f, size_t space, size_t pos) {
    size_t curr_pos = ftell(f);
    size_t sz = get_size(f);
    uchar buffer[BUFFERSIZE] = {0};
    size_t btm = sz - pos + 1;

    ftruncate(fileno(f), sz + space);

    size_t remainder = btm % BUFFERSIZE;
    fseek(f, -(space + remainder), SEEK_END);
    fread(buffer, 1, remainder, f);
    fseek(f, -remainder, SEEK_END);
    fwrite(buffer, 1, remainder, f);
    btm -= remainder;

    fseek(f, -remainder, SEEK_END);
    for (size_t i = 1; i <= btm / BUFFERSIZE; i++) {
        fseek(f, -(space + BUFFERSIZE), SEEK_CUR);
        fread(buffer, 1, BUFFERSIZE, f);
        fseek(f, space - BUFFERSIZE, SEEK_CUR);
        fwrite(buffer, 1, BUFFERSIZE, f);
        fseek(f, -BUFFERSIZE, SEEK_CUR);
    }

    fseek(f, curr_pos, SEEK_SET);
}

void remove_space(FILE *f, size_t space, size_t pos) {
    uchar buffer[BUFFERSIZE] = {0};
    size_t sz = get_size(f);
    size_t bytes_read;

    if (sz <= pos + space) {
        ftruncate(fileno(f), pos);
        rewind(f);
        return;
    }

    int file_over;
    fseek(f, pos + space, SEEK_SET);
    do {
        bytes_read = fread(buffer, 1, BUFFERSIZE, f);
        file_over = feof(f);
        fseek(f, -(space + bytes_read), SEEK_CUR);
        fwrite(buffer, 1, bytes_read, f);
        fseek(f, space, SEEK_CUR);
    } while (!file_over);
    ftruncate(fileno(f), sz - space);
    rewind(f);
}

size_t peek_dir(char *path, char ***childv) {
    DIR *d = opendir(path);
    if (!d)
        return 0;
    size_t childc = 0;
    struct dirent *child = NULL;
    while ((child = readdir(d)) != NULL) {
        if (strncmp(child->d_name, ".", MAX_FNAME_LEN) != 0 &&
            strncmp(child->d_name, "..", MAX_FNAME_LEN) != 0) {
            *childv = reallocarray(*childv, ++childc, sizeof(char*));
            (*childv)[childc-1] = calloc(MAX_FNAME_LEN, sizeof(char));
            if (!(*childv)[childc-1])
                MEM_ERR(1, "libbin.c: peek_dir()");
            strncpy((*childv)[childc-1], child->d_name, MAX_FNAME_LEN);
        }
    }
    closedir(d);
    return childc;
}
