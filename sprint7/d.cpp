#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int MOD = 1000000007;

int main(){
    long num;
    cin >> num;

    unsigned long res = 0;
    
    unsigned long long a = 1, b = 1;

    for(int i = 0; i < num; i++){
        unsigned long long tmp = b;
        b += a;
        b %= MOD;
        a = tmp;                 
    } 
    
    cout << a << endl;
    return 0;
}