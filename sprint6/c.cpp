#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

typedef struct Node{
    int vertex;
    struct Node *next;
}Node;

typedef struct List{
    int num;
    Node *top;
    List() : num(0), top(nullptr) {}
};

using namespace std;


void DFS(vector<List>& graph, vector<int>& clr, int start){
    stack<int> holder;
    holder.push(start);

    while(!holder.empty()){
        int v = holder.top();
        holder.pop();

        if(clr[v] == 0){
            cout << v + 1 << " ";  
            clr[v] = 1;
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
                if (clr[w] == 0) holder.push(w);
            }

        }else if(clr[v] == 1){          
            clr[v] = 2;
        }
    }
}


int main(){
    int n, m;
    cin >> n >> m;

    vector<List> graph(n);
    vector<int> clrs(n, 0);

    for (size_t i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        
        Node *tmp1 = new Node;
        tmp1->vertex = v;
        tmp1->next = graph[u - 1].top;
        graph[u - 1].top = tmp1;
        graph[u - 1].num++;
        
        Node *tmp2 = new Node;
        tmp2->vertex = u;
        tmp2->next = graph[v - 1].top;
        graph[v - 1].top = tmp2;
        graph[v - 1].num++;
    }
    
    
    int start;
    cin >> start;

    DFS(graph, clrs, start - 1);


    return 0;
}