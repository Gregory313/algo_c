#include <iostream>
#include <unordered_map>
using namespace std;


int countMaxLen(int *tmp, int len){
    unordered_map<int, int> pref_sum;
    int max_len = 0;
    pref_sum[0] = -1;

    int cur_sum = 0;

    for(size_t j = 0; j < len; j++){
        cur_sum += (*(tmp + j) == 0) ? -1 : 1;

        if(pref_sum.count(cur_sum)){
            int curr_len = j - pref_sum[cur_sum];
            if(curr_len > max_len){
                max_len = curr_len;
            }
        }else{
            pref_sum[cur_sum] = j;
        }
    }
    return max_len;
}


int main(){
    int len;
    scanf("%d\n", &len);
    int i = 0;
    int *arr = (int*)malloc(sizeof(int) * len);

    while(i < len && scanf("%d", (arr + i)) == 1){
        i++;
    }
    int max_len = countMaxLen(arr, len);


    cout << max_len << endl;

    free(arr);
    // free(tmp);
    return 0;
}