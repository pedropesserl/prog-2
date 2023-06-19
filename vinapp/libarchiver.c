#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <grp.h>
#include <pwd.h>
/* #include <unistd.h> */
#include "libbin.h"
#include "libarchiver.h"

#define BUFFERSIZE 1024

struct File_info *read_dir(FILE *archive, size_t *dirnmemb) {
    size_t dirpos;
    // a posição (0-indexed) da seção do diretório está no início do archive
    fread(&dirpos, sizeof(size_t), 1, archive);
    fseek(archive, dirpos, SEEK_SET);
    size_t dirsize = get_size(archive) - dirpos;
    *dirnmemb = dirsize / sizeof(struct File_info);
    struct File_info *dir = (struct File_info*)calloc(*dirnmemb, sizeof(struct File_info));
    if (!dir)
        MEM_ERR(1);
    
    fread(dir, sizeof(struct File_info), *dirnmemb, archive);
    rewind(archive);
    return dir;
}

char *get_uid(char *path) {
    struct stat info;
    stat(path, &info);
    struct passwd *pwd = getpwuid(info.st_uid);
    return pwd->pw_name;
}

char *get_gid(char *path) {
    struct stat info;
    stat(path, &info);
    struct group *grp = getgrgid(info.st_gid);
    return grp->gr_name;
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

char *get_perm(char *path) {
    struct stat info;
    stat(path, &info);
    char *perm = (char*)calloc(11, sizeof(char)); // "drwxrwxrwx\0"
    perms[0] = get_mode(info.st_mode);
    perms[1] = (info.st_mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (info.st_mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (info.st_mode & S_IXUSR) ? 'x' : '-';
    perms[4] = (info.st_mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (info.st_mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (info.st_mode & S_IXGRP) ? 'x' : '-';
    perms[7] = (info.st_mode & S_IROTH) ? 'r' : '-';
    perms[8] = (info.st_mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (info.st_mode & S_IXOTH) ? 'x' : '-';
    perms[10] = '\0';
    return perm;
} 

char *get_modtime(char *path) {
    struct stat info;
    stat(path, &info);
    char *tm = (char*)calloc(17, sizeof(char)); // "YYYY-MM-DD hh:mm\0"
    if (!tm)
        MEM_ERR(1);
    strftime(tm, 17, "%Y-%m-%d %H:%M", localtime(&info.st_ctime));
    return tm;
}

size_t get_ord(struct File_info *dir, size_t dirnmemb, char *member_name) {
    for (size_t i = 0; i < dirnmemb; i++)
        if (strncmp(dir[i].name, member_name, MAX_FNAME_LEN) == 0)
            return i + 1;
    return 0;
}

size_t get_pos_from_ord(struct File_info *dir, size_t ord) {
    size_t pos = sizeof(size_t) - 1; // os primeiros bytes guardam a posição do diretório
    for (size_t i = 0; i < ord-1; i++)
        pos += dir[i].size;
    return pos;
}
