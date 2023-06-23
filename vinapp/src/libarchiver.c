#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <grp.h>
#include <pwd.h>
#include "libbin.h"
#include "libarchiver.h"

struct File_info *read_dir(FILE *archive, size_t *dirnmemb) {
    size_t dirpos;
    // a posição (0-indexed) da seção do diretório está no início do archive
    rewind(archive);
    fread(&dirpos, sizeof(size_t), 1, archive);
    fseek(archive, dirpos, SEEK_SET);
    size_t dirsize = get_size(archive) - dirpos;
    *dirnmemb = dirsize / sizeof(struct File_info);
    struct File_info *dir = (struct File_info*)calloc(*dirnmemb, sizeof(struct File_info));
    if (!dir)
        MEM_ERR(1, "libarchiver.c: read_dir()");
    
    fread(dir, sizeof(struct File_info), *dirnmemb, archive);
    rewind(archive);
    return dir;
}

void write_dir(FILE *archive, struct File_info *dir, size_t dirnmemb) {
    size_t new_dir_pos = dir[dirnmemb-1].pos + dir[dirnmemb-1].size;
    rewind(archive);
    fwrite(&new_dir_pos, sizeof(size_t), 1, archive);
    fseek(archive, new_dir_pos, SEEK_SET);
    fwrite(dir, sizeof(struct File_info), dirnmemb, archive);
    rewind(archive);
}

void get_uid(char *buffer, char *path) {
    struct stat info;
    stat(path, &info);
    struct passwd *pwd = getpwuid(info.st_uid);
    strncpy(buffer, pwd->pw_name, MAX_UNAME_LEN);
}

void get_gid(char *buffer, char *path) {
    struct stat info;
    stat(path, &info);
    struct group *grp = getgrgid(info.st_gid);
    strncpy(buffer, grp->gr_name, MAX_GNAME_LEN);
}

static char format_mode(int mode) {
    char m;
    switch (mode & S_IFMT) {
        case S_IFREG:  m = '-'; break;
        case S_IFBLK:  m = 'b'; break;
        case S_IFCHR:  m = 'c'; break;
        case S_IFDIR:  m = 'd'; break;
        case S_IFLNK:  m = 'l'; break;
        case S_IFIFO:  m = 'p'; break;
        case S_IFSOCK: m = 's'; break;
        default:       m = '?'; break;
    }
    return m;
}

void format_perm(char *buffer, int mode) {
    buffer[0] = format_mode(mode);
    buffer[1] = (mode & S_IRUSR) ? 'r' : '-';
    buffer[2] = (mode & S_IWUSR) ? 'w' : '-';
    buffer[3] = (mode & S_IXUSR) ? 'x' : '-';
    buffer[4] = (mode & S_IRGRP) ? 'r' : '-';
    buffer[5] = (mode & S_IWGRP) ? 'w' : '-';
    buffer[6] = (mode & S_IXGRP) ? 'x' : '-';
    buffer[7] = (mode & S_IROTH) ? 'r' : '-';
    buffer[8] = (mode & S_IWOTH) ? 'w' : '-';
    buffer[9] = (mode & S_IXOTH) ? 'x' : '-';
    buffer[10] = '\0';
} 

void format_modtime(char *buffer, time_t time) {
    struct tm *local = localtime(&time);
    strftime(buffer, 17, "%Y-%m-%d %H:%M", local);
}

size_t get_ord(struct File_info *dir, size_t dirnmemb, char *member_name) {
    for (size_t i = 0; i < dirnmemb; i++)
        if (strncmp(dir[i].name, member_name, MAX_FNAME_LEN) == 0)
            return i + 1;
    return 0;
}

size_t get_pos(struct File_info *dir, size_t ord) {
    if (ord < 1)
        return 0; // Entrada inválida
    if (ord == 1)
        return sizeof(size_t); // Os primeiros bytes guardam a posição do diretório
    return dir[ord-2].pos + dir[ord-2].size;
}

void standardize_name(char *membname, char *buffer) {
    if (membname[0] == '/')
        snprintf(buffer, MAX_FNAME_LEN, ".%s", membname);
    else if (membname[0] != '.' || membname[1] != '/')
        snprintf(buffer, MAX_FNAME_LEN, "./%s", membname);
    else
        strncpy(buffer, membname, MAX_FNAME_LEN);
}

size_t make_dir_name(char *membname, char *buffer) {
    char std_name[MAX_FNAME_LEN-1] = {0};
    standardize_name(membname, std_name);
    snprintf(buffer, MAX_FNAME_LEN, "%s/", std_name);
    return strnlen(buffer, MAX_FNAME_LEN);
}

int get_perms_from_dir(struct File_info *dir, size_t dirnmemb, char *std_name) {
    for (size_t i = 0; i < dirnmemb; i++)
        if (strncmp(std_name, dir[i].name, MAX_FNAME_LEN) == 0)
            return dir[i].perm;
    return 0;
}
