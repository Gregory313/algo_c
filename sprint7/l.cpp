#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void){
    int n, m;
    cin >> n >> m;

    m += 1;
    
    vector<vector<int>> dp(n);
    vector<int> nums(n, 0);

    for(int i = 0; i < n; i++){
        cin >> nums[i]; 
    }

    for(int i = 0; i < m; i++){
        int acc_idx = 1;
        dp[0].push_back(0);
        while(acc_idx * nums[0] <= i){
            dp[0][i] = acc_idx * nums[0];
            acc_idx += 1;
        }   
    }

    for(int i = 1; i < n; i++){
        for (int j = 0; j < m; j++){
            dp[i].push_back(0);
            if(j == 0){
                continue;
            }
            int n_val = 0;

            if(j >= nums[i]){
                n_val = nums[i] + dp[i - 1][j - nums[i]];
            }   


            dp[i][j] = (max(dp[i - 1][j], n_val));
        }
    }

    cout << dp[n - 1][m - 1] << endl;

    return 0;
}