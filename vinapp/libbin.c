#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include "libbin.h"

size_t get_size(FILE *f) {
    size_t curr_pos = ftell(f);
    fseek(f, 0, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, curr_pos, SEEK_SET);
    return sz;
}

void open_space(FILE *f, size_t space, size_t pos) {
    size_t curr_pos = ftell(f);
    uchar buffer[BUFFERSIZE] = {0};
    size_t sz = get_size(f);
    size_t btm = sz - pos + 1;

    ftruncate(fileno(f), sz + space);

    size_t remainder = btm % BUFFERSIZE;
    fseek(f, -(space + remainder), SEEK_END);
    fread(buffer, 1, remainder, f);
    fseek(f, -remainder, SEEK_END);
    fwrite(buffer, 1, remainder, f);
    btm -= remainder;

    fseek(f, -remainder, SEEK_END);
    for (size_t i = 1; i <= btm / BUFFERSIZE; i++) {
        fseek(f, -(space + i*BUFFERSIZE), SEEK_CUR);
        fread(buffer, 1, BUFFERSIZE, f);
        fseek(f, -(remainder + i*BUFFERSIZE), SEEK_END);
        fwrite(buffer, 1, BUFFERSIZE, f);
    }

    fseek(f, curr_pos, SEEK_SET);
}

void remove_space(FILE *f, size_t space, size_t pos) {
    uchar buffer[BUFFERSIZE] = {0};
    size_t sz = get_size(f);
    size_t bytes_read;

    if (sz <= pos + space) {
        ftruncate(fileno(f), pos);
        rewind(f);
        return;
    }

    int file_over;
    fseek(f, pos + space, SEEK_SET);
    do {
        bytes_read = fread(buffer, 1, BUFFERSIZE, f);
        file_over = feof(f);
        fseek(f, -(space + bytes_read), SEEK_CUR);
        fwrite(buffer, 1, bytes_read, f);
        fseek(f, space, SEEK_CUR);
    } while (!file_over);
    ftruncate(fileno(f), sz - space);
    rewind(f);
}
