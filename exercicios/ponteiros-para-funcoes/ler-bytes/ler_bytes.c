#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4

union Char {
    struct {
        char b0:1;
        char b1:1;
        char b2:1;
        char b3:1;
        char b4:1;
        char b5:1;
        char b6:1;
        char b7:1;
    };
    char B;
};

// inverte o quinto e sexto bits mais significativos
char byte0(char b) {
    union Char byte = (union Char)b;
    byte.b3 = !byte.b3;
    byte.b2 = !byte.b2;
    return byte.B;
}

// inverte o msb
char byte1(char b) {
    return (unsigned char)b > 128 ? b - 128 : b + 128;
}

// inverte o lsb
char byte2(char b) {
    return b % 2 ? b - 1 : b + 1;
}

// inverte o segundo e quarto bit menos significativos
char byte3(char b) {
    union Char byte = (union Char)b;
    byte.b1 = !byte.b1;
    byte.b3 = !byte.b3;
    return byte.B;
}

int main(int argc, char **argv) {
    if (argc != 2)
        return 1;
    
    FILE *input = fopen(argv[1], "rb");
    if (!input)
        return 2;

    FILE *output = fopen("out.bin", "wb");
    if (!output)
        return 3;

    char buffer[BUFFER_SIZE];

    char (*vetor_de_funcoes[4]) (char) = { byte0, byte1, byte2, byte3 };
    
    size_t bytes_lidos = fread(buffer, 1, 4, input);
    while (!feof(input)) {
        for (size_t i = 0; i < bytes_lidos; i++)
            buffer[i] = vetor_de_funcoes[i](buffer[i]);

        fwrite(buffer, 1, bytes_lidos, output);
        bytes_lidos = fread(buffer, 1, 4, input);
    }
    if (bytes_lidos) // leu até o fim, mas ainda sobraram bytes
        fwrite(buffer, 1, bytes_lidos, output);

    fclose(input);
    fclose(output);

    return 0;
}
