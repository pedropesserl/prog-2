/* #include <stdio.h> */
/* #include <stdlib.h> */
/* #include <sys/stat.h> */
/* #include <sys/types.h> */
/* #include <unistd.h> */
#include "libbin.h"
#include "archiver.h"

#define BUFFERSIZE 1024

struct File_info *read_dir(const char *archive_path) {
    FILE *archive = fopen(path, "r");
    size_t dirpos;
    // a posição (0-indexed) da seção do diretório está no início do archive
    fread(&dirpos, sizeof(size_t), 1, archive);
    fseek(archive, dirpos, SEEK_SET);

    size_t dirsize = 64;
    struct File_info *dir = (struct File_info*)calloc(dirsize, sizeof(File_info));
    if (!dir)
        MEM_ERR(1);
    
    // FALTA COISA

    fclose(archive);
    return dir;
}

void insert(const char *archive_path, const char *new_path) {
    FILE *archive = ME_read_and_write(archive_path);
    uchar *buffer = malloc(BUFFERSIZE);
    FILE *new = fopen(new_path, "r");
    if (!new)
        FDNE_ERR(3);
    
}

#if 0

#include <stdio.h>
#include <time.h>

int main() {
    time_t t = time(0);
    struct tm *info = localtime(&t);
    printf("%d-%02d-%02d %02d:%02d\n",
            info->tm_year + 1900, info->tm_mon + 1, info->tm_mday,
            info->tm_hour, info->tm_min);
    return 0;
}

#include <stdio.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>

int main(void) {
    const char *file = "/bin/";
    struct stat arch_stat;
    stat(file, &arch_stat);
    printf("modo: %x\n", arch_stat.st_mode);
    printf("GID: %d\n", arch_stat.st_gid);
    printf("UID: %d\n", arch_stat.st_uid);
    struct group *grp = getgrgid(arch_stat.st_gid);
    printf("grupo: %s\n", grp->gr_name);
    struct passwd *pwd = getpwuid(arch_stat.st_uid);
    printf("user: %s\n", pwd->pw_name);
}

#endif
