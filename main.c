/*
    João Victor Bettu
    20230003744
    -- Codificação de Huffman --
*/

// Bibliotecas:
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structs:
typedef struct arvore{
    int id;
    char caractere;
    int freq;
    struct arvore *esquerda, *direita;
} Codificacao;

typedef struct floresta{
    Codificacao node;
    struct floresta *next, *prev;
} Lista;

typedef struct mudas{
    int tamanho;
    Lista *head, *tail;
} Sentinela;

// Varáveis globais:
Sentinela pontas;

// Assinatura das funções:
int le_palavra();
void monta_lista(FILE *p, int total_caracteres);
int tem_letra(char c);
void aumenta_freq(char c);
void print_lista();
void ordena_freq();
void troca_posi(Codificacao *maior, Codificacao *menor);
void monta_arvore();
Codificacao *guilhotina();
void imprime_arvore(Codificacao *raiz, int altura);
int calc_altura(Codificacao *no);
char** aloca_codigo(int colunas, int tamanho);
void escreve_codigo(char **codigo, Codificacao *raiz, char *caminho, int colunas);
void imprime_codigo(char **codigo, int tamanho);
void salva_codigo(char **codigo);
void escreve_no_arquivo(Codificacao *raiz, char letra, char **codigo, FILE *arquivo);
void decodificar(int tam_str, char **codigo, int tam_code);
int busca_id_letra(char *str, char **codigo, int tam);
void cria_decode(int id, Codificacao *no, FILE *pointer);

// Função main:
int main(){
    int total_caracter, altura;
    char** codigo;

    // Leitura do arquivo e criação da lista
    printf("    -- Codificação de Huffman --\n");
    printf("Lista:");
    total_caracter = le_palavra();
    printf("--------------------------------\n");
    
    // Ordena a lista por frequência
    printf("Lista ordenada:");
    ordena_freq();
    printf("--------------------------------\n");

    // Cria a árvore
    printf("Arvore:");
    monta_arvore();
    printf("--------------------------------\n");
    
    // Codifica os caracteres e salva no arquivo
    printf("Codificação:");
    altura = calc_altura(&pontas.head->node) + 1;
    codigo = aloca_codigo(altura, total_caracter);
    printf("\n");
    escreve_codigo(codigo, &pontas.head->node, "", altura);
    imprime_codigo(codigo, total_caracter);
    salva_codigo(codigo);
    printf("--------------------------------\n");

    // Decodifca o código e cria a lista decodificada
    printf("Descodifcação\n");
    decodificar(total_caracter, codigo, altura);
    printf("--------------------------------\n");

    return 0;
}

