#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

typedef struct Node{
    int vertex;
    struct Node *next;
};


struct List{
    Node *top;
};


void DFS(vector<List>& graph, int n, int start = 0){
    vector<int> clrs(n, 0);
    vector<int> entry(n, 0);
    vector<int> leave(n, 0);

    stack<int> holder;
    holder.push(start);
    int count = 0;
    while(!holder.empty()){
        int v = holder.top();
        holder.pop();

        if(clrs[v] == 0){
            entry[v] = count;
            clrs[v] = 1;
            holder.push(v);

            vector<int> vertices;
            
            Node *curr = graph[v].top;
            while(curr){
                int tmp_v = curr->vertex - 1;  
               vertices.push_back(tmp_v);
               curr = curr->next;
            }
            sort(vertices.rbegin(), vertices.rend());
            for(int w : vertices){
                if (clrs[w] == 0) holder.push(w);
            }
            count++;   
        }else if(clrs[v] == 1){
            clrs[v] = 2;
            leave[v] = count;
            count++;   
        }       
    }


    for(int i = 0; i < n; i++){
        cout << entry[i] << " " << leave[i] << endl;
    }
    
}


int main(){
    int n, m;
    cin >> n >> m;

    vector<List> graph(n);


    for(int i = 0; i < m; i++){
        Node *tmp = new Node;
        int u, v;
        cin >> u >> v;
        tmp->vertex = v;
        tmp->next = graph[u - 1].top;
        graph[u - 1].top = tmp;
    }

    DFS(graph, n);

    return 0;
}



