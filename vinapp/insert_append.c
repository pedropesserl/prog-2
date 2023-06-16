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

static void insert(FILE *archive, char *member_name) {
    struct File_info *dir = NULL;
    size_t dirnmemb = 0;
    if (get_size(archive) == 0) {
        dir = calloc(1, sizeof(struct File_info));
        if (!dir)
            MEM_ERR(1);
    } else {
        dir = read_dir(archive, &dirnmemb);
    }

    int is_new_member = get_ord(dir, dirnmemb, member_name) == 0;
    if (is_new_member) {
        dir = reallocarray(dir, ++dirnmemb, sizeof(struct File_info));
        if (!dir)
            MEM_ERR(1);
    }

    FILE *member = fopen(member_name, "rb");
    if (!member)
        FDNE_ERR(3, member_name);

    dir[dirnmemb-1] = (struct File_info){
        .name = member_name,
        .uid = get_uid(member),
        .gid = get_gid(member),
        .perms = get_perms(member),
        .td = get_td_f(),
        .size = get_size(member),
        .ord = dirnmemb,
        .pos = get_curr_pos(dir, dirnmemb)
    };
    
    uchar buffer[BUFFERSIZE];
    if (!is_new_member)
        remove(/* arquivo repetido */);

    fseek(archive, dir[dirnmemb-1].pos ,SEEK_SET);

    size_t bytes_read = fread(buffer, 1, BUFFERSIZE, member);
    while (!feof(member)) {
        fwrite(buffer, 1, bytes_read, archive);
        bytes_read = fread(buffer, 1, BUFFERSIZE, member);
    }
    if (bytes_read) // leu até o fim, mas ainda sobraram bytes
        fwrite(buffer, 1, bytes_read, archive);

    // reescreve o diretório no fim do archive, e sua nova posição no início
    fwrite(dir, sizeof(struct File_info), dirnmemb, archive);
    rewind(archive);
    size_t new_dir_pos = dir[dirnmemb-1].pos + dir[dirnmemb-1].size;
    fwrite(&new_dir_pos, sizeof(size_t), 1, archive);
}

void insert_in_archive(char *archive_path, int nmemb, char **membv) {
    standardize_members(int nmemb, char **membv);

    FILE *archive = fopen(archive_path, "rb+");
    if (!archive)
        FOPEN_ERR(2, archive_path);
    for (int i = 0; i < nmemb; i++)
        insert(archive, membv[i]);
}
