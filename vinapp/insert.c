#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#define __USE_XOPEN
#define _GNU_SOURCE
#include <time.h>
#include "libarchiver.h"
#include "insert.h"

// Compara o tempo de modificação do arquivo de nome new_memb com o armazenado
// em dir na ordem old_ord. Retorna um valor maior que, menor que, ou igual a
// 0 se o novo membro for respectivamente mais novo, de tempo igual, ou mais velho
// que o membro já armazenado.
static double compare_modtimes(struct File_info *dir, size_t old_ord, char *new_memb) {
    struct tm old_tm = {0};
    strptime(dir[old_ord-1].td, "%Y-%m-%d %H:%M", &old_tm);
    time_t old_time = mktime(&old_tm);

    struct stat new_info;
    stat(new_memb, &new_info);
    struct tm *new_tm = localtime(&new_info.st_mtim.tv_sec);
    new_tm->tm_sec = 0;
    time_t new_time = mktime(new_tm);

    return difftime(new_time, old_time);
}

static struct File_info fill_file_info(struct File_info *dir,
                                       FILE *member,
                                       char *member_name,
                                       size_t member_ord) {
    struct File_info memb;

    char std[MAX_FNAME_LEN];
    standardize_name(member_name, std);
    strncpy(memb.name, std, MAX_FNAME_LEN);

    get_uid(memb.uid, member_name);
    get_gid(memb.gid, member_name);
    get_perm(memb.perm, member_name);
    get_modtime(memb.td, member_name);
    memb.size = get_size(member);
    memb.ord = member_ord;
    memb.pos = get_pos(dir, member_ord);
    return memb;
}

static void insert(FILE *archive, struct File_info *dir,
                   size_t dirnmemb, char *member_name) {
    char std_name[MAX_FNAME_LEN];
    standardize_name(member_name, std_name);
    size_t member_ord, old_size = 0;
    int is_new_member = get_ord(dir, dirnmemb, std_name) == 0;
    if (is_new_member) {
        dir = reallocarray(dir, ++dirnmemb, sizeof(struct File_info));
        if (!dir)
            MEM_ERR(1, "insert.c:58");
        member_ord = dirnmemb;
    } else {
        member_ord = get_ord(dir, dirnmemb, std_name);
        old_size = dir[member_ord-1].size;
    }

    FILE *member = fopen(member_name, "rb");
    if (!member)
        FDNE_WARN(member_name);

    dir[member_ord-1] = fill_file_info(dir, member, member_name, member_ord);

    if (!is_new_member) { // arquivo sobrescreve um de mesmo nome no meio do archive
        size_t new = member_ord-1;
        if (dir[new].size > old_size) {
            size_t space_needed = dir[new].size - old_size;
            open_space(archive, space_needed, dir[new].pos + old_size);
            for (size_t i = member_ord; i < dirnmemb; i++)
                dir[i].pos += space_needed;

        } else if (dir[new].size < old_size) {
            size_t space_leftover = old_size - dir[new].size;
            remove_space(archive, space_leftover, dir[new].pos + dir[new].size);
            for (size_t i = member_ord; i < dirnmemb; i++)
                dir[i].pos -= space_leftover;
        }
    }

    // escreve a nova posição do diretório no início do archive
    size_t new_dir_pos = dir[dirnmemb-1].pos + dir[dirnmemb-1].size;
    rewind(archive);
    fwrite(&new_dir_pos, sizeof(size_t), 1, archive);

    uchar buffer[BUFFERSIZE];
    size_t bytes_read;
    fseek(archive, dir[member_ord-1].pos, SEEK_SET);
    do {
        bytes_read = fread(buffer, 1, BUFFERSIZE, member);
        fwrite(buffer, 1, bytes_read, archive);
    } while (!feof(member));

    // reescreve o diretório no fim do archive
    fseek(archive, new_dir_pos, SEEK_SET);
    fwrite(dir, sizeof(struct File_info), dirnmemb, archive);
    rewind(archive);
}

void insert_overwrite(char *archive_path, int nmemb, char **membv) {
    struct File_info *dir = NULL;
    size_t dirnmemb = 0;
    FILE *archive = fopen(archive_path, "rb+");
    if (!archive) {
        archive = fopen(archive_path, "wb+");
        dir = (struct File_info*)calloc(1, sizeof(struct File_info));
        if (!dir)
            MEM_ERR(1, "insert.c:114");
    } else {
        dir = read_dir(archive, &dirnmemb);
    }

    for (int i = 0; i < nmemb; i++)
        insert(archive, dir, dirnmemb, membv[i]);
}

void insert_soft(char *archive_path, int nmemb, char **membv) {
    struct File_info *dir = NULL;
    size_t dirnmemb = 0;
    FILE *archive = fopen(archive_path, "rb+");
    if (!archive) {
        archive = fopen(archive_path, "wb+");
        dir = (struct File_info*)calloc(1, sizeof(struct File_info));
        if (!dir)
            MEM_ERR(1, "insert.c:131");
    } else {
        dir = read_dir(archive, &dirnmemb);
    }

    for (int i = 0; i < nmemb; i++) {
        char std_name[MAX_FNAME_LEN];
        standardize_name(membv[i], std_name);
        size_t member_ord = get_ord(dir, dirnmemb, std_name);
        if (member_ord == 0) {
            insert(archive, dir, dirnmemb, membv[i]);
        } else {
            if (compare_modtimes(dir, member_ord, membv[i]) > 0)
                insert(archive, dir, dirnmemb, membv[i]);
        }
    }
}
