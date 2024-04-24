#ifndef __VECTOR_H
#define __VECTOR_H

//!Cria e retorna um ponteiro para cópia do vetor passado como parâmetro.
int* copiaVetor(int *vet, int len);

//!Cria e retorna um ponteiro para cópia da matriz passada como parâmetro.
int** copiaMatriz(int **m, int quantLinhas, int quantColunas);

//!Realoca a matriz passada como parâmetro adicionando ao final da mesma um vetor passado como parâmetro.
int** expandirMatriz(int **m, int *vetor, int posicaoInsercao, int lenVet);

//!Realoca o vetor passado como parâmetro adicionando o inteiro ao final do mesmo.
int *expandirVetor(int *v, int valor, int *lenVet);

//! Retorna um ponteiro para o vetor resultado entre a subtração do vet1 e vet2.
int* subtracaoVetores(int *vet1, int *vet2, int len);

//! Retorna um ponteiro para o vetor resultado entre a soma do vet1 e vet2.
int* somaVetores(int *vet1, int *vet2, int len);

//! Verifica se todos os elementos do vetor1 são menores ou iguais aos do vetor 2. Caso sejam, retorna 1. Caso não sejam, retorna 0.
int menorIgual(int *vet1, int *vet2, int len);

//! Verifica se todos os elementos do vetor1 são iguais aos do vetor 2. Caso sejam, retorna 1. Caso não sejam, retorna 0.
int igual(int *vet1, int *vet2, int len);

//! Verifica se todos os elementos do vetor v são iguais a 0. Caso sejam, retorna 1, caso não sejam, retorna 0.
int ehNulo(int *v, int len);

//! Função auxiliar que realiza o incremento de cada posição do vetor até o max.
void incrementaVetor(int *vetor, int len, int max);

//! Retorna 1 se algum valor de v for menor que a constante.
int menorQueConstante(int *v, int lenV, int constante);

#endif