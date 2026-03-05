#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


int main(){
    vector<string> words;
    string word;

    while(cin >> word){
        words.push_back(word);
    }

	reverse(words.begin(), words.end());

    for (const string& w : words) {
        cout << string(w) << " ";
    }

    return 0;
}