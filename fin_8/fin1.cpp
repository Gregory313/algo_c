/*
https://contest.yandex.ru/contest/26133/run-report/147810590/

-- ПРИНЦИП РАБОТЫ --
    По условию задачи необходимо вычислить наибольший общий префикс. 
    Строка распаковывается, обьеденяется в  одну и прямым прохождением 
    сравниваются префиксы строк

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
    n - длина строки
    m - множители
    l - длина строки
    итоговая сложность O(l)

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
    l - глубина вложенности    
    итоговая сложность O(l)
*/


#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

string unpack(const string& s) {
    stack<pair<int, string>> st;
    string curr;
    
    for (char c : s) {
        if (isdigit(c)) {
            st.push({c - '0', curr});
            curr = "";
        } else if (c == ']') {
            auto [count, prev] = st.top();
            st.pop();
            string tmp = curr;
            curr = prev;
            for (int i = 0; i < count; i++) {
                curr += tmp;
            }
        } else if (c != '[') {
            curr += c;
        }
    }
    
    return curr;
}

string findPref(vector<string>& str) {    
    vector<string> full_str;
    for (const auto& s : str) {
        full_str.push_back(unpack(s));
    }
    
    string pref = full_str[0];
    for (int i = 1; i < full_str.size(); i++) {
        int j = 0;
        while (j < pref.size() && j < full_str[i].size() && pref[j] == full_str[i][j]) {
            j++;
        }
        pref = pref.substr(0, j);
    }
    
    return pref;
}

int main() {    
    int str_count;
    cin >> str_count;
    
    vector<string> str(str_count);
    for (int i = 0; i < str_count; i++) {
        cin >> str[i];
    }
    
    string res = findPref(str);
    cout << res << endl;
    
    return 0;
}
