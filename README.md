# Codificação De Huffman

## Bibliotecas Utilizadas
- stdio.h
- string.h
- stdlib.h

## Structs Criadas
1. Codificacao: Struct da lista principal, contendo o ID do caractere, o caractere, sua frequência e dois ponteiros para as possiveis ramificações quando a árvore for criada;
2. Lista: Armazena um nó do tipo "Codificacao" e dois ponteiros para o anterior e próximo da lista, criando uma lista duplamente encadeada;
3. Sentinela: Armazena o tamanho da lista e a "cabeça" e a "ponta" (head e tail), assim podendo acessar o início e final da lista a qualquer momento.

## Variável Global
- pontas: Variável do tipo "Sentinela" para ser utilizada para acessar o início e fim da lista.

## Funções
1. le_palavra: Abre um arquivo txt e chama a função "monta_lista" para inicar a codificação do texto do arquivo;
2. monta_lista: Cria a lista encadeada de caracteres do tipo "Lista", que armazena os dados de um nó. Para caracteres repetidos, usa a função "tem_letra" para verificar se já foi preenchida na lista. Caso retorne verdadeiro, chama a função "aumenta_freq" para aumentar a frequência do caractere conforme a quantidade de vezes que ele apareceu no texto;
3. tem_letra: Verifica se o caractere atual já está na lista e retorna verdadeiro (1) ou falso (0) caso não esteja;
4. aumenta_freq: Caso a função "tem_letra" seja verdadeiro, a função "monta_lista" chama esta função para aumentar a frequência do carctere na lista encadeada, simbolizando quantas vezes ele aparece no texto;
5. print_lista: Exibe no terminal a lista criada pela função "monta_lista";
6. ordena_freq: Ordena a lista encadeada com base na frequência dos caracteres, do menor para o maior, usando o BubbleSort com flag. Usa a função "troca_posi" para trocar a posição dos itens da lista. Caso a frequência dos caracteres seja igual, faz a ordenação pela ordem deles;
7. troca_posi: Troca a posição dos itens da lista, sobrescrevendo os dados dos ponteiros recebidos;
8. monta_arvore: Corta os dois primeiros itens da lista usando a função "guilhotina" e junta ambos em um nó do tipo "Lista", usando os ponteiros da struct "Codificacao" para armazenar no lado esquerdo ou direito do nó. Após criar o novo nó, reordena novamente a frequência;
9. guilhotina: Atualiza a variável global "pontas" atualizando seu primeiro valor para o próximo e armazenando ele em uma variável, assim cortando a cabeça da lista e retornando o valor antigo de pontas.head para a função "monta_arvore";
10. imprime_arvore: Após a criação completa da árvore, utilizando recursão ele imprime os galhos da árvore;
11. calc_altura: Calcula a altura da árvore, até o nó mais baixo, para otimizar a codificação, usando apenas o espaço necessário de memória;
12. aloca_codigo: Aloca memória para criar uma matriz do tipo char, para cada linha da matriz ser um código de um caractere;
13. escreve_codigo: Utilizando recursão escreve o código do caractere na matriz. Quando vai para o galho a esquerda adiciona um "0", quando vai para o galho a direita adiciona um "1" ao codigo do caractere, ao final salva tudo na linha correspondente da matriz, usando o ID do caractere (presente na struct Codificacao) para identificar em qual linha o código do caractere será salvo;
14. imprime_codigo: Imprime o código de cada caractere no terminal;
15. salva_codigo: Cria um arquivo txt para salvar o código dos caracteres, chama a função "escreve_no_arquivo" para escrever o código;
16. escreve_no_arquivo: Utiliza recursão para escrever a palavra do arquivo txt original, dessa vez substituindo os caracteres pelo código correspondente de cada um;
17. decodifcar: Abre o arquivo txt com o texto codificado para decodificá-lo usando um loop while até o final do arquivo. No loop cada caractere é lido e comparado com o código do sistema através da função "busca_id_letra", caso não enconre é lido o próximo caractere, assim até encontrar um código de caractere;
18. busca_id_letra: Percorre a matriz do código pelas linhas, comparando o código recebido até o momento com cada código escrito na matriz, caso seja igual retorna o número da linha para escrever o caractere deste ID no texto;
19. cria_decode: Utilizando recursão a função corre até os galhos da árvore procurando o caractere com ID correspondete para escrever no arquivo.

## Main
Na função main é onde ficarão salvos informações essenciais, como as variáveis do tipo int "total_caracter" e "altura" e, do tipo char** a varíavel "codigo".
- total_caracter: Armazena o total de caracteres do texto para utilizar em outras funções como: aloca_codigo, imprime_codigo e decodificar;
- altura: Armazena a altura da árvore para ser utilizada em funções como: aloca_codigo, escreve_codigo e decofificar;
- codigo: Matriz onde é armazenado o código de cada caractere do texto.

Além das variáveis a função main também é responsável por chamar as funções para realizar a codificação e decodificação do texto, sendo separada por seções, são elas:
- "Leitura do arquivo e criação da lista": Chama a função "le_palavra" para inciar a codificação salvando os caracteres e suas frequências em uma lista;
- "Ordena a lista por frequência": Ordena por frequência e ordem dos caracteres a lista inicial;
- "Cria a árvore": Cria a árvore cortando de dois em dois os primeiros itens da lista, armazenando-os em "galhos";
- "Codifica os caracteres e salva no arquivo": seção onde é realizada a codificação do texto e criação do arquivo "codificado.txt";
- "Decodifca o código e cria a lista decodificada": por último a seção onde é realizada a decodificação do arquivo "codificado.txt" e criado o arquivo "decodificado.txt" com o texto decodificado.

## Como Usar?
main.c: Para o código funcionar, devem ser substituídos todos os caminhos de arquivo utilizados na função "fopen". No código as funções "fopen" estão com um caminho "/path/to/arquivo.txt", substitua em todas as chamdas da função "fopen" o texto "/path/to" com o caminho no sistema onde devem ser lidos ou escritos os arquivos txt.

amostra.txt: Para a codificação e decodificação funcionarem corretamente, o arquivo obrigatoriamente deve conter na primeira linha a quantidade total de caracteres do texto, incluindo espaço e caracteres especiais seguido de um quebra linha. Nas linhas seguintes ficará o texto do arquivo.
```
Exemplo:
25
Este é um exemplo de texto.
```