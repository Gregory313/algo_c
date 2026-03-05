#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define FNV_PRIME_32 16777619
#define FNV_OFFSET_32 2166136261U

unsigned long hash_fnv1a(const char *str) {
    unsigned long hash = FNV_OFFSET_32;
    int c;

    while ((c = *str++)) {
        hash ^= c;
        hash *= FNV_PRIME_32;
    }

    return hash;
}

int hashObj(const char *el, unsigned long* h_arr, int *len_hash){
    unsigned long hash = hash_fnv1a(el);//str_len;
    for(int i = 0; i < *len_hash; i++){
        if( *(h_arr + i) == hash){
            return 1;
        }
    }

    *(h_arr + *len_hash) = hash;
    (*len_hash)++;
    return 0;    
}

int main(void){
    int len = 0;
    scanf("%d\n", &len);

    char **lines = (char**)malloc(sizeof(char*) * len);    
    unsigned long *hash_holder = (unsigned long*)malloc(sizeof(unsigned long) * len);
    char *bffr = (char*)malloc(sizeof(char) * (1000 + 1));

    int i = 0, h_len = 0;
    while(fgets(bffr, 1000, stdin) != NULL){
        bffr[strcspn(bffr, "\n")] = '\0';
        int len_str = strlen(bffr);
        int rc = hashObj(bffr, hash_holder, &h_len);
        if(rc == 0){
            *(lines + i) = (char*)malloc(sizeof(char) * (len_str + 1));

            // printf("%s %s\n",*(lines + i), bffr);
            strncpy(*(lines + i), bffr, len_str);
            *(*(lines + i) + len_str) = '\0';
            i++;
        }
    }
    // printf("\n");
    // printf("\n");
    // printf("\n");

    for(int i = 0; i < h_len; i++){

        printf("%s\n",*(lines + i));
        // printf(" %ld %s \n", *(hash_holder + i), *(lines + i));
    }

    exit(EXIT_SUCCESS);
}