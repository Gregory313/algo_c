#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const pair<long, long>&a, const pair<long, long>&b){
    return a.first > b.first;
}


int main(){
    long max_mass, heap_count;
    cin >> max_mass >> heap_count;

    vector<pair<long, long>> heaps(heap_count);
    
    for(long i = 0; i < heap_count; i++){
        cin >> heaps[i].first >> heaps[i].second;
    }
    
    sort(heaps.begin(), heaps.end(), cmp);

    long sum = 0;

    for (long i = 0; i < heaps.size(); i++){   
        if(max_mass == 0) break;
        
        if(heaps[i].second <= max_mass){
            max_mass -= heaps[i].second;
            sum += (heaps[i].first * heaps[i].second);
        }else{
            sum += (heaps[i].first * max_mass);
            max_mass = 0;
        }    
    }
    

    cout << sum << endl;


    return 0;
}