#include <iostream> 
#include <unordered_map> 
#include <vector> 
#include <sstream>  
#include <string> 
#include <map> 
#include <algorithm> 
#include <set>  
#include <iterator> 
 
using namespace std; 
using HolderMap = unordered_map<string, unordered_map<int, int>>; 
 
 
typedef struct Res{ 
    int count; 
    int index_line; 
 
}Res; 
 
bool compareRes(const Res& a, const Res& b) { 
    if(a.count != b.count){ 
        return a.count > b.count; 
    } 
 
    return a.index_line < b.index_line; 
} 
 
 
void initHolder(HolderMap &holder, int n){ 
    string line; 
    int count_n = 0; 
    while(n > count_n && getline(cin, line)){ 
        stringstream ss(line); 
        string word; 
         
        while (ss >> word) { 
            holder[word][count_n]++; 
        } 
        count_n++; 
    } 
} 
 
vector<Res> initLine(HolderMap &holder, string line_m){ 
    vector<Res> results; 
    stringstream ss(line_m);  
    unordered_map<int, int> matches;  
     
    set <string> unique_words{istream_iterator<string>(ss), istream_iterator<string>()}; 
 
    for(const auto& u_word : unique_words){ 
        if(holder.find(u_word) != holder.end()){ 
            for (const auto& pos : holder[u_word]) { 
                matches[pos.first] += pos.second; 
            } 
        } 
    } 
 
    for (const auto& pair : matches) { 
        results.push_back({pair.second, pair.first}); 
    } 
    return results; 
} 
 
 
 
int main(){ 
    HolderMap holder; 
 
    int n, m; 
    scanf("%d", &n); 
    getchar();  
 
    int count_m = 0; 
 
    string line_m; 
 
    initHolder(holder, n); 
 
    scanf("%d", &m); 
    getchar();  
 
      
    while(m > count_m && getline(cin, line_m)){ 
        vector<Res> results = initLine(holder, line_m); 
         
        int len = results.size() ; 
 
        if(len >= 5){ 
            len = 5; 
        } 
         
        partial_sort(results.begin(), results.begin() + len, results.end(), compareRes); 
             
 
        for (int i = 0; i < len; ++i) { 
            cout << results[i].index_line + 1 << " "; 
        } 
        cout << endl; 
    } 
     
     
    return 0; 
} 
