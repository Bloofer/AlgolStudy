#include <iostream>
#include <queue>
using namespace std;

int arr[10][9] = {0, }; // 0:빈칸 1:왕
bool visit[10][9] = {0, };
typedef struct{
  int x, y, d;
} PIECE;
int dx[8] = {-1,-1,0,1,1,1,0,-1};
int dy[8] = {0,1,1,1,0,-1,-1,-1};
int path[8][3] = {{0,7,7}, {0,1,1}, {2,1,1}, {2,3,3}, {4,3,3}, {4,5,5}, {6,5,5}, {6,7,7}};
int kingX, kingY;

bool available(int x, int y){ return x >= 0 && y >= 0 && x < 10 && y < 9; }

int bfs(int x, int y){
  queue<PIECE> pieceQ;
  pieceQ.push(PIECE{x,y,0});

  while (!pieceQ.empty()) {
    PIECE p = pieceQ.front();
    pieceQ.pop();
    if(p.x==kingX && p.y==kingY) return p.d;

    for (int i = 0; i < 8; i++) {
      int nx = p.x;
      int ny = p.y;
      bool chk = true;
      for (int j = 0; j < 3; j++) {
        nx += dx[path[i][j]];
        ny += dy[path[i][j]];
        if(j==2 && available(nx,ny) && arr[nx][ny]>0) { chk=true; break; }
        if(!available(nx,ny) || arr[nx][ny]>0) { chk=false; break; }
      }
      if(chk && !visit[nx][ny]) { visit[nx][ny]=true; pieceQ.push(PIECE{nx,ny,p.d+1}); }
    }
  }
  return -1;
}

int main(){
  int startX, startY;
  cin >> startX >> startY;
  cin >> kingX >> kingY;
  arr[kingX][kingY] = 1;

  cout << bfs(startX, startY) << endl;
  return 0;
}
