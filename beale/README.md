Nome: Pedro Folloni Pesserl
GRR: GRR20220072

Esse é um trabalho desenvolvido para a disciplina CI1002 - Programação 2, do Departamento de Informática da UFPR. Implementa um programa que codifica e decodifica mensagens em arquivos de texto ASCII seguindo um livro-cifra, nos moldes das Cifras de Beale.


### Estruturas de dados utilizadas:

A principal estrutura de dados implementada nesse trabalho foi uma lista ligada de listas ligadas de inteiros.
A lista é composta pelas seguintes estruturas, definidas na biblioteca lista.h:

- Nó da lista de inteiros: contém um inteiro e um ponteiro para o próximo nó
```c
typedef struct no_int {
    struct no_int *prox;
    int elem;
} No_int;
```

- Cabeça da lista de inteiros: contém um ponteiro para o nó inicial e o tamanho da lista
```c
typedef struct lista_int {
    No_int *ini;
    size_t tamanho;
} L_int;
```

- Nó da lista de listas: contém um ponteiro para a cabeça da lista de inteiros contida, uma chave representada por um caracter e um ponteiro para o próximo nó
```c
typedef struct no_lista {
    struct no_lista *prox;
    char chave;
    L_int *elem;
} No_lista;
```

- Cabeça da lista de listas: contém um ponteiro para o nó inicial inicial e o tamanho da lista
```c
typedef struct lista_lista {    
    No_lista *ini;
    size_t tamanho;
} L_lista;
```

Essa lista é utilizada para armazenar as chaves de codificação geradas a partir da leitura do livro-cifra, no seguinte formato: um nó da lista de listas que contém a chave 'a' também contém a lista de inteiros referente às posições de palavras que começam com a letra 'a' ou 'A' no livro-cifra. 


### Bibliotecas utilizadas:

- `lista.[hc]`: Define as structs acima, além de funções para criar, imprimir, destruir e manipular listas de inteiros e listas de listas de várias formas. O tempo de acesso aos elementos é linear, devido à estrutura utilizada.
- `chaves.[hc]`: Inclui `lista.h`. Define funções para criar uma lista de chaves no formato descrito acima, a partir de um arquivo de chaves e a partir de um livro-cifra. Também inclui uma função para exportar um arquivo de chaves, no formato especificado em https://wiki.inf.ufpr.br/maziero/doku.php?id=prog2:cifras_de_baele.
- `codificacao.[hc]`: Inclui `lista.h` e `chaves.h`. Define uma função para codificar uma mensagem em um arquivo ASCII usando um livro-cifra, e cria uma lista de chaves usando a função descrita acima.
- `decodificacao.[hc]`: Inclui `lista.h` e `chaves.h`. Define funções para decodificar uma mensagem codificada a partir de um arquivo de chaves e a partir de um livro cifra. Usa as funções de `chaves.h` para criar as listas de chaves.

Todas essas bibliotecas são inclusas em `beale.c`. Nas três últimas, os valores de retorno das funções são padronizados da seguinte forma:
- se a operação for bem-sucedida, retorna 0;
- se houver erro de alocação de memória, retorna 1;
- se houver erro ao abrir/escrever um arquivo, retorna 2, 3 ou 5, a depender da função;
- se houver a necessidade de escrever em um arquivo que já existe, retorna 4.
Esses códigos de erro são tratados em beale.c.
