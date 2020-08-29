#include <iostream>
#include <string>
#include <climits>
#include <queue>
using namespace std;

int arr[5][5][5] = {0, };
int tmpArr[5][5][5] = {0, };
int dx[6] = {0, 0, 1, 0, 0, -1};
int dy[6] = {0, 1, 0, 0, -1, 0};
int dz[6] = {1, 0, 0, -1, 0, 0};
int minVal = INT_MAX;
bool dfsVisit[5] = {0, };

typedef struct{
  int x, y, z;
  int len;
}Q_ELEM;

void copy_arr(string s){
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 5; k++) {
        tmpArr[i][j][k] = arr[s.at(i) - '1'][j][k];
      }
    }
  }
}

int get_min(int a, int b){
  return a < b ? a : b;
}

void turn_right(int idx){
  // 임시 복사 배열 tmpArr에 해당 층 미로 90도 회전
  int tmp2dArr[5][5] = {0, };
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      tmp2dArr[j][4-i] = tmpArr[idx][i][j];
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      tmpArr[idx][i][j] = tmp2dArr[i][j];
    }
  }
}

bool available(int x, int y, int z){
  return x >= 0 && y >= 0 && z >= 0 && x < 5 && y < 5 && z < 5;
}

void bfs_maze(){
  // BFS로 3차원의 미로를 탐사하는 함수
  queue<Q_ELEM> bfsQ;
  bool visit[5][5][5] = {0, };

  Q_ELEM elem;
  // 시작 좌표 (0,0,0)에서 끝 좌표 (4,4,4)에 도달할 때까지 탐사
  elem.x = elem.y = elem.z = elem.len = 0;
  bfsQ.push(elem);

  while(!bfsQ.empty()){
    Q_ELEM topElem = bfsQ.front();
    bfsQ.pop();

    if(topElem.x == 4 && topElem.y == 4 && topElem.z == 4){
      minVal = get_min(minVal, topElem.len);
    } else {
      for (int i = 0; i < 6; i++) {
        int nextX = topElem.x + dx[i];
        int nextY = topElem.y + dy[i];
        int nextZ = topElem.z + dz[i];
        // 다음 좌표가 범위에서 벗어나지 않고, 갈 수 있는 위치(1)이며, 방문되지 않은 경우(사이클 X) 큐에 삽입
        if(available(nextX, nextY, nextZ) && tmpArr[nextX][nextY][nextZ] != 0 && !visit[nextX][nextY][nextZ]){
          Q_ELEM pushElem;
          pushElem.x = nextX;
          pushElem.y = nextY;
          pushElem.z = nextZ;
          pushElem.len = topElem.len+1;
          bfsQ.push(pushElem);
          visit[nextX][nextY][nextZ] = true;
        }
      }
    }
  }
}

void dfs_turn(string s){
  // 각 층의 미로에 대해서 →, ↓, ←, ↑ 각 방향에 대해서 돌리는 조합을 구하는 함수
  if(s.size() == 5){
    if(minVal == 12) return; // 미로탐색 경로중 최적인 12가 먼저 계산되면 더이상 탐사 중지
    else {
      for (int i = 0; i < s.size(); i++) {
        for (int j = 0; j < s.at(i) - '0'; j++) {
          turn_right(i);     // 각 층에 대해서 모든 돌리는 경우의 수를 시뮬레이션 (4^4^4^4^4가지)
        }
        if(tmpArr[0][0][0] == 1 && tmpArr[4][4][4] == 1) bfs_maze(); // 미로의 처음과 끝이 진입 가능한 경우 BFS 탐사 시작
      }
    }
  } else {
    for (int i = 0; i < 4; i++) {
      string nextC(1, i + '0');
      dfs_turn(s + nextC);
    }
  }
}

void dfs_layer(string s){
  // 5층의 미로를 쌓는 조합을 만드는 함수
  // 스트링의 엔트리의 각 문자는 해당 미로 층의 위치를 나타낸다.
  if(s.size() == 5){
    // 조합이 만들어진 경우, 해당 모양으로 미로를 쌓아 tmpArr에 복사
    copy_arr(s);
    if(minVal == 12) return; // 미로탐색 경로중 최적인 12가 먼저 계산되면 더이상 탐사 중지
    else dfs_turn("");       // 각 미로의 층들을 돌리며 DFS 탐사하는 함수 호출
  } else {
    for (int i = 0; i < 5; i++) {
      if(!dfsVisit[i]) {
        string nextC(1, i + '1');
        dfsVisit[i] = true;
        dfs_layer(s + nextC);
        dfsVisit[i] = false;
      }
    }
  }
}

int main(){
  // 모두 0이거나 1인 경우 답이 바로 계산되므로 알고리즘 호출부에서 제외한다.
  bool allZeros = true;
  bool allOnes = true;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 5; k++) {
        cin >> arr[i][j][k];
        allZeros &= (arr[i][j][k] == 0);
        allOnes &= (arr[i][j][k] == 1);
      }
    }
  }

  if (allZeros) {
    cout << -1 << endl;
  } else if (allOnes) {
    cout << 12 << endl;
  } else {
    dfs_layer("");
    if(minVal == INT_MAX) cout << -1 << endl;
    else cout << minVal << endl;
  }

  return 0;
}
