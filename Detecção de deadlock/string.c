#include <stdio.h>
#include <stdlib.h>

/*
    Retorna uma parte da string, começando da variável inicio até o fim da string
*/
char *particionaString(char *string, int inicio){
    int contador1 = inicio, contador2 = 0;
    char *novaString = malloc(sizeof(char));

    while(string[contador1] != '\0'){
        novaString = realloc(novaString, (contador2 + 1) * sizeof(char));
        novaString[contador2] = string[contador1];
        contador1++;
        contador2++;
    }
    novaString = realloc(novaString, (contador2 + 1) * sizeof(char));
    novaString[contador2] = '\0';

    return novaString; /*!< Retorna a parte da String.*/
}


/*
    Verifica se a string1 está contida na string2. Caso esteja,
    retorna a string2 sem a string 1. Caso não esteja, retorna NULL.
*/
char *estaContida(char *string1, char *string2){
    int contador1 = 0, contador2 = 0;

    while(string2[contador1] != '\0'){
        if(string2[contador1] == string1[contador2]){
            contador2++;
        }else{
            if(string1[contador2] == '\0') // contém
                return particionaString(string2, contador1); /*!< Retorna a parte da string contida.*/

            contador2 = 0;
        }

        contador1++;
    }

    return NULL;
}

/*
    Lê uma linha e retorna em formato de string.
    eof == -1 significa o fim do arquivo.
*/

char *leLinha(int *identacao, int *eof){
    char *linha = malloc(sizeof(char)), c = ' ';
    int lenLinha = 0, identacaoEsq = 1;
    *identacao = 0;

    while(*eof != -1){
        *eof = scanf("%c", &c);

        if(c == '\t' && identacaoEsq == 1){
            (*identacao)++;
        }else
            identacaoEsq = 0;

        linha = realloc(linha, (lenLinha + 1) * sizeof(char));

        if(c == '\n' || *eof == -1){

            linha[lenLinha] = '\0';
            return linha;
        }else{
            linha[lenLinha] = c;
            lenLinha++;
        }
    }

    return NULL;
}