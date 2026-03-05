/*
https://contest.yandex.ru/contest/24810/run-report/143360810/



-- ПРИНЦИП РАБОТЫ --

Реализовано удаление узла в бинарном дереве поиска (БДП) на основе рекурсии
Для удаления узла необходимо было найти удаляемый узел.
определить кол-во детей
изменить значение 
заменить ссылки дочерних и родительского объектов

Для упрощения работы с родителем использовалась рекурсия. 
Фуникция удаления реализует поиск по значению нужного узла.
При нахождении узла определялось количество дочерних обьектов.
Если узел имел только одного потомка или не имеет их вообще,
то он попадет в одно из условий, на удаление текущего узла и вставку обратного условию узла
Иначе будет реализован поиск наименьшего значения в правой ветке 
(которому соответсвует самое левое значение)
далее на место удаляемого узла запишется значение крайнего узла правой ветки
а вызовется функция для удаления этого (крайнего левого) узла в правой подветке
и вернет ссылку на новый узел (null)



-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
    h-высота дерева
    n-колво узлов

    поиск узла по ключу o(log h) 
    удаление узла o(log h) в худш - o(n) 


-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
    o(h) рекурсия


*/




#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  Node* left = nullptr;  
  Node* right = nullptr;
  Node(Node* left, Node* right, int value) : value(value), left(left), right(right) {}
};  
#endif
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <cassert>



Node *findRightBorderNode(Node *root){ 
    Node *tmp;
    while(root){
        tmp = root;
        root = root->right;
    }
    return tmp;
}


Node* remove(Node* root, int key) {
    if(!root) return nullptr;

    if(root->value > key){
        root->left = remove(root->left, key);
    }else if(root->value < key){
        root->right = remove(root->right, key);
    }else{
        if(!root->left){
            Node *tmp = root->right;
            return tmp;
        }else if(!root->right){
            Node *tmp = root->left;
            return tmp;
        }

        Node *tmp = findRightBorderNode(root->left);
        root->value = tmp->value;
        root->left = remove(root->left, tmp->value);
    }
    return root;
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    Node node3({nullptr, &node2, 1});
    Node node4({nullptr, nullptr, 6});
    Node node5({&node4, nullptr, 8});
    Node node6({&node5, nullptr, 10});
    Node node7({&node3, &node6, 5});
    Node* newHead = remove(&node7, 10);
    assert(newHead->value == 5);
    assert(newHead->right == &node5);
    assert(newHead->right->value == 8);
}

int main() {
  test();
}
#endif
