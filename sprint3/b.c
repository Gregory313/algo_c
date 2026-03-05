#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

const char* digit_to_letters[] = {
    "",     // 0
    "",     // 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz"  // 9
};

void printNum(const char** digit_to_letters, int a, int b){
    printf("%c %c\n", *(*(digit_to_letters + a) + 0), *(*(digit_to_letters + b) + 0));
    printf("%c %c\n", *(*(digit_to_letters + a) + 1), *(*(digit_to_letters + b) + 1));
    printf("%c %c\n", *(*(digit_to_letters + a) + 2), *(*(digit_to_letters + b) + 2));
           
}


void genComb(const char *digits, char* crr_comb_bffr, int dig_indx, int bffr_indx){
    if(dig_indx == strlen(digits)){
        *(crr_comb_bffr + bffr_indx) = '\0';
        printf("%s ", crr_comb_bffr);
        return;
    }

    int digit = *(digits + dig_indx) - '0';
    const char* letters = *(digit_to_letters + digit);

    for(int i = 0; *(letters + i) != '\0'; i++){
        *(crr_comb_bffr + bffr_indx) = *(letters + i);
        genComb(digits, crr_comb_bffr, dig_indx + 1, bffr_indx + 1);
    }
}


void phoneComb(const char* digits_input){
    int len = strlen(digits_input);

    if (len == 0) {
        printf("\n");
        return;
    }

    char* comb_buff = (char*)malloc((len + 1) * sizeof(char));
    if (comb_buff == NULL) {
        return;
    }

    genComb(digits_input, comb_buff, 0, 0);
    printf(" ");

    free(comb_buff);
}


int main(void){
    char a[2];
    scanf("%s", a);

    int len = 2 << 3; 


    char *buffer = (char *)malloc((len + 1) * sizeof(char));
    // printNum(digit_to_letters, 2, 3);

    // genBinary(digit_to_letters, buffer, 3, 0);
    phoneComb(a);

    exit(EXIT_SUCCESS);
}