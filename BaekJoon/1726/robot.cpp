#include <iostream>
#include <queue>
using namespace std;

int M, N;
int arr[100][100];
bool chk[100][100][4] = {0, };
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0}; // 동, 남, 서, 북
int dirMap[5] = {0, 0, 2, 1, 3};

typedef struct{
  int x, y, d, cnt;
} ENTRY;

bool available(int x, int y){ return (x >= 0 && y >= 0 && x < M && y < N); }

int bfs(int sx, int sy, int sd, int ex, int ey, int ed){
  queue<ENTRY> myQueue;
  myQueue.push(ENTRY{sx,sy,sd,0});

  while(!myQueue.empty()){
    ENTRY e = myQueue.front();
    //cout << e.x << " " << e.y << " - " << e.d << " / " << e.cnt << endl;
    if(e.x==ex && e.y==ey && e.d==ed) return e.cnt;
    myQueue.pop();
    // 명령 1. Go k: k는 1, 2 또는 3일 수 있다. 현재 향하고 있는 방향으로 k칸 만큼 움직인다.
    int nx = e.x;
    int ny = e.y;
    if(e.d%2 == 0) {
      for (int i = 0; i < N; i++) {
        ny += dy[e.d];
        if(!available(nx, ny) || arr[nx][ny]==1) break;
        else { chk[nx][ny][e.d] = true; myQueue.push(ENTRY{nx,ny,e.d,e.cnt+1}); }
      }
    } else {
      for (int i = 0; i < M; i++) {
        nx += dx[e.d];
        if(!available(nx, ny) || arr[nx][ny]==1) break;
        else { chk[nx][ny][e.d] = true; myQueue.push(ENTRY{nx,ny,e.d,e.cnt+1}); }
      }
    }
    // 명령 2. Turn dir: dir은 left 또는 right 이며, 각각 왼쪽 또는 오른쪽으로 90° 회전한다.
    if(!chk[e.x][e.y][(e.d+1)%4]) { chk[e.x][e.y][(e.d+1)%4] = true; myQueue.push(ENTRY{e.x,e.y,(e.d+1)%4,e.cnt+1}); }
    //if(!chk[e.x][e.y][(e.d+2)%4]) { chk[e.x][e.y][(e.d+2)%4] = true; myQueue.push(ENTRY{e.x,e.y,(e.d+2)%4,e.cnt+2}); }
    if(!chk[e.x][e.y][(e.d+3)%4]) { chk[e.x][e.y][(e.d+3)%4] = true; myQueue.push(ENTRY{e.x,e.y,(e.d+3)%4,e.cnt+1}); }
  }

  return 0;
}

int main(){
  cin >> M >> N;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      cin >> arr[i][j];
    }
  }
  int startX, startY, startD, endX, endY, endD;
  cin >> startX >> startY >> startD;
  cin >> endX >> endY >> endD;
  startD = dirMap[startD];
  endD = dirMap[endD];

  cout << bfs(startX-1, startY-1, startD, endX-1, endY-1, endD);

  return 0;
}
