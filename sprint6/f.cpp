#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;



void DFSrSort(vector<vector<int>>& graph, int v, vector<int>& visited, vector<int>& order){
    visited[v] = 1;
    for(int to : graph[v]){
        if(visited[to] == 0){
            DFSrSort(graph, to, visited, order);
        }
    }
    order.push_back(v);
}



int main(){
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    vector<int> visited(n, 0);
    vector<int> order;
    order.reserve(n);

    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        graph[v - 1].push_back(u - 1);
    }


    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            DFSrSort(graph, i, visited, order);
        }
    }


    for(int v : order){
        cout << v + 1 << " ";
    }

    return 0;
}



