#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    string str;
    getline(cin, str);    

    vector<int> dp(str.size(), 0);
    int j = 0;

    for(int i = 1; i < str.size(); i++){
       while(j != 0 && str[i] != str[j]){
            j = dp[j - 1];
       }
       if(str[i] == str[j]){
            j++;
       }
       dp[i] = j;
    }
    for(int i = 0; i < dp.size(); i++){
        cout << dp[i]  << " ";
    }
    return 0;
}