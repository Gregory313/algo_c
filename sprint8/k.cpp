#include <iostream>
#include <vector>

using namespace std;

int main(){
    string str1;
    string str2;

    getline(cin, str1);
    getline(cin, str2);

    if (abs((int)str1.size() - (int)str2.size()) > 2) {
       cout << "FAIL" << endl; 
    }
    
    string long_str;
    string short_str;
    int f_count = 0;


    if(str1.size() > str2.size()){
        long_str = str1;
        short_str = str2;
    }else{
        long_str = str2;
        short_str = str1;
    }  

    int len_long = long_str.size();
    int len_short = short_str.size();
    
    int i = 0;
    int j = 0;

    while(len_long > i && len_short > j){
        if(long_str[i] != short_str[j]){
            f_count++;
            if(f_count >= 2) break;

            if(i + 1 < len_long){
                if(short_str[j] == long_str[i + 1]){
                    i++;
                }else{
                    i++;
                    j++;
                }
            }else{
                break;
            }
        }else{
            i++;
            j++;
        }
    }

    if(i != len_long || j != len_short){
        f_count++;
    }

    if(f_count >= 2){
        cout << "FAIL" << endl;
        return 0;
    }else{
        cout << "OK" << endl;
    }


    return 0;
}