#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libarchiver.h"
#include "libbin.h"
#include "extract.h"

static void extract(FILE *archive, struct File_info *dir,
                    size_t dirnmemb, char *member_name) {
    char std_name[MAX_FNAME_LEN] = {0};
    standardize_name(member_name, std_name);
    size_t member_ord = get_ord(dir, dirnmemb, std_name);
    if (member_ord == 0) {
        NOT_IN_ARCH_WARN(member_name);
        return;
    }
    // criar os diretórios no caminho do membro
    size_t std_name_sz = strnlen(std_name, MAX_FNAME_LEN);
    char name_so_far[MAX_FNAME_LEN] = {0};
    name_so_far[0] = '.';
    name_so_far[1] = '/';
    for (size_t i = 2; i < std_name_sz; i++) {
        if (std_name[i] == '/') {
            DIR *d = opendir(name_so_far);
            if (d) {
                closedir(d);
            } else {
                int perms = get_perms_from_dir(dir, dirnmemb, name_so_far);
                mkdir(name_so_far, perms);
            }
        }
        name_so_far[i] = std_name[i];
    }
    // criar membro
    FILE *extracted = fopen(std_name, "rb");
    if (extracted) {
        fclose(extracted);
        EXISTS_WARN(member_name);
    }

    int perms = get_perms_from_dir(dir, dirnmemb, std_name);

    if ((perms & S_IFMT) == S_IFDIR) {
        mkdir(std_name, perms);
        return;
    }

    int fd = creat(std_name, perms);
    if (fd < 0)
        OPEN_ERR(2, std_name);
    extracted = fdopen(fd, "wb");
    if (!extracted)
        OPEN_ERR(3, std_name);

    uchar buffer[BUFFERSIZE];
    size_t i = 0;
    for (; i < dir[member_ord-1].size / BUFFERSIZE; i++) {
        fseek(archive, dir[member_ord-1].pos + i*BUFFERSIZE, SEEK_SET);
        fread(buffer, 1, BUFFERSIZE, archive);
        fwrite(buffer, 1, BUFFERSIZE, extracted);
    }
    size_t remainder = dir[member_ord-1].size % BUFFERSIZE;
    fseek(archive, dir[member_ord-1].pos + i*BUFFERSIZE, SEEK_SET);
    fread(buffer, 1, remainder, archive);
    fwrite(buffer, 1, remainder, extracted);

    fclose(extracted);
}

void extract_from_archive(char *archive_path, int nmemb, char **membv) {
    FILE *archive = fopen(archive_path, "rb+");
    if (!archive) {
        DNE_WARN(archive_path);
        return;
    }
    if (get_size(archive) == 0) {
        fclose(archive);
        printf("O arquivo %s está vazio.\n", archive_path);
    }
    size_t dirnmemb = 0;
    struct File_info *dir = read_dir(archive, &dirnmemb);

    if (nmemb > 0) {
        // depois de extrair o arquivo, se for um diretório, extrai os filhos.
        for (int i = 0; i < nmemb; i++) {
            extract(archive, dir, dirnmemb, membv[i]);
            char dir_name[MAX_FNAME_LEN] = {0};
            size_t dir_name_sz = make_dir_name(membv[i], dir_name);
            for (size_t j = 0; j < dirnmemb; j++)
                if (strncmp(dir[j].name, dir_name, dir_name_sz) == 0)
                    extract(archive, dir, dirnmemb, dir[j].name);
        }
    } else {
        for (size_t i = 0; i < dirnmemb; i++) {
            extract(archive, dir, dirnmemb, dir[i].name);
            char dir_name[MAX_FNAME_LEN] = {0};
            size_t dir_name_sz = make_dir_name(membv[i], dir_name);
            for (size_t j = 0; j < dirnmemb; j++)
                if (strncmp(dir[j].name, dir_name, dir_name_sz) == 0)
                    extract(archive, dir, dirnmemb, dir[j].name);
        }
    }

    fclose(archive);
    free(dir);
}
