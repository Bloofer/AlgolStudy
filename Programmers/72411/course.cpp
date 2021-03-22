#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

int cnt[27];
unordered_map<string, int> crsMap; // 코스 해쉬셋
vector<string> menu[27][21];

void dfs(string s, int d, string cmb){
  if(cmb.size()>=2){
    crsMap[cmb]++;
    cnt[cmb.size()] = max(cnt[cmb.size()], crsMap[cmb]);
    menu[cmb.size()][crsMap[cmb]].push_back(cmb);
  }
  for(int i=d+1; i<s.size(); i++){
    cmb.push_back(s[i]);
    dfs(s,i,cmb);
    cmb.pop_back();
  }
}

vector<string> solution(vector<string> orders, vector<int> course) {
  vector<string> answer;

  for(auto o:orders){
    sort(o.begin(), o.end());
    dfs(o,-1,"");
  }

  for(auto c:course){
    if(cnt[c]>=2){
      for(auto m:menu[c][cnt[c]])
        answer.push_back(m);
    }
  }

  sort(answer.begin(), answer.end());
  return answer;
}
