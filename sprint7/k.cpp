#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int len1, len2;

    cin >> len1;
    len1++;
    vector<int> arr1(len1, 0);

    for(int i = 1; i < len1; i++){
        int a = 0;
        cin >> a; 
        arr1[i] = a; 
    }

    cin >> len2;
    len2++;
    vector<int> arr2(len2, 0);

    for(int i = 1; i < len2; i++){
       int a = 0;
       cin >> a;
       arr2[i] = a; 
    }

    vector<vector<int>> mat_dp(len1, vector<int>(len2, 0));

    for(int i = 1; i < len1; i++){
        int v = 0;
        for(int j = 1; j < len2; j++){
            if(arr1[i] == arr2[j]){
              v = mat_dp[i - 1][j - 1] + 1;  
            }else{
              v = max(mat_dp[i - 1][j], mat_dp[i][j - 1]);
            }
            mat_dp[i][j] = v;
        }
    }

    cout << mat_dp[len1 - 1][len2 - 1] << endl;

    vector<pair<int, int>> path;
    int len1_idx = len1 - 1;
    int len2_idx = len2 - 1;
    
    while(len1_idx > 0 && len2_idx > 0){
        if(arr1[len1_idx] == arr2[len2_idx]){
            path.push_back({len1_idx, len2_idx});
            len1_idx--;
            len2_idx--;
        }else{
            if(mat_dp[len1_idx][len2_idx] == mat_dp[len1_idx - 1][len2_idx]){
                len1_idx--;
            }
            
            if(mat_dp[len1_idx][len2_idx] == mat_dp[len1_idx][len2_idx - 1] && len1_idx > 0){
                len2_idx--;
            }
        }
    }

    reverse(path.begin(), path.end());

    for(int i = 0; i < path.size(); i++){
        cout << path[i].first << " ";
    }
    cout << endl;

    for(int i = 0; i < path.size(); i++){
        cout << path[i].second << " ";
    }

    return 0;
}