#include <iostream>
#include <queue>
using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
char arr[100][100];
int cnt[100][100] = {0, };
bool visit[100][100] = {0, };
int W, H;

void bfs(int x, int y){
  queue< pair<int, int> > bfsQ;
  bfsQ.push(pair<int, int>(x, y));

  while(!bfsQ.empty()){
    pair<int, int> p = bfsQ.front();
    bfsQ.pop();
    for (int i = 0; i < 4; i++) {
      int nx = p.first + dx[i];
      int ny = p.second + dy[i];
      while(nx >= 0 && ny >= 0 && nx < H && ny < W && arr[nx][ny] != '*'){
        if(cnt[nx][ny] == 0){
          cnt[nx][ny] = cnt[p.first][p.second] + 1;
          bfsQ.push(pair<int, int>(nx, ny));
        }

        nx += dx[i];
        ny += dy[i];
      }
    }
  }
}

int main(){
  cin >> W >> H;
  int x, y;
  int endX, endY;
  bool chk = false;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      cin >> arr[i][j];
      if(arr[i][j] == 'C' && !chk) { x=i; y=j; chk=true; }
      else if(arr[i][j] == 'C' && chk) { endX=i; endY=j; }
    }
  }

  bfs(x,y);
  cout << cnt[endX][endY]-1 << endl;

  return 0;
}
