#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int N;
int arr[20][20] = {0, };      // 지역별 인구를 나타내는 배열
int voteArr[20][20] = {0, };  // 지역별 선거구 번호를 나타내는 배열
int minVal = INT_MAX;

int get_min(int a, int b){
  return a < b ? a : b;
}

int get_diff(){
  // 인구가 가장 많은 선거구와 가장 적은 선거구의 인구 차이 반환
  vector<int> populationVec = {0,0,0,0,0};
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      populationVec[voteArr[i][j]-1] += arr[i][j];
      voteArr[i][j] = 0; // 다음 선거구 계산을 위한 초기화
    }
  }
  sort(populationVec.begin(), populationVec.end());
  return populationVec.back() - populationVec.front();
}

void color_area(int x, int y, int d1, int d2){
  // 1번 선거구: 1 ≤ r < x+d1, 1 ≤ c ≤ y
  int dy = y+1;
  for (int r = 0; r < x+d1; r++) {
    if(r >= x) dy--;
    for (int c = 0; c < dy; c++) {
      voteArr[r][c] = 1;
    }
  }
  // 2번 선거구: 1 ≤ r ≤ x+d2, y < c ≤ N
  dy = y+1;
  for (int r = 0; r <= x+d2; r++) {
    for (int c = dy; c < N; c++) {
      voteArr[r][c] = 2;
    }
    if(r >= x) dy++;
  }
  // 3번 선거구: x+d1 ≤ r ≤ N, 1 ≤ c < y-d1+d2
  dy = y-d1;
  for (int r = x+d1; r < N; r++) {
    for (int c = 0; c < dy; c++) {
      voteArr[r][c] = 3;
    }
    if(r <= x+d1+d2) dy++;
  }
  // 4번 선거구: x+d2 < r ≤ N, y-d1+d2 ≤ c ≤ N
  dy = y+d2;
  for (int r = x+d2+1; r < N; r++) {
    for (int c = dy; c < N; c++) {
      voteArr[r][c] = 4;
    }
    if(r <= x+d1+d2) dy--;
  }
  // 5번 선거구
  for (int r = 0; r < N; r++) {
    for (int c = 0; c < N; c++) {
      if(voteArr[r][c]==0) voteArr[r][c] = 5;
    }
  }
}

void divide_area(){
  for (int x = 0; x < N; x++) {
    for (int y = 0; y < N; y++) {
      for (int d1 = 1; y-d1 >= 0 && y-d1 < y; d1++) {
        for (int d2 = 1; y+d2 < N && y+d2 >= 0; d2++) {
          // 기준점과 경계: d1, d2 ≥ 1, 1 ≤ x < x+d1+d2 ≤ N, 1 ≤ y-d1 < y < y+d2 ≤ N
          if(x+d1+d2 < N){
            for (int i = 0; i <= d1; i++) {
              for (int j = 0; j <= d2; j++) {
                voteArr[x+i][y-i] = 5;        // 경계선1: (x, y), (x+1, y-1), ..., (x+d1, y-d1)
                voteArr[x+j][y+j] = 5;        // 경계선2: (x, y), (x+1, y+1), ..., (x+d2, y+d2)
                voteArr[x+d1+j][y-d1+j] = 5;  // 경계선3: (x+d1, y-d1), (x+d1+1, y-d1+1), ... (x+d1+d2, y-d1+d2)
                voteArr[x+d2+i][y+d2-i] = 5;  // 경계선4: (x+d2, y+d2), (x+d2+1, y+d2-1), ..., (x+d2+d1, y+d2-d1)
              }
            }
            color_area(x,y,d1,d2);
            minVal = get_min(minVal, get_diff());
          }
        }
      }
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
  divide_area();
  cout << minVal << endl;

  return 0;
}
