#include <unistd.h>
#include "libbin.h"
#include "libarchiver.h"
#include "remove.h"

static void remove_trunc(FILE *archive, struct File_info **dir,
                         size_t *dirnmemb, char *member_name) {
    char std_name[MAX_FNAME_LEN] = {0};
    standardize_name(member_name, std_name);
    size_t member_ord = get_ord(*dir, *dirnmemb, std_name);
    if (member_ord == 0) {
        printf("Aviso: o membro %s não está no archive especificado. Ignorado.\n", member_name);
        return;
    }

    if (*dirnmemb - 1 == 0) { // archive resultante será vazio
        ftruncate(fileno(archive), 0);
        return;
    }

    // remove espaço previamente ocupado pelo membro
    remove_space(archive, (*dir)[member_ord-1].size, (*dir)[member_ord-1].pos);
    // remove espaço previamente ocupado pelos metadados do membro no archive
    ftruncate(fileno(archive), get_size(archive) - sizeof(struct File_info));

    // atualiza dir
    size_t sz_to_rm = (*dir)[member_ord-1].size;
    for (size_t i = member_ord-1; i < *dirnmemb-1; i++) {
        (*dir)[i+1].pos -= sz_to_rm;
        (*dir)[i+1].ord--;
        (*dir)[i] = (*dir)[i+1];
    }
    *dir = reallocarray(*dir, --(*dirnmemb), sizeof(struct File_info));
    if (!(*dir))
        MEM_ERR(1, "remove.c: remove_trunc()");

    write_dir(archive, *dir, *dirnmemb);
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
        remove_trunc(archive, &dir, &dirnmemb, membv[i]);

    fclose(archive);
    free(dir);
}
