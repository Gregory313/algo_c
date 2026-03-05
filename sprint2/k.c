#include <stdlib.h>


int main(void){

    int num = 0;
    scanf("%d", &num);


    if(num < 2){
        printf("1");
        return 0;
    }

    int l_e = 1;
    int e = 1, s = 1;

    for(int i = 2; i <= num; i++){
        int tmp = e;
        e += l_e;
        l_e = tmp;
    }

    printf("%d\n", e);

    return 0;
}