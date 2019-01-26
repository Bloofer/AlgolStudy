#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int solution(int l, vector<int> v) {
    
    // 1. v를 오름 차순으로 정렬함
    sort(v.begin(), v.end());

    // 2. 정렬된 숫자 중 가로등 범위 간 거리가 가장 먼 것을 찾음
    int furthestGap = 0;
    for(int i=0; i<v.size(); i++){
        if(i==0) furthestGap = v.at(i); // 맨 앞에 있는 경우
        else if(i==v.size()-1){
            // 맨 뒤에 있는 경우
            if(l - v.at(i) > furthestGap) furthestGap = l - v.at(i);
        }else {
            if((v.at(i+1) - v.at(i) - 1)/2 + 1 > furthestGap) furthestGap = (v.at(i+1) - v.at(i) - 1)/2 + 1;
        }
    }

    int answer = furthestGap;
    return answer;
}

int main(){
    int l = 15;
    vector<int> v = {15, 5, 3, 7, 9, 14, 0};

    solution(l,v);

    return 0;
}