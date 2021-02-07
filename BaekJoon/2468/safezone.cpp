#include <iostream>
#include <climits>
#include <cstring>
#include <queue>
using namespace std;

int N;
bool height[101] = {0, };
int arr[100][100] = {0, };
bool visit[100][100] = {0, };
int ans = 1; // 아무도 물에 잠기지 않는 경우가 초기 값
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool available(int x, int y){ return x>=0 && y>=0 && x<N && y<N; }
void bfs(int x, int y, int d){
  // 안전지역을 체크 함
  queue< pair<int, int> > bfsQ;
  bfsQ.push(pair<int, int>(x, y));
  visit[x][y] = true;

  while(!bfsQ.empty()){
    pair<int, int> p = bfsQ.front();
    bfsQ.pop();

    for (int i = 0; i < 4; i++) {
      int nx = p.first + dx[i];
      int ny = p.second + dy[i];
      if(available(nx, ny) && !visit[nx][ny] && arr[nx][ny]>d) { visit[nx][ny] = true; bfsQ.push(pair<int, int>(nx, ny)); }
    }
  }
}

int main(){
  cin >> N;
  int min = INT_MAX;
  int max = INT_MIN;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> arr[i][j];
      if(arr[i][j] > max) max = arr[i][j];
      if(arr[i][j] < min) min = arr[i][j];
      height[arr[i][j]-1] = true;
    }
  }
  for (int i = min; i < max; i++) {
    // i: 물에 잠기는 영역 높이
    if(!height[i]) continue;
    int cnt = 0;
    memset(visit, 0, sizeof(visit));
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        if(arr[j][k]>i && !visit[j][k]){ bfs(j,k,i); cnt++; }
      }
    }
    if(cnt > ans) ans = cnt;
  }
  cout << ans << endl;

  return 0;
}
