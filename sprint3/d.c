#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b){
    if(a == b){
        return;
    }

    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}


int partition(int *arr, int low, int high){
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

        if(left >= right){
            break;
        }else{
            swap((arr + left), (arr + right));
        }
    }
    swap((arr + left),  (arr + high));

    return left;
}


void quickSort(int *arr, int low, int high){
    if(high > low){
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}



void countSort(int* arr, int k, int n){
    int* counted_values = (int*)calloc(k, sizeof(int));
    for (int i = 0; i < k; i++){
        *(counted_values + *(arr + i))+= 1;
    }
    int index = 0;
    for(int value = 0; value < n; value++){
        for(int amount = 0; amount < *(counted_values + value); amount++){
            *(arr + index) = value;
            index++;
        }
    }
    free(counted_values);
}



int main(void){
    int len = 0;
    scanf("%d", &len);

    int *arr = (int*)malloc(sizeof(int) * len);

    int i = 0;
    while( i < len && scanf("%d", (arr + i)) == 1){
        i++;
    }

    countSort(arr, len, 3);

    for (int i = 0; i < len; i++){
        printf("%d ", *(arr + i));
    }
    
    free(arr);
    exit(EXIT_SUCCESS);
}