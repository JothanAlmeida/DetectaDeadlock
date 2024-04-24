#ifndef __MULTIPLASINSTANCIAS_H
#define __MULTIPLASINSTANCIAS_H

#include "vector.h"

//!Tipo abstrato de dados para gerenciar as estruturas do algoritmo de multiplas instâncias.
typedef struct multiplasInstancias{
    int **alocacao; /*< Matriz contendo a quantidade de recursos alocados a cada processo.*/
    int **solicitacao; /*< Matriz contendo os recursos solicitados concorrentemente por cada processo.*/
    int *disponivel; /*< Vetor contendo a quantidade de recursos disponíveis.*/
    int quantProcessos; /*< Variável para armazenar a quantidade de processos envolvidos no algoritmo.*/
    int quantRecursos; /*<Variável para armazenar a quantidade de recursos envolvidos no algoritmo.*/
}MultiplasInstancias;

//! Função que aloca e inicializa a estrutura de MultiplasInstancias.
MultiplasInstancias *incializaMultiplasInstancias(int *disponivel, int lenDisponivel);

//!Função que analisa as estruturas e conclui se o sistema está ou não em deadlock.
int verificaEstado(MultiplasInstancias *m);

//! Função para inserir um novo processo na estrutura MultiplasIntancias.
MultiplasInstancias* inserirProcesso(MultiplasInstancias *m);

//! Função usada para solicitar um recurso para um processo. Conta com uma função auxiliar para verificar se há deadlock.
MultiplasInstancias* solicitaRecurso(MultiplasInstancias *m, int processo, int *solicitacao, int *deadlock, int *executou);

//! Função utilizada para liberar um recurso que o processo está retendo.
MultiplasInstancias* desalocaRecurso(MultiplasInstancias *m, int processo, int recurso);

//! Função para liberar a memória da estrutura MultiplasInstancias.
void desalocaMultiplasInstancias(MultiplasInstancias *m);

#endif