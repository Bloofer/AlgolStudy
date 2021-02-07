#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

int orderNum = 20;
bool totalMenu[26] = {0, };
vector<string> combVec;
map<string, int> combMap;

void dfs(int n, string s){
  if(s.size() == n) combVec.push_back(s);

  int i;
  if(s.size() == 0) i = 0;
  else i = s.back()-'A'+1;

  for (; i < 26; i++) {
    if(totalMenu[i]) dfs(n, s+(char)(i+'A'));
  }
}

vector<string> solution(vector<string> orders, vector<int> course) {
  memset(totalMenu, 0, sizeof(totalMenu)); // 1. 전체 메뉴 구성에 대한 체크 배열 만듦
  for (auto i:orders) {
    for (auto j:i) {
      if(!totalMenu[j-'A']) totalMenu[j-'A'] = true; // 전체 메뉴 배열에 주문내 존재하는 음식들을 추가
    }
  }
  // for (int i = 0; i < 26; i++) {
  //   if(totalMenu[i]) cout << (char)('A' + i) << endl;
  // }

  // 2. 각 인원별 메뉴 해쉬 셋 만듦
  orderNum = orders.size();
  bool indvMenu[20][26] = {0, };
  for (int i = 0; i < orderNum; i++) {
    for (auto j:orders[i]) {
      if(!indvMenu[i][j-'A']) indvMenu[i][j-'A'] = true;
    }
  }

  // for (int i = 0; i < orderNum; i++) {
  //   for (int j = 0; j < 26; j++) {
  //     if(indvMenu[i][j]) cout << (char)('A' + j);
  //   }
  //   cout << endl;
  // }

  vector<string> answer;
  for(auto i:course){
    combVec.clear();
    dfs(i,""); // 전체 해쉬 셋에서 코스 크기별 조합 생성

    for (int j = 0; j < orderNum; j++) {
      for (auto k:combVec) {
        bool chk = true;
        for (auto l:k) {
          chk &= indvMenu[i][l-'A'];
        }
        if(chk) cout << k << endl;
      }
    }
  }




  return answer;
}

int main(){
  vector<string> orders[3] = { {"ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH"},
                              {"ABCDE", "AB", "CD", "ADE", "XYZ", "XYZ", "ACD"},
                              {"XYZ", "XWY", "WXA"}	};
  vector<int> courses[3] = { {2,3,4}, {2,3,5}, {2,3,4} };
  solution(orders[2], courses[2]);

  return 0;
}
