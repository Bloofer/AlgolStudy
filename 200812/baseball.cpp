#include <iostream>
#include <string>
#include <climits>
using namespace std;

int N;
int arr[50][9] = {0, };
int playArr[50][9] = {0, };
bool visit[9] = {0, };
int maxVal = INT_MIN;

int get_max(int a, int b){
  return a > b ? a : b;
}

void simulate_play(string s){
  // 1. 해당 타자 조합으로 들어온 이닝 정보 배열을 복사
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 9; j++) {
      playArr[i][j] = arr[i][s.at(j) - '0'];
    }
  }
  // 2. N 이닝동안 플레이를 반복
  int score = 0;
  int playerNum = 0;
  for (int i = 0; i < N; i++) {
    // 3. while 문 안에서, 아웃이 3개 누적되기 전까지 1/2/3루에 선수를 진출시킴
    int outCnt = 0;
    bool base[3] = {0, };
    while (outCnt < 3) {
      // 4. 안타-1루씩, 2루타-2루씩, 3루타-3루씩, 홈런-모두 홈까지 진루
      if(playArr[i][playerNum] == 0){ // 아웃인 경우
        outCnt++;
      } else if(playArr[i][playerNum] == 1){ // 안타인 경우
        if(base[2]){
          score++;
          base[2] = false;
        }
        if(base[1]){
          base[2] = true;
          base[1] = false;
        }
        if(base[0]){
          base[1] = true;
        }
        base[0] = true;
      } else if(playArr[i][playerNum] == 2){ // 2루타인 경우
        if(base[2]){
          score++;
          base[2] = false;
        }
        if(base[1]){
          score++;
          base[1] = false;
        }
        if(base[0]){
          base[2] = true;
          base[0] = false;
        }
        base[1] = true;
      } else if(playArr[i][playerNum] == 3){ // 3루타인 경우
        if(base[2]){
          score++;
          base[2] = false;
        }
        if(base[1]){
          score++;
          base[1] = false;
        }
        if(base[0]){
          score++;
          base[0] = false;
        }
        base[2] = true;
      } else if(playArr[i][playerNum] == 4){ // 홈런인 경우
        for (int j = 0; j < 3; j++) {
          if(base[j]) score++;
          base[j] = false;
        }
        score++;
      }
      playerNum++;
      playerNum%=9;
    }
  }
  // 5. 모든 이닝 플레이가 완료시 해당 점수를 최대값에 업데이트
  maxVal = get_max(maxVal, score);
}

void dfs(string s){
  if(s.size() == 9) {
    if(s.at(3) == '0'){
      //cout << s << endl;
      simulate_play(s); }
  } else {
    for (int i = 0; i < 9; i++) {
      if(!visit[i]){
        visit[i] = true;
        string ss(1, i + '0');
        dfs(s+ss);
        visit[i] = false;
      }
    }
  }
}

int main(){
  cin >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 9; j++) {
      cin >> arr[i][j];
    }
  }

  dfs("");
  cout << maxVal << endl;

  return 0;
}
