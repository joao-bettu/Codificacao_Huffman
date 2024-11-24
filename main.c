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

// Varáveis globais:
int total_caracteres;
Codificacao *vetor_caracteres;

// Assinatura das funções:
void le_palavra();
void monta_vetor(FILE *p);
int tem_letra(char c);
void aumenta_freq(char c);
void ordena_freq();
void troca_posi(Codificacao *a, Codificacao *b);

// Função main:
int main(){

    le_palavra();

    ordena_freq();

    return 0;
}

// Funções:
void le_palavra(){
    FILE *fp;

    fp = fopen("/home/joaobettu/Documentos/UFFS/2024-2/POD/Codificacao_Huffman/amostra.txt", "r");
    if(fp==NULL){
        printf("Não foi possível abrir o arquivo!\n");
        exit(1);
    }

    fscanf(fp, "%d\n", &total_caracteres);
    monta_vetor(fp);

    fclose(fp);
}
void monta_vetor(FILE *p){
    char c;

    vetor_caracteres = (Codificacao *)malloc(sizeof(Codificacao) * total_caracteres);

    for(int i = 0; i < total_caracteres; i++){
        c = fgetc(p);
        if(tem_letra(c)){
            aumenta_freq(c);
        }else{
            vetor_caracteres[i].caractere = c;
            vetor_caracteres[i].freq = 1;
        }
    }
    for(int i = 0; i < total_caracteres; i++){
        printf("Letra: %c\nFrequência: %d\n", vetor_caracteres[i].caractere, vetor_caracteres[i].freq);
    }
}
int tem_letra(char c){
    for(int i = 0; i < total_caracteres; i++){
        if(c == vetor_caracteres[i].caractere){
            return 1;
        }
    }
    return 0;
}
void aumenta_freq(char c){

    for(int i = 0; i < total_caracteres; i++){
        if(vetor_caracteres[i].caractere == c){
            vetor_caracteres[i].freq++;
        }
    }
}
void ordena_freq(){
    // Bubble sort
    for(int i = 0; i < total_caracteres; i++){
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
    }
    printf("\nOrdenado:\n");
    for(int i = 0; i < total_caracteres; i++){
        printf("Letra: %c\nFrequência: %d\n", vetor_caracteres[i].caractere, vetor_caracteres[i].freq);
    }
}
void troca_posi(Codificacao *maior, Codificacao *menor){
    Codificacao troca = *maior;

    *maior = *menor;
    *menor = troca;
}