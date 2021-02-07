#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int N, Q;
int arr[64][64] = {0, };
int tmp[64][64] = {0, };
bool visit[64][64] = {0, };
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void move_block(int x, int y, int n){
  vector< vector<int> > tmpVec;
  for (int j = y; j < y+2*n; j++) {
    vector<int> tmpVecSub;
    for (int i = x+2*n-1; i >= x; i--) {
      tmpVecSub.push_back(arr[i][j]);
    }
    tmpVec.push_back(tmpVecSub);
  }

  for (int i = x; i < x+2*n; i++) {
    for (int j = y; j < y+2*n; j++) {
      arr[i][j] = tmpVec[i-x][j-y];
    }
  }
}

void move_grid(int n){
  if(n == 0) return;
  int d = pow(2, n-1);
  for(int i=0; i<N; i+=2*d){
    for(int j=0; j<N; j+=2*d){
      move_block(i,j,d);
    }
  }
}

bool available(int x, int y) { return x>=0 && y>=0 && x<N && y<N; }

void ice_melt(){
  bool chk[64][64] = {0, };
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int cnt = 0;
      for (int k = 0; k < 4; k++) {
        int nx = i + dx[k];
        int ny = j + dy[k];
        if(available(nx,ny) && arr[nx][ny]>0) cnt++;
      }
      if(cnt < 3 && arr[i][j] > 0) chk[i][j] = true;
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if(chk[i][j] && arr[i][j]>0) arr[i][j]--;
    }
  }
}

int bfs(int x, int y){
  int cnt = 1;
  queue<pair<int, int>> bfsQ;
  bfsQ.push(pair<int, int>(x, y));
  visit[x][y] = true;
  while(!bfsQ.empty()){
    x = bfsQ.front().first;
    y = bfsQ.front().second;
    bfsQ.pop();

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if(available(nx, ny) && !visit[nx][ny] && arr[nx][ny]){
        visit[nx][ny] = true;
        bfsQ.push(pair<int, int>(nx, ny));
        cnt++;
      }
    }
  }

  return cnt;
}

int main(){
  cin >> N >> Q;
  N = pow(2, N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> arr[i][j];
    }
  }

  for (int i = 0; i < Q; i++) {
    int L;
    cin >> L;
    move_grid(L);
    ice_melt();
  }


  int iceCnt = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if(arr[i][j]>0) iceCnt+=arr[i][j];
    }
  }

  int maxBlock = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int bCnt = 0;
      if(!visit[i][j] && arr[i][j]) bCnt = bfs(i,j);
      if(bCnt > maxBlock) maxBlock = bCnt;
    }
  }

  cout << iceCnt << endl << maxBlock << endl;

  return 0;
}
