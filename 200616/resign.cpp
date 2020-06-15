#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

int N;
int T[15] = {0, };
int P[15] = {0, };
vector<string> combVec;
bool visit[15] = {0, };
int maxSum = INT_MIN;

int get_max(int a, int b){
  return a > b ? a : b;
}

void dfs(int idx, string cmb){
  if(idx == N) {
    combVec.push_back(cmb);
  } else {
    dfs(idx+1, cmb+"0");
    dfs(idx+1, cmb+"1");
  }
}

void simulate(string cmb){
  int sum = 0;
  bool days[N] = {0, };
  for (int i = 0; i < N; i++) {
    if(cmb[i] == '0') continue;
    if(i+T[i] > N) return;
    for (int j = 0; j < T[i]; j++) {
      if(days[i+j]) return;
      else days[i+j] = true;
    }
    sum += P[i];
  }
  maxSum = get_max(maxSum, sum);
}

int main(){
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> T[i] >> P[i];
  }
  // 1. 모든 조합을 만듬 2^15개 최대
  dfs(0, "");
  // 2. for 모든 조합에 대한 시뮬레이션 수행, 그러나 불가능하면(일정 겹치거나, 안끝나는 것) 중간 종료
  // 3. 매 시뮬레이션이 끝날 때, 수행 값의 최대를 업데이트
  for (auto s:combVec) {
    simulate(s);
  }
  cout << maxSum << endl;
  return 0;
}
