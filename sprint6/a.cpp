#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

#include <iostream>
using namespace std;

typedef struct Node{
    int vertex = 0;
    struct Node *next;
}Node;


typedef struct List{
    Node *top;
    int num;

    List() : top(NULL), num(0) {}
}List;


int main(void){
    int len = 0; 
    int n, m;

    cin >> n >> m;

    vector<List> graph(n);

    for(int i = 0; i < m; i++){
        int idx;
        int vertex;
        cin >> idx >> vertex;
        Node *tmp = new Node;
        tmp->vertex = vertex;
        tmp->next = graph[idx - 1].top;
        graph[idx - 1].top = tmp;
        graph[idx - 1].num++;
    }   

    for(int i = 0; i < n; i++){
        cout << graph[i].num << " ";


        if(graph[i].top == NULL){ cout << endl; continue;}

        vector<int> vertices;
        Node* current = graph[i].top;
        while (current != NULL) {
            vertices.push_back(current->vertex);
            current = current->next;
        }
        sort(vertices.begin(), vertices.end());

        for (int v : vertices) {
            cout << v << " ";
        }
        cout << endl;
        

        // while(graph[i].top){
        //     cout << graph[i].top->vertex << " ";
        //     graph[i].top = graph[i].top->next;
        // }
        // cout << endl;
    }

    return 0;
}
