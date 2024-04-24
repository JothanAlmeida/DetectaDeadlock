#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "thread.h"
#include "vector.h"

Thread *criaThread(char *nome){ //! Aloca e inicializa as variáveis de uma nova estrutura do tipo Thread.
    Thread *thread = malloc(sizeof(Thread));
    thread->nome = nome;
    thread->quantidadeLinhas = 0;
    thread->operacoes = NULL;
    thread->identacao = NULL;
    return thread;
}

void desalocaThread(Thread *thread){
    if(!thread)
        return;
    if(thread->operacoes){
        for(int i = 0; i < 1; i++){
            free(thread->operacoes[i]);
            free(thread->identacao[i]);
        }
        free(thread->identacao);
        free(thread->operacoes);
    }
    free(thread->nome);
    free(thread);
}