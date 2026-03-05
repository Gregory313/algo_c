#include <iostream>
#include <unordered_map>


using namespace std;


void swap(long long int *a, long long int*b){
    if(a == b){
        return;
    }


    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}



long long int patition(long long int *arr, long long int low, long long int high){
    long long int pivot = *(arr + high);
    long long int left = low;
    long long int right = high - 1;


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
            swap( *(arr + left), *(arr + right));
        }

    }

    swap( *(arr + left), *(arr + high));
    return left;
}


void quickSort(long long int *arr, long long int low, long long int high){
    if(low < high){
        long long int pivot = patition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}



int main(void){
    unordered_map<long long int, long long int> holder;
    long long int sum, len;


    scanf("%lld", &len);
    scanf("%lld", &sum);
    long long int i = 0;


    long long int* arr = (long long int*)malloc(sizeof(long long int) * len);


    while(i < len && scanf("%lld", (arr + i)) == 1){
        i++;
    }


    for (long long int k = 0; k < len; k++){
        holder[*(arr + k)] = k;
    }



    quickSort(arr, 0, len - 1);



    long long int** holder_h = (long long int**)malloc(sizeof(long long int*) * len);

    long long int indx = 0;



    long long int f = 0;

    for (long long int k = 0; k < len; k++){
        if (k > 0 && arr[k] == arr[k-1]) {
            continue;
        }

        long long int num = sum - *(arr + k);

        for (long long int l = k + 1; l < len; l++){
            if (l > k + 1 && arr[l] == arr[l-1]) {
                continue;
            }

            long long int l_num = num - *(arr + l);

            long long int left = l + 1;

            long long int right = len - 1;

            long long int l_sum = 0;

            while(left < right){
                l_sum = *(arr + right) + *(arr + left);


                if(l_sum == l_num){
                    *(holder_h + f) = (long long int*)malloc(sizeof(long long int) * 4);
                    *(*(holder_h + f) + 0) = *(arr + k);
                    *(*(holder_h + f) + 1) = *(arr + l);
                    *(*(holder_h + f) + 2) = *(arr + left);
                    *(*(holder_h + f) + 3) = *(arr + right);
                    f++;

                    // printf("%d %d %d %d\n", *(arr + k), *(arr + l), *(arr + left), *(arr + right));

                    break;
                }

                // cout << l_sum << " | " << l_num << endl;

                if( l_sum < l_num){
                    left++;
                }else if( l_sum > l_num){
                    right--;
                }
            }

            // cout << endl;

        }

    }

    printf("%lld\n", f);


    for (long long int z = 0; z < f; z++){
        for (long long int l = 0; l < 4; l++){
            printf("%lld ", *(*(holder_h + z) + l));


        }

        printf("\n");
    }

    for (long long int z = 0; z < f; z++){
        free(*(holder_h + z));
    }

    free(holder_h);


    exit(EXIT_SUCCESS);
}