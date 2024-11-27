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
    struct floresta *next;
} Lista;

// Varáveis globais:
int total_caracteres;
Codificacao *vetor_caracteres;
Lista *FIRST = NULL;

// Assinatura das funções:
void le_palavra();
void monta_lista(FILE *p);
int tem_letra(char c);
void aumenta_freq(char c);
void ordena_freq();
void troca_posi(Lista *maior, Lista *menor);
void monta_arvore();
void null_folhas(Codificacao *galho);
void print_lista();

// Função main:
int main(){

    le_palavra();

    ordena_freq();

    //monta_arvore();

    return 0;
}

// Funções:
void le_palavra(){
    FILE *fp;

    fp = fopen("/home/joaobettu/Documentos/UFFS/2024-2/POD/TF/amostra.txt", "r");
    if(fp==NULL){
        printf("Não foi possível abrir o arquivo!\n");
        exit(1);
    }

    fscanf(fp, "%d\n", &total_caracteres);
    monta_lista(fp);

    fclose(fp);
}
void monta_lista(FILE *p){
    char c;
	Lista *novo_no, *aux;

    //vetor_caracteres = (Codificacao *)malloc(sizeof(Codificacao) * total_caracteres);

    for(int i = 0; i < total_caracteres; i++){
        c = fgetc(p);
        /*if(tem_letra(c)){
            aumenta_freq(c);
        }else{
            vetor_caracteres[i].caractere = c;
            vetor_caracteres[i].freq = 1;
            null_folhas(&vetor_caracteres[i]);
        }*/
        if(tem_letra(c)){
			aumenta_freq(c);
        }else{
			novo_no = (Lista *)malloc(sizeof(Lista));
			novo_no->node.caractere = c;
			novo_no->node.freq = 1;
			null_folhas(&novo_no->node);
			novo_no->next = NULL;
			if(FIRST == NULL){
				FIRST = novo_no;
				aux = novo_no;
			}else{
				aux->next = novo_no;
				aux = novo_no;
			}
        }
    }
    print_lista();
}
int tem_letra(char c){
    /*for(int i = 0; i < total_caracteres; i++){
        if(c == vetor_caracteres[i].caractere){
            return 1;
        }
    }*/
    Lista *aux;

	for(aux = FIRST; aux!=NULL; aux = aux->next){
		if(c == aux->node.caractere){
			return 1;
		}
	}

    return 0;
}
void aumenta_freq(char c){

    /*for(int i = 0; i < total_caracteres; i++){
        if(vetor_caracteres[i].caractere == c){
            vetor_caracteres[i].freq++;
        }
    }*/

   	Lista *aux;

	if(FIRST==NULL){
		printf("Lista vazia!\n");
		exit(1);
	}

	for(aux = FIRST; aux!=NULL; aux = aux->next){
		if(aux->node.caractere == c){
			aux->node.freq++;
		}
	}
}
void ordena_freq(){
    // Bubble sort
    /*for(int i = 0; i < total_caracteres; i++){
        int houve_troca = 0;
        for(int j = i + 1; j < total_caracteres; j++){
            if(vetor_caracteres[i].freq == 0){
                troca_posi(&vetor_caracteres[j], &vetor_caracteres[i]);
                houve_troca++;
                continue;
            }
            if(vetor_caracteres[i].freq > vetor_caracteres[j].freq){
                if(vetor_caracteres[j].freq == 0){
                    continue;
                }
                troca_posi(&vetor_caracteres[i], &vetor_caracteres[j]);
                houve_troca++;
            }
        }
        if(houve_troca == 0){
            break;       
        }
    }*/

    Lista *aux, *robin;

	for(aux = FIRST; aux!=NULL; aux = aux->next){
		int houve_troca = 0;
		for(robin = aux->next; robin!=NULL; robin = robin->next){
			if(aux->node.freq > robin->node.freq){
				troca_posi(aux, robin);
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
void troca_posi(Lista *maior, Lista *menor){
    Lista troca = *maior;

    *maior = *menor;
    *menor = troca;
	printf("Saiu\n");
}
void monta_arvore(){
    Codificacao ramo;

    for(int i = 0; i < total_caracteres; i++){
        if(vetor_caracteres[i].freq == 0){
            break;
        }
        ramo.freq = vetor_caracteres[i].freq + vetor_caracteres[i+1].freq;
        printf("\nRamo freq: %d\n", ramo.freq);
        ramo.caractere = ramo.freq;
        printf("Ramo caracter: %c\n", ramo.caractere);
        ramo.esquerda = &vetor_caracteres[i];
        ramo.direita = &vetor_caracteres[i+1];
        for(int j = 0; j < total_caracteres; j++){
            if(vetor_caracteres[j].freq == 0){
                vetor_caracteres[j] = ramo;
            }
        }
    }
    printf("\nRamos:\n");
    //print_vetor();
}
void null_folhas(Codificacao *galho){
    galho->direita = NULL;
    galho->esquerda = NULL;
}
void print_lista(){
    /*for(int i = 0; i < total_caracteres; i++){
        printf("Letra: %c\nFrequência: %d\n", vetor_caracteres[i].caractere, vetor_caracteres[i].freq);
    }*/

    Lista *aux;

	for(aux = FIRST; aux!=NULL; aux = aux->next){
		printf("Letra: %c\nFrequência: %d\n", aux->node.caractere, aux->node.freq);
	}
}