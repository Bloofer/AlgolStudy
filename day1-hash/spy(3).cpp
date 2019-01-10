#include <string>
#include <vector>
#include <map>
using namespace std;

int solution(vector<vector<string>> clothes) {
    map<string, int> cMap;
    for(int i=0; i<clothes.size(); i++){
        cMap[clothes.at(i).back()]++;
    }
    // 각 옷의 종류별로 맵에 계수함

    // 문제 조건에 띠라 조합 계산
    int answer = 0;
    if(cMap.size() == 1){
        // 1) 가진 옷의 종류가 모두 같은 경우, 해당 옷의 갯수가 전체 조합의 갯수
        answer = cMap.begin()->second;
    } else {
        // 2) 가진 옷의 종류가 다른 경우, 옷 종류별 갯수 + 1 전부 곱하여 조합 계산 ( + 1은 안 입는 경우 )
        // 마지막에 계산된 조합에서 - 1 함. 이유는 최소 하루 한 종류의 옷은 입기 때문
        answer = 1;
        for(map<string,int>::iterator it=cMap.begin(); it!=cMap.end(); ++it){
            answer *= (it->second + 1); 
        }
        answer--;
    }

    return answer;
}