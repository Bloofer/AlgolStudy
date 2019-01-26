#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int solution(int l, vector<int> v) {
    
    // 1. v를 오름 차순으로 정렬함
    sort(v.begin(), v.end());

    // 2. 0부터 l까지의 구간을 조명이 비추는지 확인해야 함.
    // 조건 A) v.front() - d <= 0
    // 조건 B) v.at(i) + d >= v.at(i+1) - d
    // 조건 C) v.back() + d >= l

    bool chk = false;
    int d = 0;

    // 3. 2의 반복을 d를 증가시키면서 해당 조건이 만족되는 경우 반복을 중지할때까지 반복한다.
    while(!chk){
        d++;
    
        for(int i=0; i<v.size(); i++){
            if(i==0) {
                // 맨 앞에 있는 가로등
                if(v.front() - d > 0) {
                    chk = false;
                    break;
                } else chk = true;
            } else if(i==v.size()-1) {
                // 맨 뒤에 있는 가로등
                if(v.back() + d < l) {
                    chk = false;
                    break;
                } else chk = true;
            } else {
                // 중간에 있는 가로등
                if(v.at(i) + d < v.at(i+1) - d){
                    chk = false;
                    break;
                } else chk = true;
            }
        }

    }

    int answer = d;
    return answer;
}

int main(){
    int l = 15;
    vector<int> v = {15, 5, 3, 7, 9, 14, 0};

    solution(l,v);

    return 0;
}