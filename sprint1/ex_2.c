 
#include <stdio.h> 
#include <stdlib.h> 
 
#define SIZE 4 
#define FULL_SIZE SIZE * SIZE 
 
 
void swapElements(int* a, int* b){ 
    if(a == b){ 
        return; 
    } 
 
    *a = *a ^ *b; 
    *b = *a ^ *b; 
    *a = *a ^ *b; 
} 
 
int partition(int* arr, int low, int high){ 
    int pivot = *(arr + high); 
    int left = low; 
    int right = high - 1; 
     
    for(;;){ 
        while(left <= right && *(arr + left) <= pivot){ 
            left++; 
        } 
        while(left <= right && *(arr + right) >= pivot){ 
            right--; 
        } 
 
        if(right < left){ 
            break; 
        }else{ 
            swapElements((arr + left), (arr + right)); 
        } 
    } 
 
    int temp = *(arr + left); 
    *(arr + left) = pivot; 
    *(arr + high) = temp; 
    return left;  
} 
 
 
void quckSort(int* arr, int low, int high){ 
    if(low < high){ 
        int pivot = partition(arr, low, high); 
        quckSort(arr, low, pivot - 1); 
        quckSort(arr, pivot + 1, high); 
    } 
} 
 
int countMark(int *arr, int len, int k){ 
    int mark = 0, count = 1, pivot = 0, max_tap = k * 2; 
    int l_tap = max_tap; 
    for(int i = 1; i <= *(arr + len - 1); i++){ 
        if(i == *(arr + pivot)){ 
            for(int j = pivot; j < len; j++){ 
                if(*(arr + j) == i){ 
                    max_tap--; 
                }else{ 
                    pivot = j; 
                    break; 
                } 
            } 
            if(max_tap >= 0){ 
                mark++; 
            } 
            max_tap = k * 2; 
        } 
        // printf("%d = %d %d \n", i,  pivot, *(arr + pivot)); 
         
    } 
 
    return mark; 
} 
 
 
int main(void){ 
    int k, ch, len = 0; 
 
    if(scanf("%d", &k) != 1){ 
        perror("wrong n input"); 
    } 
 
    int arr[FULL_SIZE]; 
    char bffr[FULL_SIZE]; 
 
    while(fgets(bffr, FULL_SIZE, stdin) != NULL){ 
        for (int i = 0; bffr[i] != '\0'; i++) {  
            char ch = bffr[i]; 
            if(ch == ' ' || ch == '.' || ch == '\n'){ 
                continue; 
            } 
 
            *(arr + len) = ch - '0'; 
            len++; 
        } 
    } 
 
 
    quckSort(arr, 0, len - 1); 
 
    int mark = countMark(arr, len, k); 
    printf("%d\n", mark);     
 
    exit(EXIT_SUCCESS); 
} 
 
