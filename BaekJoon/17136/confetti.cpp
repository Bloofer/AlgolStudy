#include <iostream>
#include <climits>
using namespace std;

int confetti[6] = {0, 5, 5, 5, 5, 5};
int arr[10][10] = {0, };
bool chk[10][10] = {0, };
bool endCond = false;
int ans = INT_MAX;

bool color_available(int x, int y, int size){
  bool chk = true;
  for (int i = x; i < x+size; i++) {
    for (int j = y; j < y+size; j++) {
      chk &= (arr[i][j] == 1);
    }
  }
  return chk;
}

void paint_color(int x, int y, int size, int n){
  for (int i = x; i < x+size; i++) {
    for (int j = y; j < y+size; j++) {
      arr[i][j] = n;
    }
  }
}

bool chk_arr(){
  bool chk = true;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      chk &= (arr[i][j] == 0);
    }
  }
  return chk;
}

void dfs(int x, int y, int size, int cnt){
// 1. 10*10 돌면서 5~1까지 큰 것 순으로 색종이 배치
// 2. chk 배열 없으면서 arr에 해당 색종이 놓을 수 있는 경우만
// 3. confetti 배열 증감시키며 확인
  if(endCond) return;
  if(cnt >= ans) return;
  // cout << "ans:" << ans << "cnt:" << cnt << " " << "size:" << size << " " << x << ',' << y << endl;
  // for (int i = 0; i < 10; i++) {
  //   for (int j = 0; j < 10; j++) {
  //     cout << arr[i][j];
  //   }
  //   cout << endl;
  // }
  // int s = 0;
  // cin >> s;
  for (int i = x; i <= 10-size; i++) {
    for (int j = 0; j <= 10-size; j++) {
      if(i==x && j<y) continue;
      // recursive case
      if(!chk[i][j] && arr[i][j] && color_available(i,j,size)){
        // 만약, 2. chk 배열 없으면서 arr에 해당 색종이 놓을 수 있는 경우만
        chk[i][j] = true;
        paint_color(i,j,size,0);
        confetti[size]--;
        if(size>1 && confetti[size]==0) dfs(i,j,size-1,cnt+1);
        else dfs(i,j,size,cnt+1);
        confetti[size]++;
        paint_color(i,j,size,1);
        chk[i][j] = false;
      }
      // base case
      if((i==9 && j==9 && size==1) || (size==1 && confetti[1]==0)){
        if(ans > cnt && chk_arr()) {
          ans = cnt;
          endCond = true;
        }
        return;
      }
      // return case
      if(i==10-size && j==10-size && size!=1){
        dfs(0,0,size-1,cnt);
      }
    }
  }
}

int main(){
  bool allZeros = true;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      cin >> arr[i][j];
      allZeros &= (arr[i][j] == 0);
    }
  }
  if(!allZeros) {
    dfs(0,0,5,0);
    if(ans == INT_MAX) cout << -1 << endl;
    else cout << ans << endl;
  }
  else cout << 0 << endl;

  return 0;
}
