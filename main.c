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
void le_palavra();
void monta_lista(FILE *p, int total_caracteres);
int tem_letra(char c);
void aumenta_freq(char c);
void print_lista();
void ordena_freq();
void troca_posi(Codificacao *maior, Codificacao *menor);
void monta_arvore();
Codificacao *guilhotina();
void imprime_arvore(Codificacao *no, int altura);

// Função main:
int main(){

    le_palavra();

    ordena_freq();

    monta_arvore();

    return 0;
}

// Funções:
void le_palavra(){
    FILE *fp;
    int total_caracteres;

    fp = fopen("/home/joaobettu/Documentos/UFFS/2024-2/POD/TF/amostra.txt", "r");
    if(fp==NULL){
        printf("Não foi possível abrir o arquivo!\n");
        exit(1);
    }

    fscanf(fp, "%d\n", &total_caracteres);
    monta_lista(fp, total_caracteres);

    fclose(fp);
}
void monta_lista(FILE *p, int total_caracteres){
    char c;
	Lista *novo_no;

    pontas.head = NULL;
    pontas.tail = NULL;
    pontas.tamanho = 0;

    for(int i = 0; i < total_caracteres; i++){
        c = fgetc(p);
        if(tem_letra(c)){
			aumenta_freq(c);
        }else{
			novo_no = (Lista *)malloc(sizeof(Lista));
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

	for(aux = pontas.head; aux!=NULL; aux = aux->next){
		printf("Letra: %c\nFrequência: %d\n", aux->node.caractere, aux->node.freq);
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
		}
		if(houve_troca == 0){
			break;
		}
	}

    printf("\nOrdenado:\n");
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
        printf("\n\tLetra: %c\n\tFrequencia: %d\n\tTamanho: %d\n", raiz->caractere, raiz->freq, altura);
    }else{
        imprime_arvore(raiz->esquerda, altura + 1);
        imprime_arvore(raiz->direita, altura + 1);
    }
}