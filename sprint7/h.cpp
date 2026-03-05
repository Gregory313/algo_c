#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int n, m;

    cin >> n >> m;
    vector<string> grid(n);
    cin.ignore();

    for(int i = 0; i < n; i++){
        getline(cin, grid[i]);
    }

    vector<vector<int>> dp(n);

    for(int i = n - 1; i >= 0; i--){
        for (size_t j = 0; j < m; j++){
           int left = 0, down = 0;
            if(j != 0){
                left = dp[i][j - 1];
            }

            if(i != (n - 1)){
                down = dp[i + 1][j];
            }
            dp[i].push_back(max(left, down) + (grid[i][j] - '0'));           
        }
    }

    vector<int> path;



    cout << dp[0][m - 1] << endl;

    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < m; j++){
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    int height = 0;
    int length = m - 1;

    while( height <= n - 1 && length > 0){
        while(length != 0 && (dp[height][length] - dp[height][length - 1]) == grid[height][length] - '0'){
            path.push_back(0);
            length--;
        }

        while(height != n - 1 && (dp[height][length] - dp[height + 1][length]) == grid[height][length] - '0'){
            path.push_back(1);
            height++;
        }

        if(length == 0 && height != n - 1){
            length = m - 1;
        }
    }   


    for(int i = path.size() - 1; i >= 0; i--){
        if(path[i] == 0){
            cout << "R";
        }else{
            cout << "U";
        }
    }


    return 0;
}