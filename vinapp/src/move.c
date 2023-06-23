#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libbin.h"
#include "libarchiver.h"
#include "move.h"

void move_member(char *archive_path, char *target, char *member) {
    struct File_info *dir = NULL;
    FILE *archive = fopen(archive_path, "rb+");
    if (!archive) {
        DNE_WARN(archive_path);
        return;
    }
    if (get_size(archive) == 0) {
        fclose(archive);
        printf("O arquivo %s está vazio.\n", archive_path);
        return;
    }
    size_t dirnmemb = 0;
    dir = read_dir(archive, &dirnmemb);

    char std_target[MAX_FNAME_LEN] = {0};
    standardize_name(target, std_target);
    char std_member[MAX_FNAME_LEN] = {0};
    standardize_name(member, std_member);
    size_t tgt_ord = 0, mbr_ord = 0;
    if ((tgt_ord = get_ord(dir, dirnmemb, std_target)) == 0) {
        NOT_IN_ARCH_WARN(target);
        return;
    }
    if ((mbr_ord = get_ord(dir, dirnmemb, std_member)) == 0) {
        NOT_IN_ARCH_WARN(member);
        return;
    }
    if (strncmp(std_target, std_member, MAX_FNAME_LEN) == 0) {
        printf("Aviso: member e target são o mesmo arquivo. Ignorado.\n");
        return;
    }
    
    size_t mbrsz = dir[mbr_ord-1].size;
    size_t curr_mbrpos = dir[mbr_ord-1].pos;
    size_t new_mbrpos = dir[tgt_ord-1].pos + dir[tgt_ord-1].size;
    open_space(archive, mbrsz, new_mbrpos);
    curr_mbrpos += mbr_ord > tgt_ord ? mbrsz : 0; // a posição de member pode mudar
                                                  // devido à abertura de espaço
    // copia bytes do membro para o espaço aberto
    uchar buffer[BUFFERSIZE];
    size_t i = 0;
    for (; i < mbrsz / BUFFERSIZE; i++) {
        fseek(archive, curr_mbrpos + i*BUFFERSIZE, SEEK_SET);
        fread(buffer, 1, BUFFERSIZE, archive);
        fseek(archive, new_mbrpos + i*BUFFERSIZE, SEEK_SET);
        fwrite(buffer, 1, BUFFERSIZE, archive);
    }
    size_t remainder = mbrsz % BUFFERSIZE;
    fseek(archive, curr_mbrpos + i*BUFFERSIZE, SEEK_SET);
    fread(buffer, 1, remainder, archive);
    fseek(archive, new_mbrpos + i*BUFFERSIZE, SEEK_SET);
    fwrite(buffer, 1, remainder, archive);

    remove_space(archive, mbrsz, curr_mbrpos);

    struct File_info member_info = dir[mbr_ord-1];
    // atualiza diretório
    if (mbr_ord < tgt_ord) {
        for (size_t i = mbr_ord-1; i < tgt_ord-1; i++) {
            dir[i] = dir[i+1];
            dir[i].pos -= mbrsz;
            dir[i].ord--;
        }
        dir[tgt_ord-1] = member_info;
        dir[tgt_ord-1].ord = tgt_ord;
        dir[tgt_ord-1].pos = get_pos(dir, tgt_ord);
    } else {
        for (size_t i = mbr_ord-1; i > tgt_ord-1; i--) {
            dir[i] = dir[i-1];
            dir[i].pos += mbrsz;
            dir[i].ord++;
        }
        dir[tgt_ord] = member_info;
        dir[tgt_ord].ord = tgt_ord + 1;
        dir[tgt_ord].pos = get_pos(dir, tgt_ord + 1);
    }

    write_dir(archive, dir, dirnmemb);

    fclose(archive);
    free(dir);
}
