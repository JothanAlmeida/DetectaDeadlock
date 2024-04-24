#include <stdio.h>
#include <stdlib.h>


int* copiaVetor(int *vet, int len){
    if(!vet)
        return NULL;

    int *copia = malloc(len * sizeof(int));

    for(int i = 0; i < len; i++)
        copia[i] = vet[i];

    return copia;
}

int** copiaMatriz(int **m, int quantLinhas, int quantColunas){
    if(!m)
        return NULL;

    int **copia = malloc(quantLinhas * sizeof(int*));

    for(int i = 0; i < quantLinhas; i++)
        copia[i] = copiaVetor(m[i], quantColunas);

    return copia;

}

int* subtracaoVetores(int *vet1, int *vet2, int len){
    if(!vet1)
        return NULL;

    int *newVet = malloc(len * sizeof(int));

    for(int i = 0; i < len; i++)
        newVet[i] = vet1[i] - vet2[i];

    return newVet;
}

/*
    Verifica se todos os elementos do vetor1 são menores ou iguais aos do vetor 2.
    Caso sejam, retorna 1. Caso não sejam, retorna 0.
*/
int menorIgual(int *vet1, int *vet2, int len){
    if(!vet1)
        return 0;

    for(int i = 0; i < len; i++){
        if(vet1[i] > vet2[i])
            return 0;
    }


    return 1;
}

int igual(int *vet1, int *vet2, int len){
    if(!vet1)
        return 0;

    for(int i = 0; i < len; i++){
        if(vet1[i] != vet2[i])
            return 0;
    }


    return 1;
}

int* somaVetores(int *vet1, int *vet2, int len){
    if(!vet1)
        return NULL;

    int *newVet = malloc(len * sizeof(int));

    for(int i = 0; i < len; i++)
        newVet[i] = vet1[i] + vet2[i];

    return newVet;
}

/*
    Insere o vetor na posição final da matriz m
*/
int** expandirMatriz(int **m, int *vetor, int posicaoInsercao, int lenVet){

    if(!m)
        m = malloc(sizeof(int*));

    m = realloc(m, (posicaoInsercao + 1) * sizeof(int*));

    m[posicaoInsercao] = malloc(lenVet * sizeof(int));

    for(int i = 0; i < lenVet; i++)
        m[posicaoInsercao][i] = vetor[i];

    return m;

}

int *expandirVetor(int *v, int valor, int *lenVet){
    if(!v)
        v = malloc(sizeof(int));

    v = realloc(v, (*lenVet + 1) * sizeof(int));
    v[*lenVet] = valor;
    (*lenVet)++;

    return v;
}


void imprimeVetor(int *vet, int tamanho){
    if(vet == NULL)
        return;
    printf("/ ");

    for(int i = 0; i < tamanho; i++)
        printf("%i ", vet[i]);

    printf("/\n");

}

void imprimeMatriz(int **m, int linhas, int colunas){
    if(m == NULL)
        return;

    for(int i = 0; i < linhas; i++)
        imprimeVetor(m[i], colunas);
}


int ehNulo(int *v, int len){
    for(int i = 0; i < len; i++){
        if(v[i] != 0)
            return 0;
    }

    return 1;
}

/*
    Retorna 1 se algum valor de v for menor que a constante.
*/
int menorQueConstante(int *vetor, int lenV, int constante){
    for(int i = 0; i < lenV; i++)
		if(vetor[i] < constante)
			return 1;
	return 0;
}


void incrementaVetor(int *vetor, int len, int max){
	int contador = len-1;

	while(vetor[contador] == max){
		vetor[contador] = 1;
		contador--;

    }

    vetor[contador]++;
}
