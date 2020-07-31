#include <iostream>
using namespace std;

int arr[16][16] = {0, };
int N;
int cnt = 0;
enum PipeState {
  HRZ = 0, // 가로
  VTC,     // 세로
  DIAG,    // 대각선
} pState;

bool available(int x, int y, PipeState ps){
  if(x >= N || y >= N) return false;

  if(ps == HRZ){
    return (arr[x][y] == 0);
  } else if(ps == VTC){
    return (arr[x][y] == 0);
  } else if(ps == DIAG){
    return (arr[x][y] == 0 && arr[x][y-1] == 0 && arr[x-1][y] == 0);
  }
  return false;
}

void dfs(int x, int y, PipeState ps){
  if(x == N-1 && y == N-1) cnt++;
  else{
    if(available(x+1, y+1, DIAG)) dfs(x+1, y+1, DIAG);
    if(ps == HRZ){
      if(available(x, y+1, HRZ)) dfs(x, y+1, HRZ);
    } else if(ps == VTC){
      if(available(x+1, y, VTC)) dfs(x+1, y, VTC);
    } else if(ps == DIAG){
      if(available(x, y+1, HRZ)) dfs(x, y+1, HRZ);
      if(available(x+1, y, VTC)) dfs(x+1, y, VTC);
    }
  }
}

int main(){
  cin >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> arr[i][j];
    }
  }
  dfs(0, 1, HRZ);
  cout << cnt << endl;

  return 0;
}
