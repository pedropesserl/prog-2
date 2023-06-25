Nome: Pedro Folloni Pesserl
GRR: GRR20220072

Esse é um trabalho desenvolvido para a disciplina CI1002 - Programação 2, do
Departamento de Informática da UFPR. Implementa um programa capaz de arquivar um
ou mais arquivos ou diretórios em um único arquivo binário (chamado aqui de "archive").

### Forma de uso:

Para compilar o programa, use `make`.

Uso:
`./vina++ -[iamxrch] <archive> [membro1 [membro2 [...]]]`

Opções (use exatamente uma):
```
    -i <archive> <membro1> [membro2 [...]] Insere um ou mais membros no archive, respeitando a ordem dos parâmetros (membro1, depois membro2 e assim por diante). Se um membro já estiver no archive, será substituído.
    -a <archive> <membro1> [membro2 [...]] Mesmo comportamento da opção -i, mas substitui um membro existente APENAS caso o parâmetro seja mais recente que o arquivado.
    -m <target> <archive> <membro>         Move o membro indicado para imediatamente após o membro target, que deve estar presente em archive.
    -x <archive> [membro1 [membro2 [...]]] Extrai os membros indicados de archive. Se não for especificado nenhum membro, extrai todos os membros.
    -r <archive> <membro1> [membro2 [...]] Remove os membros indicados de archive.
    -c <archive>                           Lista o conteúdo de archive em ordem, incluindo as propriedades de cada membro (nome, UID, permissões, tamanho e data de modificação) e sua ordem no arquivo.
    -h                                     Imprime essa mensagem de ajuda.
```

O formato do arquivo de saída é o seguinte:
- 8 bytes iniciais: dão a posição da área de diretório do archive.
- Área dos arquivos: contém os arquivos que foram inseridos, byte a byte.
- Área de diretório: começa a partir da posição especificada, contém metadados
  sobre os arquivos inseridos em archive.
  Para cada arquivo, contém:
    - nome;
    - user id;
    - group id;
    - modo e permissões;
    - data e hora da última modificação;
    - tamanho;
    - ordem no arquivo;
    - posição no arquivo (dada em bytes).

### Arquivos e diretórios contidos no pacote:

- `libbin.[hc]`: Define macros e funções úteis para manipulação de arquivos binários;
- `libarchiver.[hc]`: Define macros e funções próprias para uso no arquivador. Inclui
  `libbin.h`;
- `insert.[hc]`: Define funções para inserir arquivos no archive, tanto de forma
  destrutiva (sobrescrevendo arquivos de mesmo nome já presentes) quanto preservativa
  (apenas sobrescrevendo caso o novo arquivo tenha data de modificação mais nova que o
  já presente). Se for passado o caminho de um diretório, inclui todos os conteúdos
  do diretório, recursivamente. Inclui `libbin.h` e `libarchiver.h`;
- `remove.[hc]`: Define funções para remover um arquivo do archive. Se for passado o
  caminho de um diretório, remove todos os conteúdos daquele diretório que estiverem
  presentes no archive. Inclui `libbin.h` e `libarchiver.h`;
- `content.[hc]`: Define uma função para ler um archive e imprimir seus conteúdos,
  em um formato similar ao do comando `tar tvf`. Inclui `libbin.h` e `libarchiver.h`;
- `move.[hc]`: Define uma função para mover um arquivo para imediatamente após
  outro no archive -- move todos os bytes do arquivo internamente no archive. Inclui
  `libbin.h` e `libarchiver.h`;
- `extract.[hc]`: Define funções para extrair um arquivo de archive e criá-lo no
  diretório corrente. Se for passado o caminho de um diretório, extrai todos os
  conteúdos do diretório que estiverem presentes no archive. Inclui `libbin.h` e
  `libarchiver.h`;
- `vinapp.c`: Código do programa principal. Interpreta as opções e argumentos
  passados e redireciona o programa para realizar uma das funções descritas acima.
  Inclui `insert.h`, `remove.h`, `content.h`, `move.h` e `extract.h`.

### Algoritmos e estruturas de dados utilizadas:
  A principal estrutura de dados implementada foi um vetor de `struct File_info`,
definida em `libarchiver.h` da seguinte forma:
```c
struct File_info {
    char name[MAX_FNAME_LEN];
    int uid;
    int gid;
    int perm;
    time_t td;
    size_t size;
    size_t ord;
    size_t pos;
};
```
  Quando é inserido um arquivo novo, o vetor é realocado. Essa estrutura foi utilizada
pela praticidade da implementação e pela facilidade de leitura da seção de diretório
do archive: para lermos um vetor de metadados de arquivo, podemos simplesmente ler
a posição no início do archive, pular para essa posição e ler o vetor completo,
calculando seu tamanho em relação ao fim do archive, devido à contiguidade da memória.

  Alguns algoritmos relevantes foram implementados na `libbin.[hc]`, são eles:
`open_space()` e `remove_space()`, que servem genericamente para abrir ou remover um
bloco de um tamanho especificado de um arquivo binário. Esses algoritmos foram úteis nas
outras bibliotecas mencionadas.

  Foi considerado implementar uma versão dessa estrutura por meio de uma tabela hash;
dessa forma, o acesso aos conteúdos de archive seria indexado pelo nome do arquivo,
e teria um tempo de execução menor (na implementação com vetor, a busca pelo arquivo
é feita linearmente, comparando os nomes dos arquivos com o nome do arquivo buscado).
Porém, a implementação da tabela hash é complexa, e o vetor foi escolhido pensando
em entregar um produto funcional no tempo disponível.
