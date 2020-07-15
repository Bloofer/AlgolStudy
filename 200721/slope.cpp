#include <iostream>
#include <vector>
using namespace std;

int arr[100][100] = {0, };
int N, L;

bool check_slope(vector<int> &v){
  // 모든 칸의 높이가 같은 경우 true 반환
  bool same = true;
  for(auto vv:v) same &= (vv == v[0]);
  if(same) return true;

  // 아닌경우 아래의 흐름에 따라 슬로프 검사
  bool slopeInst[N] = {0, };
  for (int i = 0; i < N-1; i++) {
    if(v[i] == v[i+1]) continue;
    else if((v[i] - v[i+1]) == 1) {
      // 내려가는 지형; 뒤쪽 인덱스(낮은 높이)에 경사로 설치
      if(i+L > N) return false;
      else {
        same = true && !slopeInst[i+1]; // 뒤 지형의 높이가 같으면서 경사로 설치 안되었는지 여부 확인
        for (int j = i+2; j <= i+L; j++) same &= ( (v[j] == v[i+1]) && !slopeInst[j] );
        if(same){
          for (int j = i+1; j <= i+L; j++) slopeInst[j] = true;
          i += (L - 1);
        } else return false;
      }
    } else if((v[i+1] - v[i]) == 1) {
      // 올라가는 지형; 앞쪽 인덱스(낮은 높이)에 경사로 설치
      if(i-L+1 < 0) return false;
      else {
        same = true && !slopeInst[i]; // 앞 지형의 높이가 같으면서 경사로 설치 안되었는지 여부 확인
        for (int j = i-1; j > i-L; j--) same &= ( (v[j] == v[i]) && !slopeInst[j] );
        if(same){
          for (int j = i-1; j > i-L; j--) slopeInst[j] = true;
        } else return false;
      }
    } else {
      // 높이 차이가 2이상 나는 경우 false
      return false;
    }
  }

  return true;
}

int main(){
  cin >> N >> L;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> arr[i][j];
    }
  }

  int cnt = 0;
  for (int i = 0; i < N; i++) {
    vector<int> rVec, cVec;
    for (int j = 0; j < N; j++) {
      rVec.push_back(arr[i][j]);
      cVec.push_back(arr[j][i]);
    }
    if(check_slope(rVec)) { cnt++; }
    if(check_slope(cVec)) { cnt++; }
    rVec.clear();
    cVec.clear();
  }

  cout << cnt << endl;

  return 0;
}
