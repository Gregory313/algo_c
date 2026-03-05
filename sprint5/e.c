#include <stdio.h>
#include <stdlib.h>


int catalanNum(int num){
    if(num <= 1){
        return 1;
    }

    int res = 0;

    for(int i = 0; i < num; i++){
        res += catalanNum(i) * catalanNum(abs(num - i - 1));
    }

    // printf("\n\n");
    return res;
}

int main(void){
    int len;
    scanf("%d", &len);

    
    printf("%d \n",catalanNum(len));

    return 0;
}



