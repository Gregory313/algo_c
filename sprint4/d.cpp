#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

long long* hashStr(int len, const char* str, long long a, long long m){
    long long* pref_arr = (long long*)calloc(len + 1, sizeof(long long));
    long long hash = 0;
    
    for(int i = 0; i < len; i++){
        hash = (hash * a + str[i]) % m;
        *(pref_arr + i + 1) = hash;
    }
    return pref_arr;
}



long long countHash(int l, int r, long long* pref_arr, long long a, long long m, vector<long long> &p_pow){
    long long hash = 0; 
    hash = (*(pref_arr + r) - *(pref_arr + l - 1) * p_pow[r + 1 - l] % m + m) % m;
    return hash;
}

int main(void){
    long long a, m, req, l, r;
    string text;

    cin >> a;
    cin >> m;
    cin >> text;
    cin >> req;

    vector<long long> p_pow(text.length() + 1);
    p_pow[0] = 1;

    for (int i = 1; i <= text.length(); ++i) {
        p_pow[i] = (p_pow[i-1] * a) % m;
    }


    long long *pref_arr = hashStr(text.length(), text.c_str(), a, m);

    for (int i = 0; i < req; i++){
        cin >> l;
        cin >> r;
        long long hash = countHash(l, r, pref_arr, a, m, p_pow);
        cout << hash << endl;
    }

    free(pref_arr);
    exit(EXIT_SUCCESS);
}