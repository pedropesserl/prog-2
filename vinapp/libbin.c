/* #include <sys/stat.h> */
/* #include <sys/types.h> */
/* #include <unistd.h> */
#include "libbin.h"
#ifndef BUFFERSIZE
#define BUFFERSIZE 1024
#endif

size_t get_size(FILE *f) {
    fseek(f, 0, SEEK_END);
    size_t sz = ftell(f);
    rewind(f);
    return sz;
}

void open_space(FILE *f, size_t space, size_t pos) {
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
}
