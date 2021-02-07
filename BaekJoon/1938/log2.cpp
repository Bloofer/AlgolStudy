#include <iostream>
#include <string>
#include <climits>
#include <queue>
using namespace std;

int arr[50][50] = {0, };
bool visit[50][50][2] = {0, };
int N;
int sttX, sttY, endX, endY;
int sttDir, endDir;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
typedef struct{
  int x, y, d, cnt;
} LOG;

bool available(int x, int y){ return x >= 0 && y >= 0 && x < N && y < N; }

int bfs(int x, int y, int d){
  queue<LOG> logQ;
  logQ.push(LOG{x,y,d,0});

  while(!logQ.empty()){
    LOG log = logQ.front();
    logQ.pop();

    // 통나무 방향(d=0은 수평, 1은 수직), 좌측/상단 좌표(x,y), 누적 명령횟수(cnt)
    if(log.x == endX && log.y == endY && log.d == endDir){
      return log.cnt;
    }

    for(int i = 0; i < 4; i++) {
      if(log.d == 0){ // 통나무가 수평일 때
        bool chk = true;
        for(int j = 0; j < 3; j++) chk &= (available(log.x+dx[i],log.y+j+dy[i]) && !arr[log.x+dx[i]][log.y+j+dy[i]]);
        if(chk && !visit[log.x+dx[i]][log.y+dy[i]][log.d]) {
          visit[log.x+dx[i]][log.y+dy[i]][log.d] = true;
          logQ.push(LOG{log.x+dx[i],log.y+dy[i],log.d,log.cnt+1});
        }
      } else { // 통나무가 수직일 때
        bool chk = true;
        for(int j = 0; j < 3; j++) chk &= (available(log.x+j+dx[i],log.y+dy[i]) && !arr[log.x+j+dx[i]][log.y+dy[i]]);
        if(chk && !visit[log.x+dx[i]][log.y+dy[i]][log.d]) {
          visit[log.x+dx[i]][log.y+dy[i]][log.d] = true;
          logQ.push(LOG{log.x+dx[i],log.y+dy[i],log.d,log.cnt+1});
        }
      }
    }

    // 통나무 회전 수행
    if(log.d == 0){ // 통나무가 수평일 때
      if(available(log.x-1, log.y) && available(log.x+1, log.y+2)){
        bool chk = true;
        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) {
            chk &= (arr[log.x-1+i][log.y+j] == 0);
          }
        }
        if(chk && !visit[log.x-1][log.y+1][1]) {
          visit[log.x-1][log.y+1][1] = true;
          logQ.push(LOG{log.x-1,log.y+1,1,log.cnt+1});
        }
      }
    } else { // 통나무가 수직일 때
      if(available(log.x, log.y-1) && available(log.x+2, log.y+1)){
        bool chk = true;
        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) {
            chk &= (arr[log.x+i][log.y-1+j] == 0);
          }
        }
        if(chk && !visit[log.x+1][log.y-1][0]) {
          visit[log.x+1][log.y-1][0] = true;
          logQ.push(LOG{log.x+1,log.y-1,0,log.cnt+1});
        }
      }
    }
  }

  return 0;
}

int main(){
  sttX = sttY = endX = endY = -1;
  cin >> N;
  string s;
  int carr[50][50];
  for (int i = 0; i < N; i++) {
    cin >> s;
    for (int j = 0; j < N; j++) {
      carr[i][j] = s[j];
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if(carr[i][j] == '1') arr[i][j] = 1;
      if(carr[i][j] == 'B' && sttX == -1) {
        sttX = i; sttY = j;
        if(available(i,j+1) && carr[i][j+1] == 'B') sttDir = 0;
        else sttDir = 1;
      }
      if(carr[i][j] == 'E' && endX == -1) {
        endX = i; endY = j;
        if(available(i,j+1) && carr[i][j+1] == 'E') endDir = 0;
        else endDir = 1;
      }
    }
  }

  cout << bfs(sttX, sttY, sttDir) << endl;

  return 0;
}
