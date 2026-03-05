#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


bool compareBySecond(const pair<float, float>& a, const pair<float, float>& b) {
    if(a.second != b.second) return a.second < b.second;
    return a.first < b.first;
    
}

int main(){
    int lessons_count;
    cin >> lessons_count;

    vector<pair<float, float>> timetable(lessons_count);
    
    for(int i = 0; i < lessons_count; i++){
        cin >> timetable[i].first >> timetable[i].second;
    }
    
    sort(timetable.begin(), timetable.end(), compareBySecond);

    vector<int> lessons;
    float time_end = timetable[0].second;
    lessons.push_back(0);

    for(int i = 1; i < lessons_count; i++){ 
        if(timetable[i].first >= time_end){
            time_end = timetable[i].second;
            lessons.push_back(i);
        }
        
        // cout << timetable[i].first << " " << timetable[i].second << " " << timetable[i].second - timetable[i].first << endl;
    }

    cout << lessons.size() << endl;
    for(int i = 0; i < lessons.size(); i++){
        cout << timetable[lessons[i]].first << " " << timetable[lessons[i]].second << endl;
    }

    return 0;
}