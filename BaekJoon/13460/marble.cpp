#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N, M;
char arr[11][11];

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
bool visit[11][11][11][11] = {0, }; // :visit[rx][ry][bx][by]

typedef struct{
  int rx, ry, bx, by;
} MARBLE;
MARBLE m;

void test_print(){
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cout << arr[i][j];
    }
    cout << endl;
  }
}

int bfs(){
// 1. 큐에 처음 이동하는 MARBLE을 삽입
  queue<MARBLE> marbleQ;
  marbleQ.push(m);
  visit[m.rx][m.ry][m.bx][m.by] = true;
  int cnt = 0;

  while (!marbleQ.empty()) {
    int size = marbleQ.size();
    while(size--){
      MARBLE tmpM;
      tmpM.rx = marbleQ.front().rx;
      tmpM.ry = marbleQ.front().ry;
      tmpM.bx = marbleQ.front().bx;
      tmpM.by = marbleQ.front().by;
      marbleQ.pop();

      // 2. 이동이 10번 넘거나 구멍에 도착한 MARBLE은 종료된다.
      if(arr[tmpM.rx][tmpM.ry] == 'O' && arr[tmpM.rx][tmpM.ry] != arr[tmpM.bx][tmpM.by]) {
        return cnt;
      }

      for (int i = 0; i < 4; i++) {
        // 3. 각 MARBLE은 동서남북으로 이동 후, 큐에 넣어지고 BFS 탐사
        int rrx = tmpM.rx;
        int rry = tmpM.ry;
        int bbx = tmpM.bx;
        int bby = tmpM.by;
        while(arr[rrx + dx[i]][rry + dy[i]] != '#' && arr[rrx][rry] != 'O'){
          rrx += dx[i];
          rry += dy[i];
        }
        while(arr[bbx + dx[i]][bby + dy[i]] != '#' && arr[bbx][bby] != 'O'){
          bbx += dx[i];
          bby += dy[i];
        }
        // 4. 만약 빨간/파란 구슬이 같은 위치에 있는데, 구멍이면 해당 턴 넘기고 일반이면 구슬 하나 이전칸 옮김
        if(rrx == bbx && rry == bby){
          if(arr[rrx][bby] == 'O') continue;
          // 4-1. 이전 칸으로 옮겨지는 것은 이동거리가 더 긴 구술
          if(abs(tmpM.rx - rrx) + abs(tmpM.ry - rry) < abs(tmpM.bx - bbx) + abs(tmpM.by - bby)){
            bbx -= dx[i];
            bby -= dy[i];
          } else {
            rrx -= dx[i];
            rry -= dy[i];
          }
        }
        // 5. 이동한 위치에 방문한적이 있으면 넘김
        if(visit[rrx][rry][bbx][bby]) continue;
        MARBLE nextM;
        nextM.rx = rrx;
        nextM.ry = rry;
        nextM.bx = bbx;
        nextM.by = bby;
        marbleQ.push(nextM);
        visit[rrx][rry][bbx][bby] = true;
      }

    }
    if(cnt == 10) return -1;
    cnt++;
  }
  return -1;
};

int main(){
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> arr[i][j];
      if(arr[i][j] == 'R'){
        m.rx = i;
        m.ry = j;
      } else if(arr[i][j] == 'B'){
        m.bx = i;
        m.by = j;
      }
    }
  }

  int ans = bfs();
  cout << ans << endl;

  return 0;
}
