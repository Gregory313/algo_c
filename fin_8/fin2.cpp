/*
https://contest.yandex.ru/contest/26133/run-report/147765236/

-- ПРИНЦИП РАБОТЫ --
    По условию задачи необходимо определить что строка состоит из подстрок из словаря
    Для решения задачи использовалась струкруа данных префиксное дерерво.
    На основе слов из словаря создается дерево.
    Выполнятеся рекурсивный поиск по деереву с мемоизацей,
    при нахождении слова рекусивно вызывается новый поиск от текущей позиции в строке.
    Мемоизации сохраняет пройденные позиции.

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
    n - кол-во слов в словре
    l - длина слова
    m - длина строки
    посторение дерева (n * l) + поиск(m * l) = итоговая сложность О(n * l + m * l)

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
    дерево O(m * l) + мемоизация O(m) + рекурсия O(m) = итоговая сложность O(n * l + m)
*/



#include <iostream>
#include <vector>
#include <map>
#include <memory>

using namespace std;

typedef struct Trie{
    map<char, unique_ptr<Trie>> children;
    bool isTerminal = false;
};

void createTrie(Trie *root, string& word){
    Trie *curr = root;
    int i = 0;
    while(i < word.size() - 1){
        char curr_symbol = word[i];
        auto& curr_node = curr->children[curr_symbol];
        if(!curr_node){
            curr_node = make_unique<Trie>();
        }
        curr = curr_node.get();
        i++;
    }

    auto& curr_node = curr->children[word[word.size() - 1]];
    if(!curr_node) curr_node = make_unique<Trie>();
    curr_node->isTerminal = true;

}



bool findWordTrie(Trie *root, string& text, int curr_start, vector<int>& memo){
    if(curr_start == text.size()) return true;
    if(memo[curr_start] != -1) return (memo[curr_start]);
    Trie *curr = root;
    for(int i = curr_start; i < text.size(); i++){   
        char curr_symbol = text[i];
        auto curr_node = curr->children.find(text[i]);
        if(curr_node == curr->children.end()){
            memo[curr_start] = 0;
            return false;
        }
        curr = curr_node->second.get();

        if(curr->isTerminal){
            if(findWordTrie(root, text, i + 1, memo)){ 
                memo[curr_start] = 1;
                return true;
            }
        }

    }
    return false;
}


int main(){
    int word_count;
    string text;
    getline(cin, text);
    cin >> word_count;
    auto root = make_unique<Trie>();

    for(int i = 0; i < word_count; i++){
        string tmp;
        cin >> tmp;
        createTrie(root.get(),tmp);
    }

    vector<int> memo(text.size(), -1);
    if(findWordTrie(root.get(), text, 0, memo)){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }

    return 0;
}