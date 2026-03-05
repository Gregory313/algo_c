/*
https://contest.yandex.ru/contest/24810/run-report/143360583/



-- ПРИНЦИП РАБОТЫ --

Реализована сортировка пирамидой.
Для реализации сортиорвки необходимо было построить пирамиду невозрастующую (кучу)
После прочтения всех элементов массива, выполнена проверка только узлов с детьми, 
так как по св-ву кучи родительский узел должен быть больше детей, 
потому проверка таких узлов позволит сократить количетсво и создать кучу.
После добавления узлов был создан новый массив, который  получает значения начиная с корня.
Корень меняется с крайним узлом и происходит балансировка через siftDown, которая на основе компратора,
определяет порядок расстановки узлов. 

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
    построение массива - o(1)
    создание кучи (sift down) - o(n * log n)
    балансировка после удаления корня (sift down) - o(n * log n)


-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
    дублирование массива o(n)

*/



#include <iostream>
#include <string>
#include <vector>

using namespace std;


typedef struct Node{
    string login = "";
    int ex_count = -1;
    int miss_count = -1;
    Node(string login, int ex_count, int miss_count) : login(login),  ex_count(ex_count), miss_count(miss_count) {}
    Node() = default; 
}Node;



bool cmp(Node& a, Node& b){
    if(a.ex_count != b.ex_count){
        return a.ex_count > b.ex_count;
    }

    if(a.miss_count != b.miss_count){
        return a.miss_count < b.miss_count;
    }

    return a.login < b.login;
}



void siftDown(vector<Node>& heap, int idx){
    if(idx > heap.size()) return;    
    int max_idx = idx;
    int l_idx = idx * 2 + 1;
    int r_idx = l_idx + 1;

    for(;;){
        if(heap.size() > l_idx && cmp(heap[l_idx], heap[max_idx])) max_idx = l_idx;
        if(heap.size() > r_idx && cmp(heap[r_idx], heap[max_idx])) max_idx = r_idx;
        
        if(max_idx != idx){ 
            swap(heap[idx], heap[max_idx]);
            idx = max_idx;
        }else{
            return;
        }

        l_idx = max_idx * 2 + 1;
        r_idx = l_idx + 1;
    }
}
 
int main(void){

    int len = 0;
    cin >> len;

    vector<Node> heap;
    vector<Node> s_heap;

    for(int i = 0; i <len; i++){
        Node tmp;
        cin >> tmp.login >> tmp.ex_count >> tmp.miss_count;
        heap.push_back(tmp);
        // siftUp(heap, i);
    }

    for(int i = len / 2 - 1; i >= 0; i--){
        siftDown(heap, i);
    }

    while(heap.size() >= 1){
        Node tmp = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(heap, 0);
        s_heap.push_back(tmp);
    }



    for(int i = 0; i < len; i++){ 
        cout << s_heap[i].login << endl; 
    }


    return 0;
}
