#include <stdio.h>
#include <stdlib.h>

long long power(int base, int exp){
    long long res = 1;
    if (exp < 0) {
        return 0;
    }

    for(int i = 0; i < exp; i++){
        res *= base;
    }
    return res;
}


long long pisanoPeriod(long long d, int num, long long *pisanos, int len){
    if (d == 1) return 1;
    long long prev = 0, curr = 1;

    for(long long i = 0; i <= d * d; i++){
        long long tmp = (curr + prev) % d;
        prev = curr;
        curr = tmp;
        if(i == num){
            return -(prev);
        }

        if(len > i){
            *(pisanos + i) = tmp;
        }

        

        if(curr == 1 && prev == 0){
            return i + 1;
        }
    }
    return 0;
}


int main(void){
    long long num = 0, len = 0;
    scanf("%lld%lld", &num, &len);

    if (num <= 1) {
        printf("1\n");
        return 0;
    }

    int len_p = 50000;
    long long pisanos[50000] = {0};
    long long d = power(10, len);
    long long p = pisanoPeriod(d, num, pisanos, len_p);

    if(p < 1){
        printf("%lld", -p);
        return 0;
    }



    if (p == -1) {
        p = num + 1;
    }


    num %= p;
    // printf("%lld -p \n", num);
    long long prev = 1, curr = 1;

    if(num == 0){
        return 0;
    }else if (num == 1){
        return 1;
    }else{
        printf("%lld\n", *(pisanos + num -1));
        // for(long long i = 2; i <= num; i++){
        //     long long tmp = (curr + prev) % d;
        //     prev = curr;
        //     curr = tmp;
        // }
    }
    return 0;
}


