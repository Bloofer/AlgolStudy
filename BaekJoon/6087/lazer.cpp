#include <iostream>
#include <queue>
#include <climits>
using namespace std;

char arr[101][101];
int W, H;
int sttX, sttY, endX, endY;
int minVal = INT_MAX;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int ddx[8] = {-1,-1,0,1,1,1,0,-1};
int ddy[8] = {0,1,1,1,0,-1,-1,-1};
bool visit[101][101] = {0, };
typedef struct{
  int x, y, m, d; // x,y:좌표, m:거울사용 횟수, d:진행방향
}ENTRY;

bool available(int x, int y){ return x>=0 && y>=0 && x<H && y<W; }
int get_min(int a, int b){ return a < b ? a : b; }

int bfs(int x, int y){
  queue<ENTRY> entryQ;
  for(int i = 0; i < 4; i++) { entryQ.push(ENTRY{x,y,0,i}); }

  while(!entryQ.empty()) {
    ENTRY e = entryQ.front();
    entryQ.pop();
    visit[e.x][e.y] = true;
    //cout << e.x << "," << e.y << ":" << e.d << endl;

    if(e.x == endX && e.y == endY){
      minVal = get_min(minVal, e.m);
    } else {
      int nx = e.x + dx[e.d];
      int ny = e.y + dy[e.d];
      if(available(nx, ny) && arr[nx][ny] != '*'){
        if(!visit[nx][ny] && e.m<minVal) {
          entryQ.push(ENTRY{nx,ny,e.m,e.d});
        }
      } else {
        nx = e.x + dx[(e.d+1)%4];
        ny = e.y + dy[(e.d+1)%4];
        if(available(nx, ny) && arr[nx][ny] != '*' && !visit[nx][ny] && e.m+1<minVal) {
          entryQ.push(ENTRY{nx,ny,e.m+1,(e.d+1)%4});
        }

        nx = e.x + dx[(e.d+3)%4];
        ny = e.y + dy[(e.d+3)%4];
        if(available(nx, ny) && arr[nx][ny] != '*' && !visit[nx][ny] && e.m+3<minVal) {
          entryQ.push(ENTRY{nx,ny,e.m+1,(e.d+3)%4});
        }
      }
    }
  }

  return minVal;
}

int main(){
  sttX = sttY = endX = endY = -1;
  cin >> W >> H;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      cin >> arr[i][j];
      if(arr[i][j] == 'C' && sttX == -1) { sttX=i; sttY=j; }
      else if(arr[i][j] == 'C' && endX == -1) { endX=i; endY=j; }
    }
  }
  cout << bfs(sttX,sttY) << endl;
  return 0;
}
