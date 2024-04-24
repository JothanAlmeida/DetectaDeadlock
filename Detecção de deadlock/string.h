#ifndef __STRING_H
#define __STRING_H

//!Retorna uma parte da string, começando da variável inicio até o fim da string
char *particionaString(char *string, int inicio);

//!Verifica se a string1 está contida na string2. Caso esteja, retorna a string2 sem a string 1. Caso não esteja, retorna NULL.
char *estaContida(char *string1, char *string2);

//!Lê uma linha e retorna em formato de string. eof == -1 significa o fim do arquivo.
char *leLinha(int *identacao, int *eof);

#endif