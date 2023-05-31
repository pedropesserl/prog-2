#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define uchar unsigned char

typedef enum { NOP, ENCODE, DECODE } Modo_t;

struct RLE {
    char byte;
    uchar freq;
};

#define BUFFER_SIZE 10

void open_file_err(char *filename) {
    fprintf(stderr, "Erro ao abrir arquivo %s.\n", filename);
    exit(4);
}

void file_exists_err(char *filename) {
    fprintf(stderr, "Erro: o arquivo %s já existe.\n", filename);
    exit(5);
}

// PROTÓTIPOS

// Função que comprime 'fIn', gravando o resultado da compressão em 'fOut'
void Encode(char *fIn, char *fOut);

// Função que descomprime 'fIn', gravando o resultado da descompressão em 'fOut'
void Decode(char *fIn, char *fOut);

// Função  ser  usada  no  programa para  chamar  Encode()  ou  Decode()
void rle(char *fIn, char *fOut, void (acao)(char*, char*));


// PROGRAMA PRINCIPAL
int main(int argc, char **argv) {
    int opt;
    char *input = NULL;
    char *output = NULL;
    Modo_t modo = NOP;

    while ((opt = getopt(argc, argv, "dei:o:")) != -1) {
    switch (opt) {
        case 'i':
            input = strdup(optarg);
            break;
        case 'o':
            output = strdup(optarg);
            break;
        case 'e':
            modo |= ENCODE;
            break;
        case 'd':
            modo |= DECODE;
            break;
        default:
            fprintf(stderr, "Forma de uso: ./rle [-e | -d] -i <arq_in> -o <arq_out>\n");
            exit(1);
        }		
    }

    // Erro se:
    //  * não forneceu os dois arquivos
    //  * não forneceu uma das opções '-e' ou '-d',
    //  * forneceu as opções '-e' e '-d' na mesma linha de comando
    if (!input || !output || modo == NOP || modo & (modo-1)) {
        fprintf(stderr, "Forma de uso: ./rle [-e | -d] -i <arq_in> -o <arq_out>\n");
        exit(2);
    }

    /* COMPLEMENTE O CÓDIGO PARA DESENVOLVER O PROGRAMA PRINCIPAL A PARTIR DESTE PONTO */
    if (modo == ENCODE)
        rle(input, output, Encode);
    else if (modo == DECODE)
        rle(input, output, Decode);
    else  // inalcançável
        exit(3);

    return 0;
}

/* DEFINA ABAIXO O CÓDIGO DAS FUNÇÕES Encode(), Decode() e rle()  */

// Função ser usada no programa principal para chamar Encode() ou Decode()
void rle(char *fIn, char *fOut, void (acao)(char*, char*)) {
    return acao(fIn, fOut);
}

// Função que comprime 'fIn', gravando o resultado da compressão em 'fOut'
void Encode(char *fIn, char *fOut) {
    FILE *input = fopen(fIn, "rb");
    if (!input)
        open_file_err(fIn);

    FILE *output = fopen(fOut, "rb");
    if (output) {
        fclose(output);
        file_exists_err(fOut);
    }
    output = fopen(fOut, "wb");
    if (!output)
        open_file_err(fOut);
    
    struct RLE *regvec = (struct RLE*)malloc(BUFFER_SIZE);
    uchar byte;
    fread(&byte, 1, 1, input);
    size_t bytes_lidos = 1;
    while (!feof(input)) {
        int i = 0;
        do {
            regvec[i].byte = byte;
            do {
                regvec[i].freq++;
                fread(&byte, 1, 1, input);
                bytes_lidos++;
            } while (byte == regvec[i].byte && !feof(input));
            i++;
        } while (i < 5 && !feof(input));
        fwrite(regvec, 1, bytes_lidos, output);
        fread(&byte, 1, 1, input);
        bytes_lidos = 1;
    }

    free(regvec);
    fclose(input);
    fclose(output);
}

// Função que descomprime 'fIn', gravando o resultado da descompressão em 'fOut'
void Decode(char *fIn, char *fOut) {
    FILE *input = fopen(fIn, "rb");
    if (!input)
        open_file_err(fIn);

    FILE *output = fopen(fOut, "rb");
    if (output) {
        fclose(output);
        file_exists_err(fOut);
    }
    output = fopen(fOut, "wb");
    if (!output)
        open_file_err(fOut);

    struct RLE *regvec = (struct RLE*)malloc(BUFFER_SIZE);
    do {
        int i = 0;
        int reg_lidos = 0;
        do {
            fread(&(regvec[i].byte), 1, 1, input);
            fread(&(regvec[i].freq), 1, 1, input);
            reg_lidos++;
            i++;
        } while (i < 5 && !feof(input));
        for (int i = 0; i <= reg_lidos; i++)
            for (int j = 0; j < regvec[i].freq; i++)
                fwrite(&(regvec[i].byte), 1, 1, output);
    } while (!feof(input));

    free(regvec);
    fclose(input);
    fclose(output);
}
