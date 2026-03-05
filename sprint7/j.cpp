#include <iostream>
#include <vector>

using namespace std;

int main(){
    int len = 0;
    cin >> len;

    vector<int> holder(len, 0);
    for(int i = 0; i < len; i++){
        cin >> holder[i];
    }

    vector<int> dp(len, 1);

    for(int i = 1; i < len; i++){
        int max_v = 1;
        int curr_idx = i;
        for(int j = i - 1; j >= 0; j--){
            if(holder[curr_idx] > holder[j] && max_v <= dp[j]){
                max_v= dp[j] + 1;
            }
        }
        dp[i] = max(max_v, dp[i]);
    }

    int answer = 0;
    int idx = 0;
    for (int i = 0; i < len; i++) {
            if (dp[i] > answer) {
                answer = dp[i];
                idx = i;
            }
        }

    cout << answer << endl;
    vector<int> path;
    path.push_back(idx + 1);

    answer--;
    idx--;
    while(answer > 0 && idx >= 0){
        if(answer == dp[idx]){
            answer -= 1;
            path.push_back(idx + 1);
        }
        idx--;
    }

    for(int i = 0; i < path.size(); i++){
        cout << path[path.size() - 1 - i] << " ";
    }
    cout << endl;

    return 0;
}