
#include "elib.h"

//este codigo com a ajuda do isalnum que remove qualquer simbolo vai remover o simbolos dos inputs stdin
void removeSymbols(char * vector){
    int i = 0;
    int j = 0;
    bool repeatedSpaces = true; //começa true pq nao queremos espacos no inicio da string
    while(vector[i]){ //loop funciona ate encontrar o \0 porque este de todos os outros é o que possui o valor de 0 no ASCII
        if(isalnum(vector[i])){ //isalnum da o valor de 0 caso encontre algo que nao e alphanumerico
                vector[j++] = vector[i]; //j++ nao significa que começa no 1 mas sim que começa no zero e sobe logo de seguida para 1
                repeatedSpaces = false;
        }
        if(vector[i] == ' '){ //caso seja um espaço temos de ver pq queremos manter os espaços mas remover os repetidos
            if(!repeatedSpaces){ //o ultimo char era uma letra ou numero qualquer
                vector[j++] = vector[i];
                repeatedSpaces = true; //comeca a ser verdade para assim no caso de haver outro espaco seguido ele nao vai ser colocado na string
            }
        }
        i++;
    }
    if(j > 0 && vector[j-1] == ' ') j--;
    vector[j] = '\0'; //garantir que a sting tem o seu fim marcado
}
int searcher(char *info, char **dataBase, int count){
    for(int i = 0; i < count; i++){
        char *search = strstr(info, dataBase[i]); //ve se encontra alguma semelhança nas strings e atribui a search
        while(search){
            bool checkBefore = (search == info) || (*(search-1) == ' '); //cheka a parte detras para ver se nao ha nenhuma palavra que nao pertence
            bool checkAfter = (search[strlen(dataBase[i])] == '\0') || (search[strlen(dataBase[i])] == ' ');//isto cheka a que tem a frente da palavra
            if(checkBefore && checkAfter) return i;

            search = strstr(search+1, dataBase[i]); //vai avaçando na palavra que achamos para ver se e ou nao o que queremos
        }
    }
    return -1; //este return e -1 para garantir que nunca pode ter um valor igual ao i que tbm damos return
}
char *round_robin(char **dataBase, int count, int*responsesBlock, int Block, int *crr){
    int block_min = -1;
    int block_size = 0;
    for(int i = 0; i < count; i++){
        if( responsesBlock[i] == Block){
            if (block_min == -1) block_min = i; //armaneza o array de resposta onde o bloco começa
            block_size++; //vai armanezar quantas respostas existem dentro do bloco
        }
    }
    //se o valor do bloco tiver um index menor que o inicio ou se ja tiver chegado ao fim do bloco ele reseta
    if(crr[Block] < block_min || crr[Block] >= block_min + block_size) crr[Block] = block_min;
    char *result = strdup(dataBase[crr[Block]]);
    crr[Block]++; //incrementa o valor do index dentro do bloco em 1 para assim haver a rotatividade esperada
    return result;
}
char *getRest(char **info, char *dataBase, int count){
        char *rest = strstr(info[0], dataBase); //encontra a keyword na string
        if(rest != NULL){
        rest += strlen(dataBase); //vai para a frente da keyword para assim nao termos a keyword no print
        if(*rest == '\0') return NULL;
        return rest;
        }
    return NULL; //por boa pratica devemos returnar sempre algo no fim do codigo mesmo que pareça impossivel chegar ate aqui
}
char *conjution(char * response, bool is_portuguese){
    
    
    if(response == NULL) return NULL; //porque pode ser que o getrest tenha returnado nada e nos nao querremos quebrar o flow no main
    char *en_cases[] = {"ARE", "AM", "WERE", "WAS", "I", "YOUR", "MY", "IVE", "YOUVE", "IM", "ME", "US", "WE"};
    char *en_conj[]  = {"AM", "ARE", "WAS", "WERE", "YOU", "MY", "YOUR", "YOUVE", "IVE", "YOURE", "YOU", "YOU", "YOU"};
    int en_count = 13;

    
    char *pt_cases[] = {"EU", "TU", "COMIGO", "CONTIGO", "TEU", "SEU", "MEU", "TEUS", "SEUS", "MEUS", "TUA", "SUA", "MINHA", "TUAS", "SUAS", "MINHAS", "MIM", "TI"};
    char *pt_conj[]  = {"TU", "EU", "CONTIGO", "COMIGO", "MEU", "MEU", "TEU", "MEUS", "MEUS", "TEUS", "MINHA", "MINHA", "TUA", "MINHAS", "MINHAS", "TUAS", "TI", "MIM"};
    int pt_count = 18;

    // mudar isto talvez mas serve para escolher qual usar
    char **cases = is_portuguese ? pt_cases : en_cases;
    char **conj  = is_portuguese ? pt_conj : en_conj;
    int count    = is_portuguese ? pt_count : en_count;
    char *new_resp = calloc(strlen(response) * 2 + 2, sizeof(char)); //criar a nova resposta tendo cuidado com o facto que a nova resposta pode ter mais bits que a anterior devido a por exemplo passar de I para YOU
    if(response[0] == ' ') strcpy(new_resp, " "); //adiciona o espaco vazio que existe no inicio da string
    char *word = strtok(response, " "); //basicamente separa a string em tipo varias caixas com palavras dentro, essa separacao e feita onde ha os ' '

    while(word != NULL) {
        char *next_word = strtok(NULL, " "); //salta para a proxima "caixa"
        bool isLast = (next_word == NULL); //se for null ou seja a string acabou sabemos que a atual e a ultima e isso ajuda no caso do you
        bool replaced = false; //saber se ja foi substituida ou nao na string


        if (!is_portuguese && strcmp(word, "YOU") == 0) { //para o caso especial do you que pode dar dois outputs diferentes
            if (isLast) strcat(new_resp, "ME");
            else strcat(new_resp, "I");
            replaced = true;
        }
        else {
            for(int i = 0; i < count; i++) {
                if(strcmp(word, cases[i]) == 0) {
                    strcat(new_resp, conj[i]);
                    replaced = true;
                    break; //para o for porque ja encontramos a conjucao
                }
            }
        }
        if(!replaced) {  //se nao for algo para substituir ent mantem-se
            strcat(new_resp, word);
        }
        if(!isLast) { //enqaunto nao for a ultima palavra metemos um espaco depois
            strcat(new_resp, " ");
        }
        word = next_word; //avançar para o proximo, nao temos aqui o strtok(NULL, " ") porque precisamos dele para o isLast e por isso ja tinhamos o usado
    }
    
    return new_resp;
    }

    

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