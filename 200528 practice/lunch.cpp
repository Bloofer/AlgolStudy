#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int T, N;
int arr[10][10];
vector< pair<int, int> > pplVec;
bool pplDown[10] = {0, }; // 사람이 내려갔는지 확인하는 배열. 벡터의 인덱스 나타냄
vector< pair<int, int> > strVec;
int strLen[2]; // 계단 길이
vector<string> strCmb;
priority_queue<int, vector<int>, greater<int>> waitQ[2];
queue<int> strQ[2];

// 1. 각 계단별로 사람을 배치하는 조합을 구함 - dfs()
// 2. 모든 조합에 대해서 계단 내려가기 시뮬레이션 수행 - simulate_stair()
// 2-1. 모든 사람이 계단을 내려갈 때까지 무한루프 시작
// 2-2. 1에서 정해진 대로 각 사람들은 해당 계단으로 이동
// 2-2-1. 모든 인원들은 각 계단 대기큐로 이동, 각 인원은 해당 계단 도착 시간을 가짐
// 2-3. 계단이 비어있는 경우 계단큐에 삽입, 차 있으면 계단 대기큐에서 대기
// 2-4. 계단 큐에서 하나하나 이동하며 바닥으로 진입시 계단큐에서 pop, 계단 대키큐 인원은 push_back
// 3. 모든 인원이 pplDown TRUE되면 종료

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

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
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
  //while(true){
    //if(waitQ[0].empty() && waitQ[1].empty() && strQ[0].empty() && strQ[1].empty()) break;
    // 큐1부터 확인 시작
    for(auto it=waitQ[0].begin(); it!=waitQ[0].end(); ++it) (*it)++

    tick++;
  //}

}

void init(){
  pplVec.clear();
  strVec.clear();
  strCmb.clear();
  for (int i = 0; i < 10; i++) pplDown[i] = false;
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
    simulate_stair(strCmb[0]);
    print_queue(waitQ[0]);
  }


  return 0;
}
