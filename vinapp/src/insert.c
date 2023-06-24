#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <time.h>
#include "libarchiver.h"
#include "insert.h"

static struct File_info fill_file_info(struct File_info *dir,
                                       FILE *member,
                                       char *member_name,
                                       size_t member_ord) {
    struct File_info memb;

    char std[MAX_FNAME_LEN] = {0};
    standardize_name(member_name, std);
    strncpy(memb.name, std, MAX_FNAME_LEN);

    get_uid(memb.uid, member_name);
    get_gid(memb.gid, member_name);
    memb.perm = get_perm(member_name);
    memb.td = get_modtime(member_name);
    memb.size = get_size(member);
    memb.ord = member_ord;
    memb.pos = get_pos(dir, member_ord);
    return memb;
}

static void insert(FILE *archive, struct File_info **dir,
                   size_t *dirnmemb, char *member_name) {
    size_t memb_name_size = strnlen(member_name, MAX_FNAME_LEN);
    if (member_name[memb_name_size - 1] == '/')
        member_name[memb_name_size - 1] = '\0';

    FILE *member = fopen(member_name, "rb");
    if (!member) {
        DNE_WARN(member_name);
        return;
    }

    char std_name[MAX_FNAME_LEN] = {0};
    standardize_name(member_name, std_name);
    size_t member_ord, old_size = 0;
    int is_new_member = get_ord(*dir, *dirnmemb, std_name) == 0;
    if (is_new_member) {
        *dir = reallocarray(*dir, ++(*dirnmemb), sizeof(struct File_info));
        if (!(*dir))
            MEM_ERR(1, "insert.c: insert() (dir)");
        member_ord = *dirnmemb;
    } else {
        member_ord = get_ord(*dir, *dirnmemb, std_name);
        old_size = (*dir)[member_ord-1].size;
    }

    (*dir)[member_ord-1] = fill_file_info(*dir, member, member_name, member_ord);

    if (!is_new_member) { // arquivo sobrescreve um de mesmo nome no meio do archive
        size_t new = member_ord-1;
        if ((*dir)[new].size > old_size) {
            size_t space_needed = (*dir)[new].size - old_size;
            open_space(archive, space_needed, (*dir)[new].pos + old_size);
            for (size_t i = member_ord; i < *dirnmemb; i++)
                (*dir)[i].pos += space_needed;

        } else if ((*dir)[new].size < old_size) {
            size_t space_leftover = old_size - (*dir)[new].size;
            remove_space(archive, space_leftover, (*dir)[new].pos + (*dir)[new].size);
            for (size_t i = member_ord; i < *dirnmemb; i++)
                (*dir)[i].pos -= space_leftover;
        }
    }

    if ((*dir)[member_ord-1].size > 0) {
        uchar buffer[BUFFERSIZE];
        size_t bytes_read;
        fseek(archive, (*dir)[member_ord-1].pos, SEEK_SET);
        do {
            bytes_read = fread(buffer, 1, BUFFERSIZE, member);
            fwrite(buffer, 1, bytes_read, archive);
        } while (!feof(member));
    }

    write_dir(archive, *dir, *dirnmemb);

    fclose(member);

    // depois de inserir o membro, checa se é um diretório. se for, insere recursivamente.
    char **childv = calloc(1, sizeof(char*));
    if (!childv)
        MEM_ERR(1, "insert.c: insert() (childv)");
    size_t childc = peek_dir(member_name, &childv);
    for (size_t i = 0; i < childc; i++) {
        char child_full_path[MAX_FNAME_LEN] = {0};
        snprintf(child_full_path, MAX_FNAME_LEN, "%s/%s", member_name, childv[i]);
        insert(archive, dir, dirnmemb, child_full_path);
    }
    for (size_t i = 0; i < childc; i++)
        free(childv[i]);
    free(childv);
}

void insert_in_archive(char *archive_path, int nmemb, char **membv) {
    struct File_info *dir = NULL;
    size_t dirnmemb = 0;
    FILE *archive = fopen(archive_path, "rb+");
    if (archive && get_size(archive) > 0) {
        dir = read_dir(archive, &dirnmemb);
    } else {
        if (!archive)
            archive = fopen(archive_path, "wb+");
        else
            archive = freopen(archive_path, "wb+", archive);
        dir = (struct File_info*)calloc(1, sizeof(struct File_info));
        if (!dir)
            MEM_ERR(1, "insert.c: insert_in_archive()");
    }

    for (int i = 0; i < nmemb; i++)
        insert(archive, &dir, &dirnmemb, membv[i]);

    fclose(archive);
    free(dir);
}

void update_archive(char *archive_path, int nmemb, char **membv) {
    struct File_info *dir = NULL;
    size_t dirnmemb = 0;
    FILE *archive = fopen(archive_path, "rb+");
    if (archive && get_size(archive) > 0) {
        dir = read_dir(archive, &dirnmemb);
    } else {
        if (!archive)
            archive = fopen(archive_path, "wb+");
        else
            archive = freopen(archive_path, "wb+", archive);
        dir = (struct File_info*)calloc(1, sizeof(struct File_info));
        if (!dir)
            MEM_ERR(1, "insert.c: update_archive()");
    }

    for (int i = 0; i < nmemb; i++) {
        char std_name[MAX_FNAME_LEN];
        standardize_name(membv[i], std_name);
        size_t member_ord = get_ord(dir, dirnmemb, std_name);
        if (member_ord == 0) {
            insert(archive, &dir, &dirnmemb, membv[i]);
        } else {
            time_t mtd = get_modtime(membv[i]);
            if (mtd == 0) {
                DNE_WARN(membv[i]);
                continue;
            }
            if (difftime(mtd, dir[member_ord-1].td) > 0)
                insert(archive, &dir, &dirnmemb, membv[i]);
            else {
                printf("O membro %s não é mais novo que sua ", membv[i]);
                printf("contraparte em %s. Ignorado.\n", archive_path);
            }
        }
    }

    fclose(archive);
    free(dir);
}
