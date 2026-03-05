/*

https://contest.yandex.ru/contest/25070/run-report/144685991/

-- ПРИНЦИП РАБОТЫ --

Алгоритм использует поиск в глубину для обхода компонент связности в сетке.
Изначальная сетка хранится в формате строк, чтобы ускорить обработку и не использовать лишнюю память
все вычисления происходять на исходной таблице. Начальный цикл гарантирует, что функция в начало
всегда будет получать # . Начиная от входной ячейи проходим остальные и для кажждой проверяем соседей
. DFS помечает все связанные ячейки как посещенные и считает их количество. 
После прохода проверяем размер текущей компоненты с максимальной.
В данной реализации используется итеративнй подход так как возможны большие входные данные, также 
был проведено сравнение между обходом в глубину и в ширину, как ожидалось обход в глубину 
быстрее, однако тратит больше памяти  чем обод в ширину.


-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
    l - ширина h - высота
    v - l * h
    e - 4 * l * h (4 соседа в худш случае)
    DFS O(v + e) 
    Итоговая сложность O(l * h)
    

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
    O(l * h) массив visited
    O(l * h) стек в худшем случае

    Итоговая сложность O(l * h)
*/




#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;




void FindNeighbours(vector<string>& grid, int x, int y, int l, int h, stack<int>& holder, vector<int>& visited){

    auto checkPush = [&](int v_x, int v_y){
        if (v_y >= 0 && v_y < h && v_x >= 0 && v_x < l  && grid[v_y][v_x] == '#' && !visited[v_y * l + v_x]){
            holder.push(v_y * l + v_x);
            visited[v_y * l + v_x] = 1;
        }
    };


    checkPush(x, y - 1);
    checkPush(x, y + 1);
    checkPush(x - 1, y);
    checkPush(x + 1, y);


}

int DFS(vector<string>& grid, int x, int y, int l, int h, vector<int>& visited){
    int sum = 0;
    stack<int> holder;
    
    int start = y * l + x;
    visited[start] = 1;
    holder.push(start);

    while(!holder.empty()){
        int v = holder.top();
        sum++;
        holder.pop();

        FindNeighbours(grid, v % l, v / l, l, h, holder, visited);
    }
    return sum;
}


int main(){
    int h, l;
    cin >> h >> l;
    cin.ignore();
    vector<string> grid(h);

    for(int i = 0; i < h; i++){
       getline(cin, grid[i]);
    }



    vector<int> visited(l * h, 0);
    int sum = 0;
    int count = 0;
    
    for(int y = 0; y < h; y++){
        for(int x = 0; x < l; x++){
            if(visited[y * l + x] == 1 || grid[y][x] != '#') continue;
            int l_sum = DFS(grid, x, y, l, h, visited);
            count++;
            sum = max(l_sum, sum);
        }
    }
    
    cout << count << " " << sum << endl;
    return 0;
}