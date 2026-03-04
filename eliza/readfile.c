/*O objetivo desta parte inicial do codigo e de abrir o ficheiro de forma dinamica e ser
capaz de o ler*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int reader_storage(char *file)
{   //open the file and read it
    FILE *pfile = fopen("file.txt", "r");
    char buffer[1024] = {0};
    int capacity_keywords = 10;
    int capacity_responses = 10;
    char **pinitial_3 = calloc(3, sizeof(char*));
    char **pkey_words = malloc(capacity_keywords * sizeof(char*));
    char **presponses = malloc(capacity_responses * sizeof(char*));
    char **pespecial = calloc(1, sizeof(char*));
    if(pfile == NULL){
        printf("Could not open file\n");
        return 1;
    }
    /*vai salvar as informacoes vinda do ficheiro
    nos diferentes arrays de pointers*/
    //para as 3 especiais
    int count = 0;
    while(count < 3 && fgets(buffer, sizeof(buffer), pfile) != NULL){
            buffer[strcspn(buffer, "\n")] = '\0'; //limpa o buff pode ser que mude para outra forma de limpar o buff
            pinitial_3[count] = strdup(buffer); //copia o que se encontra no buffer para o array alocando automaticamente a memoria suficiente
            for(int i = 0; pinitial_3[count][i] != '\0'; i++){ //tranformar letra por letra em upper case para ter tudo maiusculo
                pinitial_3[count][i] = toupper(pinitial_3[count][i]);
            }
            count++;
    }
    //para as palavras chaves
    int count_keywords = 0;
    while(fgets(buffer, sizeof(buffer), pfile) != NULL){
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strcmp(buffer, "!") == 0) break; // programa vai parar quando encontrar o !
            if(count_keywords >= capacity_keywords){
                capacity_keywords *= 2;
                pkey_words = realloc(pkey_words, capacity_keywords * sizeof(char*));
            }
            pkey_words[count_keywords] = strdup(buffer);
            for(int i = 0; pkey_words[count_keywords][i] != '\0'; i++){
                pkey_words[count_keywords][i] = toupper(pkey_words[count_keywords][i]);
            }
            count_keywords++;
    }
    //para as respostas delas
    int count_responses = 0;
    while(fgets(buffer, sizeof(buffer), pfile) != NULL){
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strcmp(buffer, ".") == 0) break; // programa vai parar quando encontrar o .
            if(count_responses >= capacity_responses){
                capacity_responses *= 2;
                presponses = realloc(presponses, capacity_responses * sizeof(char*));
            }
            presponses[count_responses] = strdup(buffer);
            for(int i = 0; presponses[count_responses][i] != '\0'; i++){
                presponses[count_responses][i] = toupper(presponses[count_responses][i]);
            }
            count_responses++;
    }
    int count_especial = 0;
    while(fgets(buffer, sizeof(buffer), pfile) != NULL){
            buffer[strcspn(buffer, "\n")] = '\0';
            pespecial[count_especial] = strdup(buffer);
            for(int i = 0; pespecial[count_especial][i] != '\0'; i++){
                pespecial[count_especial][i] = toupper(pespecial[count_especial][i]);
            }
            count_especial++;
    }
    return 0;
}
