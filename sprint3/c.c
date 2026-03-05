#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE 256 
#define INITIAL_LINES_CAPACITY 5

typedef struct Line{
    char *text;
    int len;
}Line;


Line* readLine(){
    size_t curr_capacity = CHUNK_SIZE;
    size_t len = 0;

    char *bffr = (char*)malloc(sizeof(char) * curr_capacity + 1);
    if(bffr == NULL){
        perror("no mem alloc");
        return NULL;
    }

    while(fgets(bffr + len, curr_capacity - len - 1, stdin) != NULL){
        len = strlen(bffr);

        if(len > 0 &&  *(bffr + len - 1) == '\n'){
            *(bffr + len - 1) = '\0';
            len--;
            break;
        }

        curr_capacity *= 2;
        char *tmp = (char*)realloc(bffr, curr_capacity + 1);
        if(tmp == NULL){
            perror("no mem alloc");
            free(bffr);
            return NULL;
        }
        bffr = tmp;
    }

    if(len == 0 && feof(stdin)){
        free(bffr);
        return NULL;
    }

    char* sized_buff = (char*)realloc(bffr, len + 1);
    if(sized_buff == NULL){
        sized_buff = bffr;
    }

    Line *n_line = (Line*)malloc(sizeof(Line));
    if(n_line == NULL){
        perror("no mem alloc");
        free(sized_buff);
        return NULL;
    }

    n_line->len = len + 1;
    n_line->text = bffr;

    return n_line;
}


Line** readStrings(int *lines_num){
    Line **lines = (Line**)malloc(sizeof(Line*) * 10);
    if(lines == NULL){
        perror("no mem alloc");
        return NULL;
    }
   
    int capacity = INITIAL_LINES_CAPACITY;
    *lines_num = 0;

    for(;;){

        Line *curr_line = readLine();
        if (curr_line == NULL)  break;

        if (*lines_num == capacity) {
            capacity *= 2;
            Line **tmp = (Line**)realloc(lines, capacity);
            if(tmp == NULL){
                for (size_t i = 0; i < *lines_num; i++){
                    free((*(lines + i))->text);
                    free(*(lines + i));
                }
                free(lines);
                *lines_num = 0;
                return NULL;
                
            }
            lines = tmp;
        }

        *(lines + *lines_num) = curr_line;
        (*lines_num)++;
    }

    if(*lines_num < capacity){
        Line **sized_lines = (Line**)realloc(lines, sizeof(Line*) * *lines_num);
        if(sized_lines != NULL){
            lines = sized_lines;
        }
    }
    return lines;
}


void freeLines(Line **lines, int num_lines){
    for(int i = 0; i < num_lines; i++){
        if(*(lines + i) != NULL){
            free((*(lines + i))->text);
            free(*(lines + i));
        }
    }
    free(lines);
}



int compareStrings(char* a, char* b){
    int res = 0;
    int a_ptr = 0;
    int b_ptr = 0;

    while(*(b + b_ptr) != '\0'){
        if( *(b + b_ptr) == *(a + a_ptr)){
            res++;
            a_ptr++;
        }
        b_ptr++;
    }

    if(res == strlen(a)){
        return 0;
    }else{
        return 1;
    }
}



int main(void){
    char *arr = (char*)malloc(sizeof(char) * (INITIAL_LINES_CAPACITY + 1));
    
    int len = 0;
    Line **lines = readStrings(&len);

    // for (int i = 0; i < len; i++){
    //     printf("%s ", (*(lines + i))->text);        
    // }
    if(compareStrings((*(lines))->text, (*(lines + 1))->text) == 0){
        printf("True\n");
    }else{
        printf("False\n");
    }

    freeLines(lines, len);
    exit(EXIT_SUCCESS);
}