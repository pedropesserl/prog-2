#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
/* #include <sys/types.h> */
/* #include <unistd.h> */
#include "libbin.h"
#include "archiver.h"

#define BUFFERSIZE 1024

struct File_info *read_dir(FILE *archive, size_t *dirnmemb) {
    fseek(archive, 0, SEEK_END);
    size_t sz = ftell(archive);
    rewind(archive);

    size_t dirpos;
    // a posição (0-indexed) da seção do diretório está no início do archive
    fread(&dirpos, sizeof(size_t), 1, archive);
    fseek(archive, dirpos, SEEK_SET);
    size_t dirsize = sz - dirpos;
    *dirnmemb = dirsize / sizeof(struct File_info);
    struct File_info *dir = (struct File_info*)calloc(*dirnmemb, sizeof(File_info));
    if (!dir)
        MEM_ERR(1);
    
    fread(dir, sizeof(struct File_info), *dirnmemb, archive);
    rewind(archive);
    return dir;
}

char *get_td_f() {
    time_t t = time(NULL);
    struct tm *info = localtime(&t);
    char *tf = NULL;
    size_t format_size = 17; // "YYYY-MM-DD hh:mm\0"
    snprintf(tf, format_size, "%d-%02d-%02d %02d:%02d",
            info->tm_year + 1900, info->tm_mon + 1, info->tm_mday,
            info->tm_hour, info->tm_min);
    return tf;
}

static char get_mode(int mode) {
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

char *get_perms(FILE *f) {
    struct stat f_stat;
    stat(f, &f_stat);
    char perms[11]; // "drwxrwxrwx\0"
    perms[0] = get_mode(f_stat.st_mode);
    perms[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
    perms[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
    perms[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
    perms[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
    perms[10] = '\0';
    return perms;
} 

char *get_uid(FILE *f) {
    struct stat f_stat;
    stat(f, &f_stat);
    struct passwd *pwd = getpwuid(f_stat.st_uid);
    return pwd->pw_name;
}

char *get_gid(FILE *f) {
    struct stat f_stat;
    stat(f, &f_stat);
    struct group *grp = getgrgid(f_stat.st_gid);
    return grp->gr_name;
}

size_t get_ord(struct File_info *dir, size_t dirnmemb, char *member_name) {
    for (size_t i = 0; i < dirnmemb; i++)
        if (strncmp(dir[i].name, member_name, MAX_FNAME_LEN) == 0)
            return i + 1;
    return 0;
}

size_t get_curr_pos(struct File_info *dir, size_t ord) {
    size_t pos = sizeof(size_t) - 1; // os primeiros bytes guardam a posição do diretório
    for (size_t i = 0; i < ord-1; i++)
        pos += dir[i].size;
    return pos;
}
