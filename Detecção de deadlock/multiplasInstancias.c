#include <stdio.h>
#include <stdlib.h>
#include "multiplasInstancias.h"

//! Função que aloca e inicializa a estrutura de MultiplasInstancias.
MultiplasInstancias *incializaMultiplasInstancias(int *disponivel, int lenDisponivel){
    MultiplasInstancias *m = (MultiplasInstancias*) malloc(sizeof(MultiplasInstancias));

    m->disponivel = malloc(lenDisponivel * sizeof(int));

    int *vetNulo = calloc(lenDisponivel, sizeof(int));
    m->solicitacao = NULL;
    for(int i = 0; i < (lenDisponivel); i++){
        m->disponivel[i] = disponivel[i];
        m->solicitacao = expandirMatriz(m->solicitacao, vetNulo, i, lenDisponivel);
    }

    free(vetNulo);

    m->alocacao = NULL;
    m->quantRecursos = lenDisponivel;
    m->quantProcessos = 0;

    return m;
}

//!Função que analisa as estruturas e conclui se o sistema está ou não em deadlock.
int verificaEstado(MultiplasInstancias *m){

    int *trabalho = copiaVetor(m->disponivel, m->quantRecursos); /* Cópia do vetor disponível */
    int *termino = calloc(m->quantProcessos, sizeof(int)); /* Vetor usado para indicar quais processos já foram encerrados. */

    for(int i = 0; i < m->quantProcessos; i++){
        if(ehNulo(m->alocacao[i], m->quantRecursos))
            termino[i] = 1;

    }

    int deadlock = 0; /* Variável para indicar se há deadlock. Caso haja, ela assume 1, caso não haja, assume 0. */

    int i = 0;
    while(i < m->quantProcessos){ /* Laço onde acontece a verificação de deadlock */
        if(termino[i] == 0 && menorIgual(m->solicitacao[i], trabalho, m->quantRecursos)){

            int *aux = trabalho;
            trabalho = somaVetores(trabalho, m->alocacao[i], m->quantRecursos);
            free(aux);

            termino[i] = 1;
            i = 0;
        }else
            i+=1;
    }

    for(i = 0; i < m->quantProcessos; i++){
        if(termino[i] == 0){
            deadlock = 1;
            break;
        }
    }

    free(termino);
    free(trabalho);

    return deadlock;
}

//! Função para inserir um novo processo na estrutura MultiplasIntancias.
MultiplasInstancias* inserirProcesso(MultiplasInstancias *m){

    int *vetNulo = calloc(m->quantRecursos, sizeof(int));

    m->alocacao = expandirMatriz(m->alocacao, vetNulo, m->quantProcessos, m->quantRecursos); // Espande a matriz com o novo vetor

    m->quantProcessos++;

    free(vetNulo);

    return m;
}

//! Função usada para solicitar um recurso para um processo. Conta com uma função auxiliar para verificar se há deadlock.
MultiplasInstancias* solicitaRecurso(MultiplasInstancias *m, int processo, int *solicitacao, int *deadlock, int *executou){

    int *aux = m->solicitacao[processo];
    m->solicitacao[processo] = somaVetores(m->solicitacao[processo], solicitacao, m->quantRecursos);
    free(aux);

    if(menorIgual(m->solicitacao[processo], m->disponivel, m->quantRecursos)){
        aux = m->solicitacao[processo];
        m->solicitacao[processo] = subtracaoVetores(m->solicitacao[processo], solicitacao, m->quantRecursos);
        free(aux);

        aux = m->disponivel;
        m->disponivel = subtracaoVetores(m->disponivel, solicitacao, m->quantRecursos);
        free(aux);


        aux = m->alocacao[processo];
        m->alocacao[processo] = somaVetores(m->alocacao[processo], solicitacao, m->quantRecursos);
        free(aux);
    }

    *executou = 1;

    if(!verificaEstado(m))
        *deadlock = 0;
    else
        *deadlock = 1;


    return m;
}

//! Função utilizada para liberar um recurso que o processo está retendo.
MultiplasInstancias* desalocaRecurso(MultiplasInstancias *m, int processo, int recurso){
    if(processo < m->quantProcessos){
        m->disponivel[recurso]++;
        m->alocacao[processo][recurso]--;
    }

    return m;
}

//! Função para liberar a memória da estrutura MultiplasInstancias.
void desalocaMultiplasInstancias(MultiplasInstancias *m){
    if(!m)
        return;

    if(m->disponivel)
        free(m->disponivel);
    if(m->quantProcessos > 0){
        for(int i = 0; i < m->quantProcessos; i++){
            free(m->alocacao[i]);
            free(m->solicitacao[i]);
        }

        free(m->solicitacao);
        free(m->alocacao);
    }

    free(m);
    m = NULL;
}