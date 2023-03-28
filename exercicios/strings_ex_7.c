/* Colocar entre colchetes ([ ]) os caracteres de uma string que não sejam letras, números ou espaço; as alterações devem ser feitas na própria string, sem usar string auxiliar. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

void inserir_na_string(char string[MAX + 1], int posicao, char caracter) {
    size_t i;
    for (i = strlen(string) + 1; i > posicao; i--) {
        string[i] = string[i - 1];
    }
    string[posicao] = caracter;
}

int caracter_estranho(char c) {
    if (c == ' ')
        return 0;
    if ('0' <= c && c <= '9')
        return 0;
    if ('A' <= c && c <= 'Z')
        return 0;
    if ('a' <= c && c <= 'z')
        return 0;
    return 1;
}

int main(void) {
    char input[MAX + 1];

    printf("Insira uma string:\n");
    scanf("%s", input);
    
    size_t i;
    for (i = 0; i < strlen(input); i++) {
        if (caracter_estranho(input[i])) {
            inserir_na_string(input, i, '[');
            inserir_na_string(input, i+2, ']');
            i += 2;
        }
    }

    printf("%s\n", input);

    return 0;
}
