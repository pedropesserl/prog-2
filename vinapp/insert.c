#include <string.h>
#include "libarchiver.h"
#include "insert.h"

// Se o nome de um arquivo não tiver caminho relativo, padroniza para que tenha.
static void standardize_members(size_t nmemb, char **membv) {
    for (size_t i = 0; i < nmemb; i++) {
        if (membv[i][0] == '/') {
            char *relative = malloc(MAX_FNAME_LEN);
            snprintf(relative, MAX_FNAME_LEN, ".%s", membv[i]);
            membv[i] = relative;
        } else if (membv[i][0] != '.' || membv[i][1] != '/') {
            char *relative = malloc(MAX_FNAME_LEN);
            snprintf(relative, MAX_FNAME_LEN, "./%s", membv[i]);
            membv[i] = relative;
        }
    }
}

static struct File_info fill_file_info(struct File_info *dir,
                                       FILE *member,
                                       char *member_name,
                                       size_t member_ord) {
    struct File_info memb;
    strncpy(memb.name, member_name, MAX_FNAME_LEN);
    get_uid(memb.uid, member_name);
    get_gid(memb.gid, member_name);
    get_perm(memb.perm, member_name);
    get_modtime(memb.td, member_name);
    memb.size = get_size(member);
    memb.ord = member_ord;
    memb.pos = get_pos(dir, member_ord);
    return memb;
}

static void insert(FILE *archive, char *member_name) {
    struct File_info *dir = NULL;
    size_t dirnmemb = 0;
    if (get_size(archive) == 0) {
        dir = (struct File_info*)calloc(1, sizeof(struct File_info));
        if (!dir)
            MEM_ERR(1);
    } else {
        dir = read_dir(archive, &dirnmemb);
    }
    
    size_t member_ord, old_size = 0;
    int is_new_member = get_ord(dir, dirnmemb, member_name) == 0;
    if (is_new_member) {
        dir = reallocarray(dir, ++dirnmemb, sizeof(struct File_info));
        if (!dir)
            MEM_ERR(1);
        member_ord = dirnmemb;
    } else {
        member_ord = get_ord(dir, dirnmemb, member_name);
        old_size = dir[member_ord-1].size;
    }

    FILE *member = fopen(member_name, "rb");
    if (!member)
        FDNE_ERR(3, member_name);

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

void insert_in_archive(char *archive_path, int nmemb, char **membv) {
    standardize_members(nmemb, membv);

    FILE *archive = fopen(archive_path, "rb+");
    if (!archive)
        archive = fopen(archive_path, "wb+");
    for (int i = 0; i < nmemb; i++) {
        insert(archive, membv[i]);
    }
}
