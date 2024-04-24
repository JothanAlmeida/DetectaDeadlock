/**
 * @file main.c
 * @author Ailton José Brandão Junior
 * @author Pedro Antônio Ferreira Sant' Ana
 * @author Jothan Rodrigues de Almeida
 * @brief
 * @version 0.1
 * @date 2022-08-12
 *
 * @copyright Copyright (c) 2022
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "thread.h"
#include "string.h"
#include "multiplasInstancias.h"

#define stringInicioThread "thread \0"       /*< Parte da string de criação de uma thread*/
#define stringSolicitaRecurso "p \0"         /*< Parte da string de solicitação de recurso */
#define stringLiberaRecurso "v \0"           /*< Parte da string de liberação de recurso */

/**
*    Essa função é responsável por verificar as operações nas
*    linhas e classificá-las em:
*        1  = Cria thread nova;
*        2  = Solicitar recurso;
*        3  = Liberar recurso;
*        -1 = OperacaoInvalida.
*/

char* verificaOperacao(char *linha, int *operacao){
    char *retorno = NULL;

    retorno = estaContida(stringInicioThread, linha);
    if(retorno){
        *operacao = 1;  /* A operação é de criar thread */
        return retorno;
    }

    retorno = estaContida(stringSolicitaRecurso, linha);
    if(retorno){
        *operacao = 2; /* A operação é de solicitação de recurso */
        return retorno;
    }

    retorno = estaContida(stringLiberaRecurso, linha);
    if(retorno){
        *operacao = 3; /* A operação é de liberação de recurso */
        return retorno;
    }

    *operacao = -1;   /* A operação é inválida */
    return retorno;
}

/**
*    Essa função é responsável por preencher o vetor de disponíveis.
*    A primeira linha do arquivo representa a quantiade de recursos disponíveis,
*    essa função recebe a leitura da linha e aloca em um vetor a quantidade de recursos
*    que são especificados.
*/
int* preencheDisponivel(char *linha, int *lenDisponivel){
    char *numero = NULL;
    int contador = 0, *disponivel = NULL, lenNumero = 0; /*Contador armazena a quantidade de recursos diferentes*/

    *lenDisponivel = 0;
    while(1){
        numero = realloc(numero, (lenNumero + 1) * sizeof(char));

        if(linha[contador] != ' ' && linha[contador] != '\0'){
            numero[lenNumero] = linha[contador];
            lenNumero++;
        }else{
            numero[lenNumero] = '\0';
            disponivel = expandirVetor(disponivel, strtol(numero, NULL, 10), lenDisponivel);
            free(numero);
            numero = NULL;
            lenNumero = 0;

            if(linha[contador] == '\0')
                break;
        }
        contador++;
    }

    return disponivel; /* Retorna o vetor alocado com os recursos disponíveis */
}

/**
*    Função responsável por executar as operações realizadas por cada thread.
*    Em caso de números superiores a zero (positivos), representam a solicitação de um recurso.
*    Caso contrário (negativos), representam a liberação de um recurso.
*/

MultiplasInstancias* executaOperacao(MultiplasInstancias *m, int linhaExecucao, int processo, Thread *thread, int *deadlock, int *executou){
    if(linhaExecucao >= thread->quantidadeLinhas)
        return m;

    if(thread->operacoes[0][linhaExecucao] > 0){ /* A thread está solicitando recurso */

        int solicitacao[m->quantRecursos];

        for(int i = 0; i < m->quantRecursos; i++)
            solicitacao[i] = 0;

        solicitacao[thread->operacoes[0][linhaExecucao] - 1] = 1;

        return solicitaRecurso(m, processo, solicitacao, deadlock, executou);
    }
    else   /*A thread está liberando recurso*/
    {
        *executou = 1;
        return desalocaRecurso(m, processo, -1*(thread->operacoes[0][linhaExecucao] + 1));
    }
}

