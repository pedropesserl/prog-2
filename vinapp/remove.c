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
    // remover o arquivo
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
