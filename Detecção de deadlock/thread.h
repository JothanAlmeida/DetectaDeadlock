#ifndef __THREAD_H
#define __THREAD_H

//! Tipo Abstrato de Dados para controle de informações da thread.
typedef struct thread{
    char *nome; /*!< Variável para identificar o nome de uma thread.*/
    int **operacoes; /*!< Matriz de operações realizadas pela thread.*/
    int **identacao; /*!<  Matriz contendo as informações de tabulação de cada operação da thread.*/
    int quantidadeLinhas; /*!<  Variável contendo a quantidade de linhas de uma thread.*/
}Thread;

//! Aloca uma nova estrutura do tipo Thread e inicializa as variáveis.
Thread *criaThread(char *nome);

//! Libera a memória alocada na estrutura Thread passada como parâmetro
void desalocaThread(Thread *thread);

#endif