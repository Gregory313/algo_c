#include <iostream>
#include <cmath>
#include <string.h>

int main(){

    long long a, m;
    scanf("%lld\n%lld\n", &a, &m);

    
    char *string = (char*)malloc(sizeof(char) * 100000000);
    fgets(string, 100000000, stdin);

    string[strcspn(string, "\n")] = 0;

    int len = strlen(string);

    // printf("%d %d \n%s \n%d\n", a, m, string, strlen(string));

    // printf("%d\n", len);

    long long hash = 0;
    for(int i = 0; i < len; i++){
        hash = (hash * a + *(string + i)) % m;
        
    }

    printf("%lld ", hash);

    return 0;
}