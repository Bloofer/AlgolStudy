#include <iostream>
#include <climits>
using namespace std;

char arr[101][101];
int W, H;
int sttX, sttY;
int minVal = INT_MAX;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
bool visit[101][101][4] = {0, };

bool available(int x, int y){ return x>=0 && y>=0 && x<H && y<W; }
int get_min(int a, int b){ return a < b ? a : b; }

void dfs(int x, int y, int cnt, int dir){
  if(cnt > minVal) return;
  int nx = x + dx[dir]; int ny = y + dy[dir];
  if(!available(x, y) || arr[x][y] == '*') return;
  else if(arr[x][y]=='C' && (x != sttX || y != sttY)){ minVal = get_min(minVal, cnt); return; }
  else if(arr[x][y]=='.' || (x == sttX && y == sttY)){
    cout << x << "," << y << ":" << dir << endl;
    if(!visit[nx][ny][dir]) {
      visit[x][y][dir] = true;
      dfs(nx,ny,cnt,dir);
      visit[x][y][dir] = false;
    }

    int ndir = (dir+1) % 4;
    nx = x + dx[ndir]; ny = y + dy[ndir];
    if(!visit[nx][ny][ndir]){
      visit[x][y][ndir] = true;
      dfs(nx,ny,cnt+1,ndir);
      visit[x][y][ndir] = false;
    }

    ndir = (dir+3) % 4;
    nx = x + dx[ndir]; ny = y + dy[ndir];
    if(!visit[nx][ny][ndir]){
      visit[x][y][ndir] = true;
      dfs(nx,ny,cnt+1,ndir);
      visit[x][y][ndir] = false;
    }
  }
}

int main(){
  bool chk = false;
  cin >> W >> H;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      cin >> arr[i][j];
      if(arr[i][j] == 'C' && !chk) { sttX=i; sttY=j; chk=true; }
    }
  }

  for (int i = 0; i < 4; i++) {
    visit[sttX][sttY][i] = true;
    dfs(sttX,sttY,0,i);
    visit[sttX][sttY][i] = false;
  }
  cout << minVal << endl;

  return 0;
}
