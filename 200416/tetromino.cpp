#include <iostream>
#include <climits>
#include <string>
using namespace std;

int N, M;
int arr[500][500];

int dx[8] = {0,1,0,-1,1,-1,-1,1};
int dy[8] = {1,0,-1,0,-1,-1,1,1};
// 0:→, 1:↓, 2:←, 3:↑, 4:↙, 5:↖, 6:↗, 7:↘ (4~7은 5번 도형 그리는 용)

int maxVal = INT_MIN;
string shape[7] = {"000", "012", "100", "300", "010", "030", "004"};
string dir[7] = {"01", "0", "0123", "0123", "01", "01", "0123"};
// 1: □□□□ 2: □□ 3: □   4: □□□ 5: □□  6:  □□ 7: □□□
//            □□    □□□    □       □□    □□      □
// 각 도형별 회전가능방향
// 1:X2, 2:X1, 3:X4, 4:X4, 5:X2, 6:X2, 7:X4
// 각 도형별 좌표 그리는 방법(0~3:방향)
// 1:000, 2:012, 3:100, 4:300, 5:010, 6:030 7:004

bool is_valid(int x, int y){
  return (x >= 0 && x < N && y >= 0 && y < M);
}

int get_max(int a, int b){
  return a > b ? a : b;
}

void check_pos(int x, int y){
  // 1. 해당 좌표부터 엔트리 값 shape로 좌표이동하며 sum에 더함
  // 2. for loop안에서 360도 회전하며 한 모양에 대한 4방향 확인 후 다음 모양으로
  //    A. 초기 x,y 좌표 가져옴
  //    B. shape와 각도 i에 따라 다음 좌표가져오고, 좌표 하나라도 invalid면 최대값 계산에 배제
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < dir[i].size(); j++) {
      int sum = arr[x][y];
      bool chk = true;
      int xx = x;
      int yy = y;
      for (int k = 0; k < shape[i].size(); k++) {
        xx += dx[(shape[i][k] + j - '0') % 4];
        yy += dy[(shape[i][k] + j - '0') % 4];
        if(!is_valid(xx, yy)) break;
        sum += arr[xx][yy];
        if(k == shape[i].size() - 1) maxVal = get_max(sum, maxVal);
      }
    }
  }

  // 7번 도형은 그릴 때 대각선 이동이 필요하므로 따로 처리
  for (int j = 0; j < dir[6].size(); j++) {
    int sum = arr[x][y];
    bool chk = true;
    int xx = x;
    int yy = y;
    for (int k = 0; k < shape[6].size(); k++) {
      if(shape[6][k] + j - '0' >= 4) {
        xx += dx[(shape[6][k] + j - '0') % 4 + 4];
        yy += dy[(shape[6][k] + j - '0') % 4 + 4];
      } else {
        xx += dx[(shape[6][k] + j - '0') % 4];
        yy += dy[(shape[6][k] + j - '0') % 4];
      }
      if(!is_valid(xx, yy)) break;
      sum += arr[xx][yy];
      if(k == shape[6].size() - 1) maxVal = get_max(sum, maxVal);
    }
  }
}

int main(){
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> arr[i][j];
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      check_pos(i, j);
    }
  }
  cout << maxVal;
  return 0;
}
