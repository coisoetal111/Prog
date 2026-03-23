#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>

typedef struct _Run_Results {
    char *pos;
    char *esc;
    char *pos_esc;
    char *dorsal;
    char *nome;
    char *sexo;
    char *tempo;
    struct _Run_Results *next;
} Run_Results;

Run_Results *final_info(char *file);
Run_Results *_info(char *line);
Run_Results *insert_info(Run_Results *info_head, Run_Results *info);
void print_lista(Run_Results *info_head);
void free_lista(Run_Results *info_head);



int main() {

    Run_Results *info;

    info = final_info("RunResults.txt");
    print_lista(info);
    free_lista(info);



}

Run_Results *final_info(char* filename){


    FILE *in = fopen(filename, "r");
    if (in == NULL) { 
        printf("Erro ao abrir %s\n", filename);
        exit(1);
    }
    
    
    int count = -1, size = 256;
    char temp[size], *token;
    Run_Results *info, *info_head = NULL;


    while(fgets(temp, size, in)){
        if (count == -1)
        {
            count ++;
            continue;
        }
        info =_info(temp);
        info_head = insert_info(info_head, info);
        
   }

   fclose(in);

   return info_head;
}
Run_Results* _info(char* line){
    Run_Results* info;
    
    int position = 0;
    char* token;

    if ((info = calloc(1, sizeof(Run_Results))) == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(EXIT_FAILURE);
    }

    char **ptr[] = {&info->pos, &info->esc, &info->pos_esc, &info->dorsal, &info->nome, &info->sexo, &info->tempo};
    token = strtok(line, "\t");

    while(token != NULL){
        token[strcspn(token, "\n")] = '\0';
        if ((*ptr[position] = malloc(strlen(token)+1)) == NULL) {
            printf("Erro ao alocar memoria no malloc.\n");
            exit(EXIT_FAILURE);
        }
        
        
        
        strcpy(*ptr[position], token);
        token = strtok(NULL, "\t");
        position++;
    }
    info->next = NULL;

    return info;

}

Run_Results *insert_info(Run_Results *info_head, Run_Results *info){
    Run_Results* aux;
    
    
    
    if(info_head == NULL) {info_head = info;
    
    return info_head;
    }
    aux = info_head;
    while (aux->next != NULL)
    {
        aux = aux->next;
    }
    aux->next = info;

    return info_head;



}

void print_lista(Run_Results *info_head) {
    Run_Results *Aux;
    FILE *out = fopen("RunResult_out.txt", "w");
    for (Aux = info_head; Aux != NULL; Aux=Aux->next) {
        fprintf(out, "%s\t%s\t%s\t%s\t%s\t%s\t%s\n", Aux->pos, Aux->esc, Aux->pos_esc, Aux->dorsal, Aux->nome, Aux->sexo, Aux->tempo);
    }

    fclose(out);
}

void free_lista(Run_Results *info_head) {
    Run_Results *Aux;

    Aux = info_head;
    while (info_head != NULL) {
        Aux = info_head;
        info_head = info_head->next;
        free(Aux->pos);
        free(Aux->esc);
        free(Aux->pos_esc);
        free(Aux->dorsal);
        free(Aux->nome);
        free(Aux->sexo);
        free(Aux->tempo);
        free(Aux);
    }
}

