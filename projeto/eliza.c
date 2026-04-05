/*Rodrigo Torres- ist1117968
Diogo Pinto - ist1117735
Grupo 121
LEEC - 25/26*/

#include "elib.h"









int main(int argc, char **argv)
{
    // Terminal handler setup
    char *filename = "eliza.dat";
    FILE *output = stdout;
    FILE *input = stdin;
    FILE *log = NULL;
    int terhandler;
    bool is_portuguese = false; //para saber depois se a conjucao e em portugues ou nao
    opterr = 0; //para nunca imprimir os seus erros no terminal 
    char *error_msg = NULL; //para a mensagem de erro 
    while ((terhandler = getopt(argc, argv, "hi:o:l:f:p")) != -1) {
        switch (terhandler) {
            case 'h':
                printf("Arguments:\n-h\t\tshow the help for the user(this message) and ends\n");
                printf("-i[filename]\tentry name file, in alternative of stdin\n");
                printf("-o[filename]\texit name file, in alternative of stdout\n");
                printf("-l[filename]\tmake log of the input and output to the file filename\n");
                printf("-i[filename]\tuse the file filename with the data base of responses instead of \"eliza.dat\"\n");
                printf("-p\t\tuse portuguese rules, instead of the english ones\n");
                exit(EXIT_SUCCESS);
                break;
            case 'i':
                input = fopen(optarg, "r");
                if (input == NULL) {
                    fprintf(output, "Error while opening the file %s\n", optarg);
                    exit(EXIT_FAILURE); 
                }
                break;
            case 'o':
                output = fopen(optarg, "w");
                if (output == NULL) exit(EXIT_FAILURE);
                break;
            case 'l':
                log = fopen(optarg, "w");
                if (log == NULL) exit(EXIT_FAILURE);
                break;
            case 'f':
                filename = optarg;
                break;
            case 'p':
                is_portuguese = true; //passa a portugues
                break;

            case '?':
                if (error_msg == NULL) { //apenas "aluga" espaco se houver um primeiro erro
                    error_msg = malloc(100 * sizeof(char));
                    
                    if (optopt == 'i' || optopt == 'l' || optopt == 'o' || optopt == 'f')
                        sprintf(error_msg, "Option -%c requires an argument.\n", optopt);
                    else if (isprint(optopt))
                        sprintf(error_msg, "Unknown option `-%c'.\n", optopt);
                    else
                        sprintf(error_msg, "Unknown option character `\\x%x'.\n", optopt);
                }
                break;
            default:
                abort();
        }
    }
    if (error_msg != NULL) { //ve se existiu algum erro no codigo
        fprintf(output, "%s", error_msg);
        free(error_msg); // limpa a memoria
        
        if(output != stdout) fclose(output);
        if(input != stdin) fclose(input);
        if(log != NULL) fclose(log);
        return 1;
    }
-
-
-

    //terminal handler
    char *filename = "eliza.dat";
    FILE *output = stdout;
    FILE *input = stdin;
    FILE *log = NULL;
    int terhandler;
    bool is_portuguese = false;//para saber depois na conjução se é em portugues ou não
    while ((terhandler = getopt(argc, argv, "hi:o:l:f:p")) != -1)
  {
    switch (terhandler)
      {
      case 'h':
        printf("Arguments:\n-h\t\tshow the help for the user(this message) and ends\n");
        printf("-i[filename]\tentry name file, in alternative of stdin\n");
        printf("-o[filename]\texit name file, in alternative of stdout\n");
        printf("-l[filename]\tmake log of the input and output to the file filename\n");
        printf("-i[filename]\tuse the file filename with the data base of responses instead of \"eliza.dat\"\n");
        printf("-p\t\tuse portuguese rules, instead of the english ones\n");
        exit(EXIT_SUCCESS);
        break;
      case 'i':
       input = fopen(optarg, "r");
                if (input == NULL) {
                    fprintf(output, "Error while opening the file %s", optarg);
                    if(output != NULL) fclose(output);
                    if(log != NULL) fclose(log);
                    return 1;
                }

        break;
      case 'o':
        output = fopen(optarg, "w");
                if (output == NULL) {
                    //eu poderia meter uma mensagem de erro no stderr mas no enunciado especifica-se que não é para escrever no stderr
                    if(input != NULL) fclose(input);
                    if(log != NULL) fclose(log);
                    return 1;
                }
        //cria um ficheiro com o nome dado e escreve o output aí
        
        break;
        case 'l':
        log = fopen(optarg, "w");
                if (log == NULL) {
                    fprintf(output, "Error while opening the file %s", optarg);
                    if(input != NULL) fclose(input);
                    if(output != NULL) fclose(output);
                    return 1;
                }
        break;
      case 'f':
       filename = optarg;
        break;
      case 'p':
        is_portuguese = true;
        //Português ao invés de inglês
        break;




        case '?':
        if (optopt == 'i' || optopt == 'l' || optopt == 'o' || optopt == 'f')
          fprintf (output, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (output, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (output,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        if(output != stdout) fclose(output);
        if(input != stdin) fclose(input);
        if(log != NULL) fclose(log);
        return 1;
      default:
        abort ();
    }
}



    Eliza *info = ReadFile(filename);
    //caso o ReadFile der return NULL, fecha todos os ficheiros para não haver erros de valgrind
    if (info == NULL) {
        if(output != stdout) fclose(output);
        if(input != stdin) fclose(input);
        if(log != NULL) fclose(log);
        return 1; 
    }
    char buffer[1024] = {0}; //buffer para armazenar temporáriamente as informções do input


    fprintf(output, "%s\n", info->pinitial_3[2]);


    if(log != NULL) fprintf(log, "%s\n", info->pinitial_3[2]); //escrever as inputs no log
    /* temos de nos preocupar com o receber input, encontrar a equivalencia em termos de keywords e rotacionar as palavras*/
    char **pinput = calloc(10, sizeof(char*)); //estou a usar aqui o calloc pq como vou precisar guardar informação convem que comece em null
    while(true){
        if(fgets(buffer, sizeof(buffer), input) == NULL) break;
            if(log != NULL) fprintf(log, "%s\n", buffer); //escrever as inputs no log
            buffer[strcspn(buffer, "\r\n")] = '\0';  //vamos tratar o input ja no buffer para assim caso recebemos BYE ou ADEUS o programa para
            if(buffer[0] == '\0') continue;
            for(int i = 0; buffer[i] != '\0'; i++){
                buffer[i] = toupper(buffer[i]);
            }
            removeSymbols(buffer);
            if(strcmp(buffer, "\0") == 0) continue; // caso o input seja so espaços
            if(strcmp(buffer, is_portuguese ? "ADEUS":"BYE") == 0){ //falta meter o is_portuguese aqui para depois funcionar para o adeus
                fprintf(output, "%s\n", info->pinitial_3[10]);
                if(log != NULL) fprintf(log, "%s\n", info->pinitial_3[10]);// escrever output no log

                break;
            }
            pinput[0] = strdup(buffer);
            //criar condição para caso de repeticao de input
            if(pinput[1] != NULL && strcmp(pinput[0], pinput[1]) == 0){ //caso o ultimo input seja igual ao input atual
                fprintf(output, "%s\n", info->pinitial_3[6]);
                if(log != NULL) fprintf(log, "%s\n", info->pinitial_3[6]);// escrever output no log
                free(pinput[0]);
                continue;
            }
            if(pinput[1] != NULL) free(pinput[1]); //liberta o ultimo input
            pinput[1] = strdup(pinput[0]); //guarda o input atual

            int match = searcher(pinput[0], info->pkey_words, info->count_keywords); //vai receber o index da keyword onde foi encontrado a correspondencia
            if(match == -1) match = info->count_keywords - 1; //vamos pegar  no ultima string de todas dentro do array de keywords para obtermos o index do bloco
            int currentBlock = info->pkey_words_block[match]; //obter o index do block onde esta a correspondencia
           

        // DEBUG - apagar depois
        //fprintf(output, "DEBUG: keyword=%s block=%d crr=%d\n", 
        //info->pkey_words[match], currentBlock, info->counterRound_robin[currentBlock]);
            char *resp = round_robin(info->presponses, info->count_responses, info->presponses_block, currentBlock, info->counterRound_robin);
            char *asterisk = strchr(resp, '*');
            if(asterisk != NULL){
                char *rest = getRest(pinput, info->pkey_words[match], info->count_keywords);
                char *finishResponses = conjution(rest, is_portuguese);
                if(finishResponses != NULL){
                    char *final_of_string = strdup(asterisk + 1); //passa para uma sting todo o resto depois do *
                    *asterisk = '\0'; //remove o * no resp ja que estes estao associados pelo mesmo adereco
                    int size = strlen(finishResponses) + strlen(resp) + strlen(final_of_string) + 1;
                    resp = realloc(resp, size * sizeof(char));
                    strcat(resp, finishResponses);
                    strcat(resp, final_of_string);
                    free(finishResponses);
                    free(final_of_string);
                }else{
                    int len = strcspn(resp, "*");
                    resp[len] = resp[len+1];
                    resp[len+1] = '\0';
                }
            }
                fprintf(output, "%s\n", resp);
                if(log != NULL) fprintf(log, "%s\n", resp);// escrever output no log
                free(resp);
                free(pinput[0]); //limpagem de memoria do stdin
    }
    //fechar os ficheiros do terminal
    if(output != stdout) fclose(output);
    if(input != stdin) fclose(input);
    if(log != NULL) fclose(log);

    FreeMem(pinput, info);

    

    
    exit(EXIT_SUCCESS);
}

