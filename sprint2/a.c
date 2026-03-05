#include <stdio.h>
#include <stdlib.h>

void freeMatrix(int **arr, int len){
    for(int i = 0; i < len; i++){
        free(*(arr + i));
    }
    free(arr);
}

int main(void){
    int r, c;
    if(scanf("%d%d", &r, &c) != 2){
        perror("error input");
    }

    int **matrix = (int**)malloc(sizeof(int**) * c);
    if(matrix == NULL){
        perror("no free mem");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < c; i++){
        *(matrix + i) = (int*)malloc(sizeof(int) * r);
        if(*(matrix + i) == NULL) { perror("no free mem"); exit(EXIT_FAILURE);}
    }


    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            scanf("%d", (*(matrix + j) + i));
        } 
    }

    for(int i = 0; i < c; i++){
        for(int j = 0; j < r; j++){
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }

    freeMatrix(matrix, c);
    return 0;
}