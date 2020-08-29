#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int arr[12][6] = {0, }; // Empty:0, R:1, G:2, B:3, Y:4
bool puyoArr[12][6] = {0, };
bool visit[12][6] = {0, };

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
typedef struct {
  int x, y;
} PUYO;

bool available(int x, int y){
  return x>=0 && y>=0 && x<12 && y<6;
}

void puyo_bfs(int a, int b){
  queue<PUYO> puyoQ;
  vector<PUYO> puyoV;
  PUYO p {a, b};
  puyoQ.push(p);
  puyoV.push_back(p);
  visit[a][b] = true;
  int depth = 1;

  while(!puyoQ.empty()){ // 큐가 빌때까지 반복 진행
    PUYO popPuyo = puyoQ.front();
    puyoQ.pop();
    for (int k = 0; k < 4; k++) { // 상하 좌우를 탐사하며 주변 푸요를 탐색
      int nx = popPuyo.x + dx[k];
      int ny = popPuyo.y + dy[k];
      if(available(nx, ny) && !visit[nx][ny] && arr[nx][ny]==arr[a][b]){ // 만약, 주변에 같은 색의 푸요를 찾았다면
        PUYO newP {nx, ny};
        puyoQ.push(newP); // 큐에 해당 푸요를 넣고 탐사 진행 반복
        puyoV.push_back(newP);
        visit[nx][ny] = true;
        depth++;
      }
    }
  }

  if(depth>=4){ // 푸요의 길이가 4가 넘는 애들에 대해서 연쇄표시
    for(auto pv:puyoV) puyoArr[pv.x][pv.y] = true;
  }
}

void puyo_search(){
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 6; j++) {
      // 모든 배열의 엔트리를 탐사하되, puyoArr에 표시되었거나, 빈 배열은 스킵
      if(arr[i][j] == 0 || puyoArr[i][j] || visit[i][j]) continue;
      else {
        puyo_bfs(i, j);
      }
    }
  }
}

int c_to_int(char c){
  if(c == '.') return 0;
  else if(c == 'R') return 1;
  else if(c == 'G') return 2;
  else if(c == 'B') return 3;
  else if(c == 'Y') return 4;
  else return -1;
}

void init(){
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 6; j++) {
      visit[i][j] = false;
      puyoArr[i][j] = false;
    }
  }
}

int main(){
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 6; j++) {
      char c;
      cin >> c;
      arr[i][j] = c_to_int(c);
    }
  }

  bool puyoSplash; // 푸요의 연쇄작용 여부 확인
  int cnt = 0;
  do { // 1. 푸요 탐사 함수의 반환이 false일 때까지 while문 수행
    puyoSplash = false;
    init();
    puyo_search(); // 2. 처음에 푸요 탐사함수가 연쇄로 없어질 푸요를 puyoArr에 표기후 Arr에 직접 없앰
    for (int i = 0; i < 12; i++) {
      for (int j = 0; j < 6; j++) {
        if(puyoArr[i][j]) {
          arr[i][j] = 0;
          puyoSplash = true;
        }
      }
    }
    if(puyoSplash) cnt++;

    // 3. 각 열에 대해 호출하여 모든 열을 없어진 푸요를 제외하고 모두 아래로 밈
    for (int i = 0; i < 6; i++) {
      vector<int> tmpV;
      for (size_t j = 0; j < 12; j++) if(arr[11-j][i] != 0) tmpV.push_back(arr[11-j][i]);
      int tmpSiz = tmpV.size();
      for (size_t j = 0; j < 12-tmpSiz; j++) tmpV.push_back(0);
      for (size_t j = 0; j < 12; j++) arr[11-j][i] = tmpV[j];
    }
  } while(puyoSplash);

  cout << cnt << endl;

  return 0;
}
