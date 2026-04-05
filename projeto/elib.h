#ifndef ELIB_H
#define ELIB_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>



/*o struct é usado no código para a função read file
como em c as funções só dão return a uma "variavel" criei o struct para servir de bundle para 
tudo aquilo que o código necessita de saber */
typedef struct
{
    int capacity_keywords;
    int capacity_responses;
    char **pinitial_3;
    char **pkey_words;
    char **presponses;
    int count_keywords;
    int *pkey_words_block;
    int count_responses;
    int *presponses_block;
    int blocks;
    int *counterRound_robin;
} Eliza;








char *getRest(char **info, char *dataBase, int count);
Eliza *ReadFile(char* filename);
void removeSymbols(char * vector);
int searcher(char *info, char **dataBase, int count);
char *round_robin(char **dataBase, int count, int*responsesBlock, int Block, int *crr);
char *conjution(char * response, bool is_portuguese);
void FreeMem(char **pinput, Eliza* info);

#endif