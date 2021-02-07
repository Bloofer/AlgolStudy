#include <iostream>
#include <queue>
using namespace std;

int arr[201][201] = {0, };
bool visit[201][201][31] = {0, };
int K, W, H;
typedef struct{
  int x, y, d, k; // x,y:원숭이 좌표, d:이동 횟수, k:말 이동 횟수
} MONKEY;

int dx[8] = {-1,-1,0,1,1,1,0,-1};
int dy[8] = {0,1,1,1,0,-1,-1,-1};
int horseMove[8][2] = {{0,1}, {2,1}, {2,3}, {4,3}, {4,5}, {6,5}, {6,7}, {0,7}};

bool available(int x, int y){ return x >= 0 && y >= 0 && x < H && y < W; }

int bfs(int x, int y){
  queue<MONKEY> monkeyQ;
  monkeyQ.push(MONKEY{x,y,0,0});

  while(!monkeyQ.empty()){
    MONKEY m = monkeyQ.front();
    monkeyQ.pop();

    if(m.x==H-1 && m.y==W-1) return m.d;

    if(m.k < K){
      for (int i = 0; i < 8; i++) {
        int nx = m.x;
        int ny = m.y;
        for (int j = 0; j < 2; j++) {
          nx += dx[horseMove[i][j]];
          ny += dy[horseMove[i][j]];
        }
        if(available(nx, ny) && !visit[nx][ny][m.k+1] && arr[nx][ny]==0){
          visit[nx][ny][m.k+1] = true;
          monkeyQ.push(MONKEY{nx,ny,m.d+1,m.k+1});
        }
      }
    }

    for (int i = 0; i < 4; i++) {
      int nx = m.x + dx[2*i];
      int ny = m.y + dy[2*i];
      if(available(nx, ny) && !visit[nx][ny][m.k] && arr[nx][ny]==0){
        visit[nx][ny][m.k] = true;
        monkeyQ.push(MONKEY{nx,ny,m.d+1,m.k});
      }
    }
  }

  return -1;
}

int main(){
  cin >> K >> W >> H;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      cin >> arr[i][j];
    }
  }

  cout << bfs(0,0) << endl;

  return 0;
}
