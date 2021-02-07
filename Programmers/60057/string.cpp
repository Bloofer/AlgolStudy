#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(string s) {
  int ans = s.size();
  for (int i = 1; i <= s.size()/2; i++) {
    string tmp = "";
    for (int j = 0; j < s.size(); j+=i) {
      // 현재 기준 위치에서 substr과 다음 substr을 비교
      if(j+2*i <= s.size()){ // 현재 위치가 다음 substr을 비교가능할 때
        // 만약 substr이 같은게 없으면 문자열에 그대로 해당 위치 문자 붙이고 continue
        if(s.substr(j,i)!=s.substr(j+i,i)) {
          tmp += s.substr(j,i);
          continue;
        }
        // 만약 substr이 같은게 있으면 substr들을 확인가능한 위치까지 비교. 그 갯수만큼 인덱스 이동, tmp에 이어붙임
        tmp += s.substr(j,i);
        int cnt = 1;
        while(j+2*i <= s.size() && s.substr(j,i)==s.substr(j+i,i)){
          cnt++;
          j+=i;
        }
        tmp += to_string(cnt);
      } else{ // 현재 위치가 다음 substr을 비교불가능할 때
        tmp += s.substr(j); // 남은 문자열을 tmp에 붙여 for문 탈출
        break;
      }
    }
    if(ans > tmp.size()) ans = tmp.size(); // 더 짧은 압축열을 찾으면 길이 정답에 업데이트
  }
  return ans;
}
