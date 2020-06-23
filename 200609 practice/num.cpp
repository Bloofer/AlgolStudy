#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool visit[10] = {0, };
int T, N, K;
vector<string> combVec;

void dfs(int idx, string comb){
  if(idx == N) combVec.push_back(comb);
  else {
    for (int i = 0; i < N; i++) {
      if(!visit[i]) {
        visit[i] = true;
        dfs(idx+1, comb+(char)(i+'1'));
        visit[i] = false;
      }
    }
  }
}

bool func_s(string s1, string s2){
  int sum = 0;
  for (int i = 0; i < N; i++) {
    sum += s1[i] + s2[i];
  }
  return sum >= K;
}

int main(){
  cin >> T;
  for (int i = 0; i < T; i++) {
    cin >> N >> K;
    dfs(0, "");

    int cnt = 0;
    for (int j = 0; j < combVec.size(); j++) {
      for (int k = 0; k < combVec.size(); k++) {
        if(func_s(combVec[j], combVec[k])) {
          cout << combVec[j] << " " << combVec[k] << endl;
          cnt++;
        }
      }
    }
    combVec.clear();
    cout << cnt << endl;
  }

  return 0;
}
