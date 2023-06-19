/* #include <sys/stat.h> */
/* #include <sys/types.h> */
/* #include <unistd.h> */
#include "libbin.h"
#ifndef BUFFERSIZE
#define BUFFERSIZE 1024
#endif

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
    size_t btm = get_size(f) - pos + 1;

    fseek(f, 0, SEEK_END);
    for (size_t s = space; s >= BUFFERSIZE; s -= BUFFERSIZE)
        fwrite(buffer, 1, BUFFERSIZE, f);
    fwrite(buffer, 1, space % BUFFERSIZE, f);

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
    fprintf(stderr, "remove_space(): não implementada\n");
    exit(1);

    uchar buffer[BUFFERSIZE] = {0};

    
    rewind(f);
}
