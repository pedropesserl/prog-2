#include <unistd.h>
#include "libbin.h"
#include "libarchiver.h"
#include "remove.h"

static void remove_trunc(FILE *archive, struct File_info *dir,
                         size_t dirnmemb, char *member_name) {
    char std_name[MAX_FNAME_LEN];
    standardize_name(member_name, std_name);
    size_t member_ord = get_ord(dir, dirnmemb, std_name);
    if (member_ord == 0) {
        printf("O membro %s não está no archive especificado. Ignorado.\n", member_name);
        return;
    }
    // atualiza dir
    for (size_t i = member_ord-1; i < dirnmemb-1; i++) {
        dir[i+1].pos -= dir[member_ord-1].size;
        dir[i+1].ord--;
        dir[i] = dir[i+1];
    }
    dir = reallocarray(dir, --dirnmemb, sizeof(struct File_info));
    if (dirnmemb == 0) { // archive resultante será vazio
        ftruncate(fileno(archive), 0); // remove os bytes que guardavam a posição de dir
        return;
    } else if (!dir)
        MEM_ERR(1, "remove.c:29");

    // remove espaço previamente ocupado pelo membro
    remove_space(archive, dir[member_ord-1].size, dir[member_ord-1].pos);
    // remove espaço previamente ocupado pelos metadados do membro no archive
    remove_space(archive, sizeof(struct File_info),
            get_size(archive) - sizeof(struct File_info));

    // escreve a nova posição do diretório no início do archive
    size_t new_dir_pos = dir[dirnmemb-1].pos + dir[dirnmemb-1].size;
    rewind(archive);
    fwrite(&new_dir_pos, sizeof(size_t), 1, archive);
    // reescreve o diretório no fim do archive
    fseek(archive, new_dir_pos, SEEK_SET);
    fwrite(dir, sizeof(struct File_info), dirnmemb, archive);
    rewind(archive);
}

void remove_from_archive(char *archive_path, int nmemb, char **membv) {
    FILE *archive = fopen(archive_path, "rb+");
    if (!archive) {
        FDNE_WARN(archive_path);
        exit(0);
    }
    size_t dirnmemb = 0;
    struct File_info *dir = read_dir(archive, &dirnmemb);
    
    for (int i = 0; i < nmemb; i++)
        remove_trunc(archive, dir, dirnmemb, membv[i]);
}
