#include <iostream>
#include <vector>


using namespace std;


int main(){
    string str;
    string sub_str;
    string new_sub_str;

    getline(cin, str);
    getline(cin, sub_str);
    getline(cin, new_sub_str);

    vector<int> dp(sub_str.size(), 0);

    int j = 0;
    for(int i = 1; i < sub_str.size(); i++){
        while(j != 0 && sub_str[i] != sub_str[j]){
            j = dp[j - 1];
        }

        if(sub_str[i] == sub_str[j]){
            j++;
        }
        dp[i] = j;    
    }


    string new_str;
    for(int i = 0; i < str.size(); i++){
        while(j != 0 && str[i] != sub_str[j]){
            j = dp[j - 1];
        }

        new_str += str[i];

        if(str[i] == sub_str[j]){
            j++;
            if(j == sub_str.size()){
                new_str.erase(new_str.size() - j, j);
                new_str += new_sub_str;
                j = 0;
                continue;
            }
        }
    }

    for(int i = 0; i < new_str.size(); i++){
        cout << new_str[i];
    }
    cout << endl;
    return 0;
}