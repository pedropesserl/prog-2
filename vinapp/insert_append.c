#include "archiver.h"
#include "insert_append.h"

// Se o nome de um arquivo não tiver caminho relativo, padroniza para que tenha.
static void standardize_members(size_t nmemb, char **membv) {
    for (size_t i = 0; i < nmemb; i++) {
        if (membv[i][0] == '/') {
            char *relative = malloc(MAX_FNAME_LEN);
            snprintf(relative, MAX_FNAME_LEN, ".%s", membv[i]);
            membv[i] = relative;
            free(relative);
        } else if (membv[i][0] != '.' || membv[i][1] != '/') {
            char *relative = malloc(MAX_FNAME_LEN);
            snprintf(relative, MAX_FNAME_LEN, "./%s", membv[i]);
            membv[i] = relative;
            free(relative);
        }
    }
}

static void insert_to_end(FILE *archive, char *member_name) {

}

static void insert_overwrite(FILE *archive, char *member_name) {

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
    
    size_t member_ord, size_old = 0;// pos_old = 0; 
    int is_new_member = get_ord(dir, dirnmemb, member_name) == 0;
    if (is_new_member) {
        dir = reallocarray(dir, ++dirnmemb, sizeof(struct File_info));
        if (!dir)
            MEM_ERR(1);
        member_ord = dirnmemb;
    } else {
        member_ord = get_ord(dir, dirnmemb, member_name);
        size_old = dir[member_ord-1]->size;
        /* pos_old = dir[member_ord-1]->pos; */
    }

    FILE *member = fopen(member_name, "rb");
    if (!member)
        FDNE_ERR(3, member_name);

    dir[member_ord-1] = (struct File_info){
        .name = member_name,
        .uid  = get_uid(member_name),
        .gid  = get_gid(member_name),
        .perm = get_perm(member_name),
        .td   = get_modtime(member_name),
        .size = get_size(member),
        .ord  = member_ord,
        .pos  = get_pos_from_ord(dir, member_ord)
    };

    uchar buffer[BUFFERSIZE];
    size_t bytes_read;
    if (!is_new_member) { // arquivo sobrescreve um de mesmo nome no meio do archive
        if (dir[member_ord-1].size > size_old) {
            size_t space_needed = dir[member_ord-1].size - size_old;
            open_space(archive, space_needed, dir[member_ord-1].pos + size_old);
            for (size_t i = member_ord; i < dirnmemb; i++)
                dir[i].pos += space_needed;

        } else if (dir[member_ord-1].size < size_old) {
            size_t space_leftover = size_old - dir[member_ord-1].size;
            remove_space(archive, space_leftover, dir[member_ord-1].pos + dir[member_ord-1].size);
            for (size_t i = member_ord; i < dirnmemb; i++)
                dir[i].pos -= space_leftover;
        }
    }
    /* fseek(archive, dir[member_ord-1].pos, SEEK_SET); */
    /*size_t bytes_read = fread(buffer, 1, BUFFERSIZE, member)*/;
    /* size_t bytes_read = fread(buffer, 1, BUFFERSIZE, member); */
    /* while (!feof(member)) { */
    /*     fwrite(buffer, 1, bytes_read, archive); */
    /*     bytes_read = fread(buffer, 1, BUFFERSIZE, member); */
    /* } */
    /* if (bytes_read) // leu até o fim, mas ainda sobraram bytes */
    /*     fwrite(buffer, 1, bytes_read, archive); */
    // ^
    // | testar se essas duas implementações são equivalentes
    // v
    fseek(archive, dir[member_ord-1].pos, SEEK_SET);
    do {
        bytes_read = fread(buffer, 1, BUFFERSIZE, member);
        fwrite(buffer, 1, bytes_read, archive);
    } while (!feof(member));

    // reescreve o diretório no fim do archive, e sua nova posição no início
    fseek(archive, dir[dirnmemb-1].pos + dir[dirnmemb-1].size);
    fwrite(dir, sizeof(struct File_info), dirnmemb, archive);
    rewind(archive);
    size_t new_dir_pos = dir[dirnmemb-1].pos + dir[dirnmemb-1].size;
    fwrite(&new_dir_pos, sizeof(size_t), 1, archive);
    rewind(archive);
}

void insert_in_archive(char *archive_path, int nmemb, char **membv) {
    standardize_members(int nmemb, char **membv);

    FILE *archive = fopen(archive_path, "rb+");
    if (!archive)
        FOPEN_ERR(2, archive_path);
    for (int i = 0; i < nmemb; i++) {
        insert(archive, membv[i]);
    }
}