/**
*    Em caso de deadlock, esta função é responsável por imprimir a saída como requerida.
*    Imprime cada passo, por sua vez, com o nome de uma thread e o comando que ela
*    executou (incluindo todos os caracteres de tabulação que o precederem em sua linha),
*    separados por um caracter dois pontos (“:”).
*/
void geraSaida(Thread **threads, int *vetorPermutacao, int *linhaExecucao, int quantThreads){
    int *vetorAux = calloc(quantThreads, sizeof(int)); /* Vetor responsável por garantir a impressão de somente os processos
                                                          que ocasionaram o deadlock */

    while(!igual(vetorAux, linhaExecucao, quantThreads)){
        for(int i = 0; i < quantThreads; i++){

            if(vetorAux[i] < linhaExecucao[i]){
                for(int j = 0; j < vetorPermutacao[i]; j++){

                    printf("%s:", threads[i]->nome); /*Imprime o nome da thread*/

                    for(int l = 0; l < threads[i]->identacao[0][vetorAux[i]]; l++)
                        printf("\t");                                               /*Identação*/

                    if(threads[i]->operacoes[0][vetorAux[i]] > 0)
                        printf("p %i\n", threads[i]->operacoes[0][vetorAux[i]] - 1); /* Imprime quando a operação é de solicitação */
                    else
                        printf("v %i\n", (-1*threads[i]->operacoes[0][vetorAux[i]]) - 1); /* Imprime quando a operação é de liberação */

                    vetorAux[i]++;

                    if(vetorAux[i] == linhaExecucao[i])
                        break;
                }
            }
        }
    }
    free(vetorAux);
}
/**
*    Função responsável por identificar o momento do deadlock, se ocorrer,
*    e quais processos participaram para tal.
*/
void testaDeadlock(int *disponiveis, int quantThread, int lenDisponiveis, int maximoLinhas, Thread **threads){
    int vetorPermutacao[quantThread], *linhaExecucao = NULL, *vetorNulo = calloc(quantThread, sizeof(int)), deadlock = 0, executou = 1;
    MultiplasInstancias *m = NULL;

    for(int i = 0; i < quantThread; i++)
        vetorPermutacao[i] = 1;

    vetorPermutacao[quantThread-1] = 0;  /* Vetor responsável por gerar todas as permutações na
                                            matriz de modo a verificar todas as possibilidades possíveis */

    while(menorQueConstante(vetorPermutacao, quantThread, maximoLinhas) && !deadlock){

        if(m)
            desalocaMultiplasInstancias(m); /* Libera o vetor m de multiplas instancias */

        m = incializaMultiplasInstancias(disponiveis, lenDisponiveis); /*Inicializa o vetor de multiplas instancias */

        for(int i = 0; i < quantThread; i++)
            m = inserirProcesso(m);

        incrementaVetor(vetorPermutacao, quantThread, maximoLinhas); /* Incrementa o vetor em 1 unidade */

        if(linhaExecucao){         /*Zera o vetor de linha de execução */
            free(linhaExecucao);
            linhaExecucao = NULL;
        }
        linhaExecucao = copiaVetor(vetorNulo, quantThread);

        int contador = 0;
        while(!deadlock){
            for(int i = 0; i < quantThread; i++){ /*Executa as intruções de todas as threadas*/

                for(int j = 0; j < vetorPermutacao[i]; j++){
                    if(!menorQueConstante(linhaExecucao, quantThread, maximoLinhas)) /* Acabou a execução */
                        break;

                    m = executaOperacao(m, linhaExecucao[i], i, threads[i], &deadlock, &executou);

                    if(executou == 1)
                        linhaExecucao[i]++;
                    else
                        break;

                    if(deadlock){
                        break;
                    }
                }
                contador++;

                if(deadlock)
                    break;
            }
            if(!menorQueConstante(linhaExecucao, quantThread, maximoLinhas)) /* Acabou a execução */
                break;
        }
    }
    if(deadlock){
        geraSaida(threads, vetorPermutacao, linhaExecucao, quantThread); /* Imprime a saída como solicitado*/
    }else
        printf("programa livre de impasses.\n");

    if(linhaExecucao)
        free(linhaExecucao);

    desalocaMultiplasInstancias(m);

    free(vetorNulo);
}

