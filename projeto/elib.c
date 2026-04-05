
#include "elib.h"



    

Eliza *ReadFile(char* filename){
    Eliza *info = malloc(sizeof(Eliza));
    FILE *pfile = fopen(filename, "r");
    if(pfile == NULL){
        printf("Could not open file\n");
        free(info);
        return NULL; 
    }
    
    char buffer[1024] = {0}; 
    info->capacity_keywords = 10;
    info->capacity_responses = 10;
    info->pinitial_3 = calloc(12, sizeof(char*)); 
    info->pkey_words = malloc(info->capacity_keywords * sizeof(char*));
    info->presponses = malloc(info->capacity_responses * sizeof(char*));
    
    // conta o numero de blocos
    int total_blocks = 0;
    while(fgets(buffer, sizeof(buffer), pfile) != NULL){
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if(strcmp(buffer, "!") == 0) total_blocks++;
    }
    
    // calcula os blocos corretamente e aloca a memória
    info->blocks = total_blocks - 3; 
    info->counterRound_robin = calloc(info->blocks, sizeof(int));
    
    
    rewind(pfile); 
    
    //le as primeiras 12 linhas, os blocos especiais
    int count = 0;
    while(count < 12 && fgets(buffer, sizeof(buffer), pfile) != NULL){
        buffer[strcspn(buffer, "\r\n")] = '\0'; 
        info->pinitial_3[count] = strdup(buffer); 
        for(int i = 0; info->pinitial_3[count][i] != '\0'; i++){ 
            
            info->pinitial_3[count][i] = toupper((unsigned char)info->pinitial_3[count][i]);
        }
        count++;
    }
    
    info->count_keywords = 0;
    info->pkey_words_block = malloc(info->capacity_keywords * sizeof(int));
    info->count_responses = 0;
    info->presponses_block = malloc(info->capacity_responses * sizeof(int));
    
    for(int i = 0; i < info->blocks; i++){
        // Para as palavras chaves
        while(fgets(buffer, sizeof(buffer), pfile) != NULL){
            buffer[strcspn(buffer, "\r\n")] = '\0';
            if (strcmp(buffer, "!") == 0) break; 
            
            char *temp = strdup(buffer);
            for(int j = 0; temp[j] != '\0'; j++){
                
                temp[j] = toupper((unsigned char)temp[j]);
            }
            
            
            bool is_duplicate = false;
            for(int k = 0; k < info->count_keywords; k++) {
                if (strcmp(info->pkey_words[k], temp) == 0) {
                    info->pkey_words_block[k] = i; 
                    is_duplicate = true;
                    break;
                }
            }
            
            if (is_duplicate) {
                free(temp);
            } else {
                if(info->count_keywords >= info->capacity_keywords){
                    info->capacity_keywords *= 2;
                    info->pkey_words = realloc(info->pkey_words, info->capacity_keywords * sizeof(char*));
                    info->pkey_words_block = realloc(info->pkey_words_block, info->capacity_keywords * sizeof(int));
                }
                info->pkey_words[info->count_keywords] = temp;
                info->pkey_words_block[info->count_keywords] = i; 
                info->count_keywords++;
            }
        }
        
        // Para as respostas delas
        while(fgets(buffer, sizeof(buffer), pfile) != NULL){
            buffer[strcspn(buffer, "\r\n")] = '\0';
            if (strcmp(buffer, ".") == 0) break; 
            
            if(info->count_responses >= info->capacity_responses){
                info->capacity_responses *= 2;
                info->presponses = realloc(info->presponses, info->capacity_responses * sizeof(char*));
                info->presponses_block = realloc(info->presponses_block, info->capacity_responses * sizeof(int));
            }
            info->presponses[info->count_responses] = strdup(buffer);
            for(int j = 0; info->presponses[info->count_responses][j] != '\0'; j++){
                
                info->presponses[info->count_responses][j] = toupper((unsigned char)info->presponses[info->count_responses][j]);
            }
            info->presponses_block[info->count_responses] = i; 
            info->count_responses++;
        }
    }
    fclose(pfile);
    return info;
}

void FreeMem(char **pinput, Eliza *info){

    //limpagem de memoria do stdin
    if(pinput[1] != NULL) free(pinput[1]);
    free(pinput);
    //limpagem de memoria do dados que vinham do ficheiro
    free(info->counterRound_robin);
    for(int i = 0; i < 12; i++) if(info->pinitial_3[i] != NULL) free(info->pinitial_3[i]);
    free(info->pinitial_3);
    for(int i = 0; i < info->count_keywords; i++) free(info->pkey_words[i]);
    free(info->pkey_words);
    for(int i = 0; i < info->count_responses; i++) free(info->presponses[i]);
    free(info->presponses);
    free(info->pkey_words_block);
    free(info->presponses_block);
    free(info);
}