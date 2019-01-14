#include <string>
#include <iostream>
#include <vector>
using namespace std;

int solution(string arrangement) {
    int answer = 0;
    int cnt = -1;
    for(int i=0; i<arrangement.size(); i++){
        if(arrangement.at(i) == '(') cnt++;
        else {
            // 레이저를 만난 경우, cnt 만큼 증가
            if(arrangement.at(i-1) == '(') answer += cnt;
            // 막대의 닫는 괄호 만난 경우, 나머지 조각인 1만 증가
            else answer++;
            cnt--;
        }
    }
    return answer;
}