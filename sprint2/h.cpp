#include <iostream>
#include <vector>
#include <stack>


using namespace std;


int main(){
    string bffr;
    cin >> bffr;
    stack<char> holder;
    for(int i = 0; i < bffr.size(); i++){
        char symbol = bffr[i];
        if(symbol == ')'){
            if(!holder.empty() && ((int)(holder.top() + 1) == (int)symbol)){
                holder.pop();
            }else{
                cout << "False" << endl;
                return 0;
                break;
            }
        }else if(!holder.empty() && (symbol == '}' || symbol == ']')){
            // cout << holder.top() << " " << symbol << endl;
            if((int)holder.top() + 2 == symbol){
                holder.pop();
            }else{
                cout << "False" << endl;
                return 0;
                break;
            }
        }else{
            holder.push(symbol);
        }
    } 

    // cout << holder.size() << endl;
    // for(int i = 0; i < holder.size(); i++){
    //     cout << holder.top() << endl;
    //     holder.pop();
    // }
    if(!holder.size()){
        cout << "True" << endl;
    }else{
        cout << "False" << endl;
    }

    return 0;
}