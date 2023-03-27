/* Colocar entre colchetes ([ ]) os caracteres de uma string que não sejam letras, números ou espaço; as alterações devem ser feitas na própria string, sem usar string auxiliar. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

void inserir_na_string(char string[MAX + 1], int posicao, char caracter) {
    int i;
    for (i = strlen(string); i >= posicao; i++) {
        string[i + 1] = string[i];
    }
    string[posicao] = caracter;
}

int main() {
    printf("Insira string de até %d caracteres:\n", MAX);

    char input[MAX + 1];
    scanf("%s", input);
    
    int atual;
    int i, n = strlen(input);
    for (i = 0; i < n; i++) {
        atual = (int)input[i];
        if (atual != 32 && atual < 48 && atual > 57 && atual < 65 && atual > 90 && atual < 97 && atual > 122) {
            printf("achei um caracter estranho!!\n");
            inserir_na_string(input, i, '[');
            inserir_na_string(input, i+2, ']');
            n = strlen(input);
        }
    }

    printf("%s\n", input);

    return 0;
}
