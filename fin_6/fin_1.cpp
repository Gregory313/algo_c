/*
https://contest.yandex.ru/contest/25070/run-report/144682466/



-- ПРИНЦИП РАБОТЫ --

Реализован поиск максимального оставного дерева на основе алгоритма Прима.

Для реаилзации алогоритма необходимо начать с любой вершины, выбрать наименьшее ребро,
добавить в граф. 
Так как при прямой реализации необходимо знать наибольшее ребро, это можно реалзивать поиском максимума массива
однако сложность максимума  O(все ребра), а если использовать приоритетную очередь, основанную на куче,
тогда сложность будет O(все ребра log все ребра)

Так же во избежания дублирования вершин использовалась хеш табилца, так как она быстрая, O(1) операции вставки, удаления (и сортировка не нужна), 
в сравнениие с set основанным на бинраном дереве поиска.

основной цикл строится на данных в очереди. При добавлении первой вершины добавляются в очередь все дочерние ее узлы,
с условием что таких узлов мы еще не рассматривали. Извлекается верхнее (большее) ребро.
Проверка на то что данное ребро с вершиной не были рассмотрены (т.к. на вершине может остаться ребро рассмотренной верщины),суммирование весов. 
Когда очередь заканчена, проверка на то что все узлы были проверены, если условие не выполняется, значит в графе несколько компонет связности.



-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
    Е - ребра V - вершины
    вставка (в хеш таблицу посещенного узла) O(V) 
    удаление O(V) (из хеш таблицы посещенного узла) 
    вставка в приоритетную очередь (E * O log E)
    проверка ребра O(E)
    Итоговая сложность O(V) + O(E * logE ) +  O(E) + 0(V) = O(E * logE)


-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
    Итоговая сложность 2 * (хеш таблица O(V)) + очередь O(E) = O(E + V)
    

*/







#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;


struct Edge{
    int weight;
    int to;

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};


typedef vector<vector<Edge>> Graph;


class MST{
private:
    priority_queue<Edge> pq;
    unordered_set<int> not_visited;
    unordered_set<int> visited;

public:
    void addVertex(Graph &graph, int v){
        not_visited.erase(v);
        visited.insert(v);

        for(auto& edge : graph[v]){
            if(!visited.count(edge.to) > 0){
                pq.push(edge);
            }
        }
    }
        
    void updateSP(Graph &graph, int &sum){
        Edge cur_edge = pq.top();
        pq.pop();

        if(not_visited.count(cur_edge.to) > 0){
            sum += cur_edge.weight;
            addVertex(graph, cur_edge.to);
        }
    }

    int maxSP(Graph &graph){
    int sum = 0;
    for(int i = 0; i < graph.size(); i++){
        not_visited.insert(i);
    }

    addVertex(graph, 0);

    while(!pq.empty()){
        updateSP(graph, sum);
    }

    if(not_visited.size() > 0){
        return -1;
    }

    return sum;
}



};





int main(){
   int n, m;
   cin >> n >> m;

   MST mst;
   Graph graph(n);

   for(int i = 0; i < m; i++){
    int u, v, w;
    cin >> u >> v >> w;
    graph[u - 1].push_back({w, v - 1});
    graph[v - 1].push_back({w, u - 1});  
   }


   int sum = mst.maxSP(graph);

   if(sum == -1){
    cout << "Oops! I did it again" << endl;
   }else{
    cout << sum << endl; 
   }

    return 0;
}