int main(){

    /* Declaração das variávies */
    char *linha = NULL, *retorno = NULL;
    int quantThreads = 0, quantidadeMaximaLinhas = 0, operacao = 0, *disponiveis = NULL, lenDisponiveis = 0
    ,*vetorOperacoes = NULL, identacao = 0, recursoInt = 0, eof = 0, *vetorIdentacao = NULL;
    Thread **threads = NULL;

    do{
        identacao = 0;
        linha = leLinha(&identacao, &eof);

        retorno = verificaOperacao(linha, &operacao); /* verificando qual operação foi solicitada */
        if(operacao == 1){                            /* Inicialização de nova thread */
            if(quantThreads > 0){
                threads[quantThreads-1]->operacoes = expandirMatriz(threads[quantThreads-1]->operacoes, vetorOperacoes, 0, threads[quantThreads-1]->quantidadeLinhas);
                free(vetorOperacoes);
                vetorOperacoes = NULL;

                threads[quantThreads-1]->identacao = expandirMatriz(threads[quantThreads-1]->identacao, vetorIdentacao, 0, threads[quantThreads-1]->quantidadeLinhas);
                free(vetorIdentacao);
                vetorIdentacao = NULL;

                /* Definindo a maior quantidade de linhas de uma thread */
                if(threads[quantThreads-1]->quantidadeLinhas > quantidadeMaximaLinhas)
                    quantidadeMaximaLinhas = threads[quantThreads-1]->quantidadeLinhas;
            }

            /* Inicializando as variáveis da nova thread */
            threads = realloc(threads, (quantThreads + 1) * sizeof(Thread*));
            threads[quantThreads] = criaThread(retorno);
            quantThreads++;

        }else if(operacao == 2){        /* A thread (quantThread-1) solicita recurso */

            recursoInt = (int)strtol(retorno, NULL, 10); /* Identifica o recurso solicitado */

            /* Abaixo é alocado ao vetor de operações qual é o recurso solicitado e por qual thread está sendo feita*/
            vetorOperacoes = expandirVetor(vetorOperacoes, (recursoInt + 1), &threads[quantThreads-1]->quantidadeLinhas);
            threads[quantThreads-1]->quantidadeLinhas--;
            vetorIdentacao = expandirVetor(vetorIdentacao, identacao, &threads[quantThreads-1]->quantidadeLinhas);

            free(retorno);
            retorno = NULL;

        }else if(operacao == 3){       /* A thread (quantThread-1) libera recurso */

            recursoInt = (int)strtol(retorno, NULL, 10); /* Identifica o recurso liberado */

            /* Abaixo é alocado ao vetor de operações qual o recurso liberado e por qual thread */
            vetorOperacoes = expandirVetor(vetorOperacoes, -1*(recursoInt + 1), &threads[quantThreads-1]->quantidadeLinhas);
            threads[quantThreads-1]->quantidadeLinhas--;
            vetorIdentacao = expandirVetor(vetorIdentacao, identacao, &threads[quantThreads-1]->quantidadeLinhas);

            free(retorno);

            retorno = NULL;

        }else if(quantThreads == 0){     /* primeira linha do arquivo, inicializando o vetor de disponíveis */
            disponiveis = preencheDisponivel(linha, &lenDisponiveis);
        }

        if(eof == -1){          /* Para encerrar o laço */
            threads[quantThreads-1]->operacoes = expandirMatriz(threads[quantThreads-1]->operacoes, vetorOperacoes, 0, threads[quantThreads-1]->quantidadeLinhas);
            free(vetorOperacoes);
            vetorOperacoes = NULL;
            threads[quantThreads-1]->identacao = expandirMatriz(threads[quantThreads-1]->identacao, vetorIdentacao, 0, threads[quantThreads-1]->quantidadeLinhas);
            free(vetorIdentacao);
            vetorIdentacao = NULL;

            /* Definindo a maior quantidade de linhas de uma thread */
            if(threads[quantThreads-1]->quantidadeLinhas > quantidadeMaximaLinhas)
                quantidadeMaximaLinhas = threads[quantThreads-1]->quantidadeLinhas;
        }

        free(linha);
        linha = NULL;
    }while(eof != -1);

    /* É chamada a função para verificar se há possibilidade de deadlock. */
    testaDeadlock(disponiveis, quantThreads, lenDisponiveis, quantidadeMaximaLinhas, threads);

    /* Desalocando memória */
     for(int i = 0; i < quantThreads; i++)
        desalocaThread(threads[i]);

    free(threads);
    free(disponiveis);

    return 0;
}