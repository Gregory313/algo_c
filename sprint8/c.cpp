#include <iostream>
#include <vector>
#include <stack>


using namespace std;


int main(){
    int num = 0;
    cin >> num;
    
    vector<string> holder(num);

    for(int i = 0; i < num; i++){
        cin >> holder[i];    
    }

    bool isStop = false;
    int idx = 0;
    string pref;
    while(!isStop){
      char ps = '\0';
      bool match = true;
      for(int i = 0; i < num; i++){
        if(idx == holder[i].size()){ isStop = true; break; }
        char cs = holder[i][idx];
        if(ps == '\0'){
            ps = cs;
        }else if(ps != cs){
            match = false;
            isStop = true;
            break;
        }
      }
      if(!isStop && match){
        pref += ps;
      }
      idx++;  
    }

    cout << pref.size() << endl;


    return 0;
}