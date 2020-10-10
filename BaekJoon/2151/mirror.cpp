#include <iostream>
#include <climits>
using namespace std;

char arr[50][50];
bool visit[50][50][4] = {0, };
// visit 배열을 사용할 때 해당 좌표에 방문한 방향까지 같이 고려, 해당 방향에 같은 방향으로 재반복아님
int N;
int minCnt = INT_MAX;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int startX, startY;

bool available(int x, int y) { return x >= 0 && y >= 0 && x < N && y < N; }
int get_min(int a, int b) { return a < b ? a : b; }

void dfs(int x, int y, int cnt, int dir){
  // x,y: 현재 좌표, cnt: 거울의 갯수, dir: 현재방향
  // 1. dfs는 방향과 좌표정보를 가지고 탐사를 계속 진행
  if(cnt > minCnt) return; // 2. cnt가 최소 거울 갯수를 초과하면 탐사를 종료한다(가지치기)
  int nx = x + dx[dir]; int ny = y + dy[dir];
  if(!available(x, y) || arr[x][y] == '*') return; // 3. 영역을 벗어나거나 *을 만나면 종료
  else if(arr[x][y] == '#' && (x != startX || y != startY)) { minCnt = get_min(minCnt, cnt); return; } // 4. #을 만나면 해당 cnt를 최소에 업데이트
  else if(arr[x][y] == '.' || (x == startX && y == startY)) { // 5. .을 만나면 방향 그대로 이동 진행
    if(!visit[nx][ny][dir]){
      visit[x][y][dir] = true;
      dfs(nx, ny, cnt, dir);
      visit[x][y][dir] = false;
    }
  }
  else if(arr[x][y] == '!') { // 6. !를 만나면 거울을 설치하는/안하는 경우로 dfs 분기
    if(!visit[nx][ny][dir]){
      visit[x][y][dir] = true;
      dfs(nx, ny, cnt, dir);
      visit[x][y][dir] = false;
    }

    int ndir = (dir + 3) % 4;
    nx = x + dx[ndir]; ny = y + dy[ndir];
    if(!visit[nx][ny][ndir]){
      visit[x][y][ndir] = true;
      dfs(nx, ny, cnt+1, ndir);
      visit[x][y][ndir] = false;
    }

    ndir = (dir + 1) % 4;
    nx = x + dx[ndir]; ny = y + dy[ndir];
    if(!visit[nx][ny][ndir]){
      visit[x][y][ndir] = true;
      dfs(nx, ny, cnt+1, ndir);
      visit[x][y][ndir] = false;
    }
  }
}

int main(){
  cin >> N;
  bool chk = false;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> arr[i][j];
      if(arr[i][j] == '#' && !chk) {startX=i; startY=j; chk=true;}
    }
  }
  for (int i = 0; i < 4; i++) dfs(startX,startY,0,i);
  cout << minCnt << endl;

  return 0;
}
