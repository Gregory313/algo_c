#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>



using namespace std;

void bfs(vector<vector<int>>& graph, int start){
    queue<int> holder;
    holder.push(start);

    vector<int> clr(graph.size(), 0); 

    while(!holder.empty()){
        int v = holder.front();
        holder.pop();
        
        if (clr[v] == 1) continue; 

        cout << v + 1 << " ";
        clr[v] = 1;

        vector<int> vertices = graph[v];
        sort(vertices.begin(), vertices.end());

        for(int child_v : vertices){
            if(clr[child_v] == 0){
                holder.push(child_v);
            } 
        }

    }
    return;
}



int main(){
    int m, n;
    cin >> n >> m;

    vector<vector<int>> graph(n);

    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        graph[v - 1].push_back(u - 1);
        graph[u - 1].push_back(v - 1);
    }

    int start;
    cin >> start;

    bfs(graph, start - 1);


    return 0;
}

