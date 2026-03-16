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
int peso(char *esc);
int comp(const void *a, const void *b);
void sort(Run_Results **total_info);
void print_lista(Run_Results *info_head);
void free_lista(Run_Results *info_head);



int main() {
    Run_Results *total_info;
    total_info = final_info("RunResults.txt");
    sort(&total_info);
    print_lista(total_info);
    free_lista(total_info);
}

Run_Results *final_info(char *file) {
    Run_Results *info, *info_head = NULL;
    FILE *fptr = fopen(file, "r");
    int count = -1, size = 100;
    char temp[size], *token;

    if (fptr == NULL) {
        printf("Erro ao abrir o ficheiro com o nome: %s\n", file);
        exit(EXIT_FAILURE);
    }
    while (fgets(temp, size, fptr) != NULL) {
        if (count == -1) {
            count++;
            continue;
        }
        info = _info(temp);
        info_head = insert_info(info_head, info);
    }

    fclose(fptr);

    

    return info_head;

}

Run_Results *_info(char *line) {
    Run_Results *info;
    char *token;
    int position = 0;

    if ((info = (Run_Results*) calloc(1, sizeof(Run_Results))) == NULL) {
        printf("Erro ao alocar a memoria.\n");
        exit(EXIT_FAILURE);
    }

    char **ptr[] = {&info->pos, &info->esc, &info->pos_esc, &info->dorsal, &info->nome, &info->sexo, &info->tempo};
    token = strtok(line, "\t");

    while (token != NULL) {
        token[strcspn(token, "\n")] = '\0';
        if ((*ptr[position] = malloc(strlen(token)+1)) == NULL) {
            printf("Erro ao alocar memoria no malloc.\n");
            exit(EXIT_FAILURE);
        }
        strcpy(*ptr[position], token);
        position++;
        token = strtok(NULL, "\t");
    }
    info->next = NULL;

    return info;
}

Run_Results *insert_info(Run_Results *info_head, Run_Results *info) {
    Run_Results *AuxT;

    if (info_head == NULL) {
        info_head = info;
    } else {
        AuxT = info_head;
        while (AuxT->next != NULL)
            AuxT = AuxT->next;
        AuxT->next = info;
    }

    return info_head;
}

void print_lista(Run_Results *info_head) {
    Run_Results *Aux;
    FILE *out = fopen("RunResults_out.txt", "w");
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


void sort(Run_Results **info_head) {
    if (*info_head == NULL) return;

    
    int count = 0;
    Run_Results *curr = *info_head;
    while (curr) { count++; curr = curr->next; }

    
    Run_Results **array = malloc(count * sizeof(Run_Results *));
    curr = *info_head;
    for (int i = 0; i < count; i++) {
        array[i] = curr;
        curr = curr->next;
    }

   
    qsort(array, count, sizeof(Run_Results *), comp);

    
    for (int i = 0; i < count - 1; i++) {
        array[i]->next = array[i+1];
    }
    array[count-1]->next = NULL;
    *info_head = array[0]; 

    free(array);
}

int comp(const void *a, const void *b) {
    
    Run_Results *atletaA = *(Run_Results **)a;
    Run_Results *atletaB = *(Run_Results **)b;

    return peso(atletaA->esc) - peso(atletaB->esc);
}

int peso(char *esc) {
    if (strcmp(esc, "F20") == 0) return 1;
    if (strcmp(esc, "F40") == 0) return 2;
    if (strcmp(esc, "F45") == 0) return 3;
    if (strcmp(esc, "M20") == 0) return 4;
    if (strcmp(esc, "M35") == 0) return 5;
    if (strcmp(esc, "M40") == 0) return 6;
    if (strcmp(esc, "M45") == 0) return 7;
    if (strcmp(esc, "M50") == 0) return 8;
    if (strcmp(esc, "M55") == 0) return 9;
    if (strcmp(esc, "M60") == 0) return 10;
    

    return 99;
}