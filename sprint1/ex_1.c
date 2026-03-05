#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
 
int main(void){ 
    int n; 
 
    if(scanf("%d", &n) != 1){ 
        perror("wrong n input"); 
    } 
 
    int *arr = (int*)malloc(sizeof(int) * n); 
    if(arr == NULL){ 
        perror("no mem"); 
    	exit(EXIT_FAILURE); 
    } 
 
    int  len = 0; 
    while(len < n && scanf("%d", (arr + len)) == 1){ 
        len++; 
    } 
 
    int *arr_c = (int*)malloc(sizeof(int) * n); 
    if(arr_c == NULL){ 
        perror("no mem"); 
    	exit(EXIT_FAILURE); 
    } 
 
    int last_zero = -1; 
    for(int i = 0; i < len; i++){ 
        if(*(arr + i) == 0){ 
            last_zero = i; 
            continue; 
        } 
        if(last_zero == -1){ 
            *(arr_c + i) = INT_MAX; 
        }else{ 
            *(arr_c + i) = abs(i - last_zero); 
        } 
    } 
 
    for(int i = len - 1; i > -1; i--){ 
        if(*(arr + i) == 0){ 
            last_zero = i; 
            continue; 
        } 
        int dist = abs(i - last_zero); 
        if(*(arr_c + i) > dist){ 
            *(arr_c + i) = dist; 
        } 
    } 
 
    for(int i = 0; i < len; i++){ 
        printf("%d ", *(arr_c + i)); 
    } 
 
    free(arr); 
    free(arr_c); 
    exit(EXIT_SUCCESS); 
} 
 