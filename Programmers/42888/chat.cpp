#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

map<string, string> aliasMap;

vector<string> solution(vector<string> record) {
  vector<pair<bool, string>> recordVec; // 0: 나감, 1: 들어옴 레코드 기록 벡터

  for(auto r:record){
    istringstream iss(r);
    string s, stat, id;
    int cnt = 0;
    while(getline(iss, s, ' ')){
      if(cnt == 0) stat = s;
      else if(cnt == 1) {
        id = s;
        if(stat == "Leave") {
          recordVec.push_back(pair<bool, string>(false, s));
        }
      } else if(cnt == 2) {
        if(stat == "Enter") {
          if(aliasMap.find(id) != aliasMap.end()) aliasMap[id] = s;
          else aliasMap.insert(pair<string, string>(id, s));
          recordVec.push_back(pair<bool, string>(true, id));
        } else if(stat == "Change") {
          aliasMap[id] = s;
        }
      }
      cnt++;
    }
  }

  vector<string> answer;
  for(auto r:recordVec) {
    if(r.first) answer.push_back(aliasMap[r.second]+"님이 들어왔습니다.");
    else answer.push_back(aliasMap[r.second]+"님이 나갔습니다.");
  }

  return answer;
}
