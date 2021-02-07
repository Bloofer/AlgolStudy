#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int visit[3][3][3][3] = {0, }; // x/y:0의 위치와 i/j:판의 상태, 엔트리: 해당배열내 값
vector<vector<int>> status[3][3];
struct entry{
  int x,y,move;
  int arr[3][3];
};
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool check(int a[][3]){
  bool chk = true;
  int cnt = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if(i==2&&j==2) {
        return (chk&&(a[i][j]==0));
      }else{
        chk&=(a[i][j]==cnt);
        cnt++;
      }
    }
  }
  return chk;
}

bool available(int x, int y){ return x>=0 && y>=0 && x<3 && y<3; }
bool is_visited(int x, int y, int a[][3]){
  bool chk = true;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      chk &= (visit[x][y][i][j] == a[i][j]);
    }
  }
}

int bfs(int a, int b, int a[][3]){
  queue<entry> bfsQ;
  entry e;
  e.x=a; e.y=b;
  e.move=0;
  copy(&a[0][0], &a[0][0]+3*3, &e.arr[0][0]);
  bfsQ.push(e);

  while(!bfsQ.empty()){
    entry frtE = bfsQ.front();
    bfsQ.pop();
    if(check(frtE.arr)){ return frtE.move; }
    else {
      for (int i = 0; i < 4; i++) {
        int nx = frtE.x + dx[i];
        int ny = frtE.y + dy[i];
        if(available(nx,ny)) {
          swap(frtE.arr[frtE.x][frtE.y],frtE.arr[nx][ny]);
          if(!visit[frtE.x][frtE.y][][])
        }

      }
    }
  }

  return -1;
}

int main(){
  int x, y;
  int puzzle[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cin >> puzzle[i][j];
      if(puzzle[i][j]==0){ x=i; y=j; }
    }
  }

  cout << bfs(x,y,puzzle) << endl;
  cout << check(puzzle) << endl;

  return 0;
}
