#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


void genBinary(int n, char *bffr, int max_len, int indx_bffr, int l_count, int r_count){
    if(n == 0){
        *(bffr + indx_bffr) = '\0';
        if (l_count == r_count && l_count == (max_len / 2)) {
            printf("%s\n", bffr);
        }
    }else{
        
        if(l_count < r_count){
            return;
        }else{
            *(bffr + indx_bffr) = '(';
            genBinary(n - 1, bffr, max_len, indx_bffr + 1, l_count+1, r_count);

            *(bffr + indx_bffr) = ')';
            genBinary(n - 1, bffr, max_len, indx_bffr + 1, l_count, r_count+1);
        }
    

    }
}


void genBinaryC(int n){
    int indx_bffr = 0;
    int max_len = 1 << n;
    char *bffr = (char *)malloc((n + 1) * sizeof(char));

    for (size_t i = 0; i < max_len; i++){
        for (size_t j = 0; j < n; j++){
            int bit = (i >> (n - 1 - j)) & 1;
            if (bit == 0) {
                *(bffr + j) = '0';
            } else {
                *(bffr + j) = '1';
            }
        }
        *(bffr + n) = '\0';
        printf("%s\n", bffr);
    }   
}


int main(void){
    int n;
    scanf("%d", &n);

    char *buffer = (char *)malloc((n + 1) * sizeof(char));
    n *= 2;
    genBinary(n, buffer, n, 0, 0, 0);

    // genBinaryC(n);

    exit(EXIT_SUCCESS);
}