// Funções:
int le_palavra(){
    FILE *fp;
    int total_caracteres;

    fp = fopen("/path/to/amostra.txt", "r");
    if(fp==NULL){
        printf("Não foi possível abrir o arquivo!\n");
        exit(1);
    }

    fscanf(fp, "%d\n", &total_caracteres);
    monta_lista(fp, total_caracteres);

    fclose(fp);

    return total_caracteres;
}
void monta_lista(FILE *p, int total_caracteres){
    char c;
	Lista *novo_no;
    int contador = 0;

    pontas.head = NULL;
    pontas.tail = NULL;
    pontas.tamanho = 0;

    for(int i = 0; i < total_caracteres; i++){
        c = fgetc(p);
        if(tem_letra(c)){
			aumenta_freq(c);
        }else{
            novo_no = (Lista *)malloc(sizeof(Lista));
            novo_no->node.id = contador;
            contador++;
			novo_no->node.caractere = c;
			novo_no->node.freq = 1;
			novo_no->node.direita = NULL;
            novo_no->node.esquerda = NULL;
			novo_no->next = NULL;
            novo_no->prev = NULL;
			if(pontas.head == NULL){
				pontas.head = novo_no;
                pontas.tail = novo_no;
                pontas.tamanho++;
			}else{
				novo_no->prev = pontas.tail;
                pontas.tail->next = novo_no;
                pontas.tail = novo_no;
                pontas.tamanho++;
			}
        }
    }
    print_lista();
}
int tem_letra(char c){
    Lista *aux;

	for(aux = pontas.head; aux!=NULL; aux = aux->next){
		if(c == aux->node.caractere){
			return 1;
		}
	}

    return 0;
}
void aumenta_freq(char c){
    Lista *aux;

	if(pontas.head==NULL){
		printf("Lista vazia!\n");
		exit(1);
	}

	for(aux = pontas.head; aux!=NULL; aux = aux->next){
		if(aux->node.caractere == c){
			aux->node.freq++;
		}
	}
}
void print_lista(){
    Lista *aux;
    printf("\n");
	for(aux = pontas.head; aux!=NULL; aux = aux->next){
		printf("\tLetra: %c\n\tFrequência: %d\n", aux->node.caractere, aux->node.freq);
	}
}
void ordena_freq(){
    // Bubble sort
    Lista *aux, *robin;

	for(aux = pontas.tail; aux!=NULL; aux = aux->prev){
		int houve_troca = 0;
		for(robin = pontas.head; robin!=aux; robin = robin->next){
            if(robin->node.freq > robin->next->node.freq){
                troca_posi(&robin->node, &robin->next->node);
                houve_troca = 1;
            }
            if(robin->node.freq == robin->next->node.freq){
                if(robin->node.caractere > robin->next->node.caractere){
                    troca_posi(&robin->node, &robin->next->node);
                    houve_troca = 1;
                }
            }
		}
		if(houve_troca == 0){
			break;
		}
	}

    print_lista();
}
void troca_posi(Codificacao *maior, Codificacao *menor){
    Codificacao troca = *maior;

    *maior = *menor;
    *menor = troca;
}
void monta_arvore(){
    Codificacao *primeiro = NULL, *segundo = NULL;
    Lista *novo;

    while(pontas.tamanho > 1){
        primeiro = guilhotina();
        segundo = guilhotina();

        novo = (Lista *)malloc(sizeof(Lista));

        int frequencia = primeiro->freq + segundo->freq;

        novo->node.freq = frequencia;
        novo->node.caractere = '+';
        novo->node.esquerda = primeiro;
        novo->node.direita = segundo;
        novo->next = NULL;
        novo->prev = NULL;
        if(pontas.head == NULL){
            pontas.head = novo;
            pontas.tail = novo;
            pontas.tamanho++;
        }else{
            pontas.tail->next = novo;
            novo->prev = pontas.tail;
            pontas.tail = novo;
            pontas.tamanho++;
        }
        ordena_freq();
    }
    printf("\n");
    imprime_arvore(&pontas.head->node, 0);
}
Codificacao *guilhotina(){
    Lista *aux;

    if(pontas.head == NULL){
        exit(1);
    }

    if(pontas.head->next == NULL){
        aux = pontas.head;
        pontas.head = NULL;
        pontas.tamanho--;
        return &aux->node;
    }
    aux = pontas.head;
    pontas.head = pontas.head->next;
    pontas.head->prev = NULL;
    pontas.tamanho--;

    return &aux->node;
}
void imprime_arvore(Codificacao *raiz, int altura){
    if(raiz->direita == NULL && raiz->esquerda == NULL){
        printf("\tLetra: %3c -> Frequencia: %3d -> Altura: %3d\n", raiz->caractere, raiz->freq, altura);
    }else{
        imprime_arvore(raiz->esquerda, altura + 1);
        imprime_arvore(raiz->direita, altura + 1);
    }
}
int calc_altura(Codificacao *no){
    int esq, dir;

    if(no == NULL)
        return -1;
    else{
        esq = calc_altura(no->esquerda) + 1;
        dir = calc_altura(no->direita) + 1;

        if(esq > dir){
            return esq;
        }else{
            return dir;
        }
    }
}
char** aloca_codigo(int colunas, int tamanho){
    char** codigo;

    codigo = malloc(sizeof(char*) * tamanho);

    for(int i = 0; i < tamanho; i++)
        codigo[i] = calloc(colunas, sizeof(char));

    return codigo;
}
void escreve_codigo(char **codigo, Codificacao *raiz, char *caminho, int colunas){
    char esquerda[colunas], direita[colunas];

    if(raiz->esquerda == NULL && raiz->direita == NULL){
        strcpy(codigo[raiz->id], caminho);
        printf("\tRaiz %3d: %3c -> %s\n", raiz->id, raiz->caractere, caminho);
    }else{
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        strcat(esquerda, "0");
        strcat(direita, "1");

        escreve_codigo(codigo, raiz->esquerda, esquerda, colunas);
        escreve_codigo(codigo, raiz->direita, direita, colunas);
    }
}
void imprime_codigo(char **codigo, int tamanho){
    printf("\n");
    for(int i = 0; i < tamanho; i++){
        if(strlen(codigo[i])>0)
            printf("\t%3d: %s\n", i, codigo[i]);
    }
}
void salva_codigo(char **codigo){
    FILE *codif, *amostra;
    int tamanho;
    char letra;

    codif = fopen("/path/to/codificado.txt", "w");
    if(codif == NULL){
        printf("Erro ao criar codificado!\n");
        exit(1);
    }

    amostra = fopen("/path/to/amostra.txt", "r");
    if(amostra == NULL){
        printf("Erro ao abrir amostra!\n");
        exit(1);
    }

    fscanf(amostra, "%d\n", &tamanho);

    for(int i = 0; i < tamanho + 1; i++){
        letra = fgetc(amostra);
        escreve_no_arquivo(&pontas.head->node, letra, codigo, codif);
    }

    fclose(codif);
    fclose(amostra);
}
void escreve_no_arquivo(Codificacao *raiz, char letra, char **codigo, FILE *arquivo){
    if(raiz->esquerda == NULL && raiz->direita == NULL){
        if(raiz->caractere == letra){
            fprintf(arquivo, "%s", codigo[raiz->id]);
        }
    }else{
        escreve_no_arquivo(raiz->esquerda, letra, codigo, arquivo);
        escreve_no_arquivo(raiz->direita, letra, codigo, arquivo);
    }
}
void decodificar(int tam_str, char **codigo, int tam_code){
    FILE *codificado, *decodifica;
    int id;

    codificado = fopen("/path/to/codificado.txt", "r");
    if(codificado == NULL){
        printf("Erro ao abrir arquivo codificação!\n");
        exit(1);
    }

    decodifica = fopen("/path/to/decodificado.txt", "w");
    if(decodifica == NULL){
        printf("Erro ao criar decode!\n");
        exit(1);
    }

    while(!feof(codificado)){
        char *code;
        code = calloc(tam_code, sizeof(char));
        for(int i = 0; i < tam_code + 1; i++){
            code[i] = fgetc(codificado);
            id = busca_id_letra(code, codigo, tam_str);
            if(id>=0){
                cria_decode(id, &pontas.head->node, decodifica);
                break;
            }
        }
    }

    fclose(decodifica);
    fclose(codificado);
}
int busca_id_letra(char *str, char **codigo, int tam){
    for(int i = 0; i < tam; i++){
        if(strcmp(str, codigo[i])==0){
            return i;
        }
    }
    return -1;
}
void cria_decode(int id, Codificacao *no, FILE *pointer){
    if(no->esquerda == NULL && no->direita == NULL){
        if(no->id == id)
            fprintf(pointer, "%c", no->caractere);
    }else{
        cria_decode(id, no->esquerda, pointer);
        cria_decode(id, no->direita, pointer);
    }
}
