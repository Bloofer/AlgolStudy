#include <iostream>
#include <queue>
#include <climits>
using namespace std;

int R, C;
char arr[50][50];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
typedef struct{
  int x, y, sec;
}ENTRY;
queue<ENTRY> waterQ, hedgehogQ;
int minTime = INT_MAX;

int get_min(int a, int b){
  return a < b ? a : b;
}

bool available(int x, int y){
  return x < R && y < C && x >= 0 && y >= 0
        && arr[x][y] != '*' && arr[x][y] != 'X'; // 고슴도치 위치만 빼고
}

void escape(){
  int tick = 0;
  // 매 초를 증가시키며 고슴도치 -> 물 순으로 이동
  // 고슴도치 큐가 빌 때까지 반복
  while (!hedgehogQ.empty()) {
    while(hedgehogQ.front().sec == tick){
      int x = hedgehogQ.front().x;
      int y = hedgehogQ.front().y;
      int s = hedgehogQ.front().sec;
      hedgehogQ.pop();
      if(arr[x][y] == '*') continue;
      else if(arr[x][y] == 'D') { // 만약, 비버굴을 발견하면 종료하고 시간을 최소에 업데이트
        minTime = get_min(minTime, s);
        continue;
      }

      for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(available(nx, ny) && arr[nx][ny] != 'S') {
          // 먼저 고슴도치가 주변 영역중 갈 수 있는 영역으로 이동(범위 안, 돌 X)
          if(arr[nx][ny] != 'D') arr[nx][ny] = 'S';
          hedgehogQ.push(ENTRY{nx,ny,s+1});
        }
      }
    }

    while(!waterQ.empty() && waterQ.front().sec == tick){
      int x = waterQ.front().x;
      int y = waterQ.front().y;
      int s = waterQ.front().sec;
      waterQ.pop();

      for (int i = 0; i < 4; i++) {
        // 물은 BFS로 지도를 칠하며 영역을 넓혀나감
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(available(nx, ny) && arr[nx][ny] != 'D') {
          arr[nx][ny] = '*'; // 비버가 있는 위치를 만나도 위에 덧칠함
          waterQ.push(ENTRY{nx,ny,s+1});
        }
      }
    }
    tick++;
  }

}

int main(){
  cin >> R >> C;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      cin >> arr[i][j];
      if(arr[i][j] == '*') waterQ.push(ENTRY{i,j,0});
      else if(arr[i][j] == 'S') hedgehogQ.push(ENTRY{i,j,0});
    }
  }

  escape();
  if(minTime == INT_MAX) cout << "KAKTUS" << endl;
  else cout << minTime << endl;

  return 0;
}
