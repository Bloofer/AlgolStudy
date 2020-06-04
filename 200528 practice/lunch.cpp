#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

int T, N;
int arr[10][10];
vector< pair<int, int> > pplVec;
vector< pair<int, int> > strVec;
int strLen[2]; // 계단 길이
vector<string> strCmb;
priority_queue<int, vector<int>, greater<int>> waitQ[2];
int strQ[2][3];  // 계단 큐
int qSize[2] = {0, }; // 계단큐의 길이
int sol = INT_MAX;

int get_min(int a, int b){
  return a < b ? a : b;
}

void dfs(int idx, string cmb){
  if(idx == pplVec.size()) {
    strCmb.push_back(cmb);
    return;
  } else{
    dfs(idx+1, cmb+"0");
    dfs(idx+1, cmb+"1");
  }
}

int calculate_dist(int x1, int y1, int x2, int y2){
  return abs(x1 - x2) + abs(y1 - y2);
}

void pop_stairQ(int idx){
  if(qSize[idx] == 0){
    return;
  } else if(qSize[idx] == 1){
    strQ[idx][0] = 0;
    qSize[idx] = 0;
  } else{
    for (int i = 1; i < qSize[idx]; i++) {
      strQ[idx][i-1] = strQ[idx][i];
    }
    strQ[idx][qSize[idx] - 1] = 0;
    qSize[idx]--;
  }
}

void simulate_stair(string cmb){
  for (int i = 0; i < pplVec.size(); i++) {
    int strIdx = cmb[i] - '0';
    int dist = calculate_dist(pplVec[i].first, pplVec[i].second, strVec[strIdx].first, strVec[strIdx].second);
    waitQ[strIdx].push(dist);
  }

  // 1. waitQ에는 각 계단별 대기자가 삽입됨(도착한 순서대로)
  // 2. 먼저 삽입된 대기자들 순으로 모든 waitQ와 strQ가 빌때까지 무한루프
  // 3. tick을 하나씩 증가시키며 strQ가 비어있을 경우 waitQ의 top을 pop하고 새로 strQ에 push_back
  // 4. 여기서 waitQ의 top은 tick이 자기자신보다 크거나 같아야만 진입가능
  int tick = 0;

  while(true){
    if(waitQ[0].empty() && waitQ[1].empty() && qSize[0] == 0 && qSize[1] == 0) break;
    // 큐1/2 확인 시작
    for (int i = 0; i < 2; i++) {
      // 1. 계단 큐의 인원이 계단길이만큼 시간이 도달했으면 stair pop
      while(strQ[i][0] >= strLen[i]) pop_stairQ(i);
      // 2. 계단 큐가 비어있는 경우(현재 크기가 3보다 작은경우) && 대기 큐가 비지 않은 경우
      //    대기 큐에서 인원한명 pop, 계단 큐에 삽입하고 계단 큐 크기 + 1
      //    여기서 대기큐의 top은 tick + 1이 자기자신보다 작거나 같아야만 진입가능
      while(qSize[i] < 3 && !waitQ[i].empty() && waitQ[i].top() <= tick+1){
        waitQ[i].pop();
        qSize[i]++;
      }
      // 3. 계단 큐의 인원들 시간 + 1
      for (int j = 0; j < qSize[i]; j++) {
        strQ[i][j]++;
      }
    }
    tick++;
  }
  sol = get_min(sol, tick);
}

void init(){
  pplVec.clear();
  strVec.clear();
  strCmb.clear();
  for (int i = 0; i < waitQ[0].size(); i++) waitQ[0].pop();
  for (int i = 0; i < waitQ[1].size(); i++) waitQ[1].pop();
  qSize[0] = qSize[1] = 0;
  sol = INT_MAX;
}

int main(){
  cin >> T;
  for (int i = 0; i < T; i++) {
    cin >> N;
    init();
    int strIdx = 0;
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        cin >> arr[j][k];
        if(arr[j][k] == 1) pplVec.push_back(pair<int, int>(j, k));
        else if(arr[j][k] > 1) {
          strLen[strIdx++] = arr[j][k];
          strVec.push_back(pair<int, int>(j, k));
        }
      }
    }
    dfs(0, "");
    for(auto s:strCmb) simulate_stair(s);
    cout << "#" << i + 1 << " " << sol + 1 << endl;
  }

  return 0;
}
