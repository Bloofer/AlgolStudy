#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;
bool check[100001] = {0, };
bool cmp(vector<int> &v1, vector<int> &v2){ return v1.size() < v2.size(); }

vector<int> solution(string s) {
  int p = 0;
  int cnt = 0;
  string tmp = "";
  vector<string> tmpVec;

  // 1. 스트링으로 주어진 형태의 입력을 대괄호를 기준으로 나눔
  while(p!=s.size()){
    if(s[p] == '{') cnt++;
    else if(s[p] == '}') {
      if(cnt == 2) { tmpVec.push_back(tmp); tmp = ""; }
      cnt--;
    } else if(cnt == 2) tmp+=s[p];
    p++;
  }

  // 2. 대괄호 내에서 나누어진 튜플들의 원소를 정수형으로 쪼개어 중첩벡터에 삽입
  vector<vector<int>> tupleVec;
  for(auto t:tmpVec){
    vector<int> numVec;
    stringstream ss(t);
    for (int i; ss >> i;) {
      numVec.push_back(i);
      if (ss.peek() == ',') ss.ignore();
    }
    tupleVec.push_back(numVec);
  }

  // 3. 중첩벡터 내 벡터, 각 튜플의 원소의 크기에 따라 정렬
  sort(tupleVec.begin(), tupleVec.end(), cmp);
  vector<int> answer;
  for(auto t:tupleVec){
    for(auto tt:t) {
      // 4. 그 안에서 제일 작은 집합의 원소부터 튜플에 삽입
      if(!check[tt]) { answer.push_back(tt); check[tt] = true; }
    }
  }
  return answer;
}
