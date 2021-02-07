#include <iostream>
#include <string>
#include <climits>
using namespace std;

int arr[50][50] = {0, };
int carr[50][50];
bool visit[50][50][2] = {0, };
int N;
int minCnt = INT_MAX;
int sttX = -1;
int sttY = -1;
int endX = -1;
int endY = -1;
int sttDir, endDir;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool available(int x, int y){ return x >= 0 && y >= 0 && x < N && y < N; }
int get_min(int a, int b){ return a < b ? a : b; }

void dfs(int x, int y, int d, int cnt){
  if(cnt > minCnt) return;

  // 통나무 방향(d=0은 수평, 1은 수직), 좌측/상단 좌표(x,y), 누적 명령횟수(cnt)
  if(x == endX && y == endY && d == endDir){
    minCnt = get_min(minCnt, cnt);
    return;
  }

  for(int i = 0; i < 4; i++) {
    if(d == 0){ // 통나무가 수평일 때
      bool chk = true;
      for(int j = 0; j < 3; j++) chk &= (available(x+dx[i],y+j+dy[i]) && !arr[x+dx[i]][y+j+dy[i]]);
      if(chk && !visit[x+dx[i]][y+dy[i]][d]) {
        visit[x+dx[i]][y+dy[i]][d] = true;
        dfs(x+dx[i],y+dy[i],d,cnt+1);
        visit[x+dx[i]][y+dy[i]][d] = false;
      }
    } else { // 통나무가 수직일 때
      bool chk = true;
      for(int j = 0; j < 3; j++) chk &= (available(x+j+dx[i],y+dy[i]) && !arr[x+j+dx[i]][y+dy[i]]);
      if(chk && !visit[x+dx[i]][y+dy[i]][d]) {
        visit[x+dx[i]][y+dy[i]][d] = true;
        dfs(x+dx[i],y+dy[i],d,cnt+1);
        visit[x+dx[i]][y+dy[i]][d] = false;
      }
    }
  }

  // 통나무 회전 수행
  if(d == 0){ // 통나무가 수평일 때
    if(available(x-1, y) && available(x+1, y+2)){
      bool chk = true;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          chk &= (arr[x-1+i][y+j] == 0);
        }
      }
      if(chk && !visit[x-1][y+1][1]) {
        visit[x-1][y+1][1] = true;
        dfs(x-1,y+1,1,cnt+1);
        visit[x-1][y+1][1] = false;
      }
    }
  } else { // 통나무가 수직일 때
    if(available(x, y-1) && available(x+2, y+1)){
      bool chk = true;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          chk &= (arr[x+i][y-1+j] == 0);
        }
      }
      if(chk && !visit[x+1][y-1][0]) {
        visit[x+1][y-1][0] = true;
        dfs(x+1,y-1,0,cnt+1);
        visit[x+1][y-1][0] = false;
      }
    }
  }
}

int main(){
  cin >> N;
  string s;
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

  dfs(sttX, sttY, sttDir, 0);
  if(minCnt == INT_MAX) cout << 0 << endl;
  else cout << minCnt << endl;

  return 0;
}
