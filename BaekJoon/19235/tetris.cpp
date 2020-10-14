#include <iostream>
#include <cstring>
using namespace std;

int N;
int BLUE[4][6] = {0, };
int GREEN[6][4] = {0, };
int score = 0;

bool tetris_blue(){
  // BLUE의 테트리스를 확인해서 존재시 해당 열을 제거하고 true 반환, 테트리스 없으면 false
  bool isTetris = false;
  for (int i = 2; i < 6; i++) {
    bool check = true;
    for (int j = 0; j < 4; j++) {
      check &= (BLUE[j][i] > 0);
    }
    if(check) { BLUE[0][i] = BLUE[1][i] = BLUE[2][i] = BLUE[3][i] = 0; isTetris = true; score++; } // 테트리스 발견시 해당 열 제거
  }
  return isTetris;
}

bool tetris_green(){
  // GREEN의 테트리스를 확인해서 존재시 해당 행을 제거하고 true 반환, 테트리스 없으면 false
  bool isTetris = false;
  for (int i = 2; i < 6; i++) {
    bool check = true;
    for (int j = 0; j < 4; j++) {
      check &= (GREEN[i][j] > 0);
    }
    if(check) { memset(GREEN[i], 0, sizeof(int)*4); isTetris = true; score++; } // 테트리스 발견시 해당 열 제거
  }
  return isTetris;
}

void push_block_blue(){
  // 테트리스 이후 BLUE/GREEN의 연한구역에 블록을 처음 놓는 시작점
  bool changeBlue;
  do{
    changeBlue = false;
    for (int i = 4; i >= 0; i--) {
      for (int j = 0; j < 4; j++) {
        if(BLUE[j][i] == 1 || BLUE[j][i] == 2){
          if(BLUE[j][i+1] == 0) {
            swap(BLUE[j][i], BLUE[j][i+1]);
            changeBlue = true;
          }
        } else if(BLUE[j][i] == 3){
          if(BLUE[j][i+1] == 0 && BLUE[j+1][i+1] == 0) {
            swap(BLUE[j][i], BLUE[j][i+1]);
            swap(BLUE[j+1][i], BLUE[j+1][i+1]);
            changeBlue = true;
          }
          j++;
        }
      }
    }
  } while(changeBlue);
}

void push_block_green(){
  bool changeGreen;
  do{
    changeGreen = false;
    for (int i = 4; i >= 0; i--) {
      for (int j = 0; j < 4; j++) {
        if(GREEN[i][j] == 1 || GREEN[i][j] == 3){
          if(GREEN[i+1][j] == 0) {
            swap(GREEN[i][j], GREEN[i+1][j]);
            changeGreen = true;
          }
        } else if(GREEN[i][j] == 2){
          if(GREEN[i+1][j] == 0 && GREEN[i+1][j+1] == 0) {
            swap(GREEN[i][j], GREEN[i+1][j]);
            swap(GREEN[i][j+1], GREEN[i+1][j+1]);
            changeGreen = true;
          }
          j++;
        }
      }
    }
  } while(changeGreen);

}


int check_vague_blue(){
  // BLUE의 연한구역내 블록 존재여부 확인, 쌓여있는 열의 갯수 반환
  int check = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      if(BLUE[j][i] > 0) { check++; break; }
    }
  }
  return check;
}

int check_vague_green(){
  // GREEN의 연한구역내 블록 존재여부 확인, 쌓여있는 행의 갯수 반환
  int check = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      if(GREEN[i][j] > 0) { check++; break; }
    }
  }
  return check;
}

void put_block(int t, int x, int y){
  // BLUE/GREEN의 연한구역에 블록을 처음 놓는 시작점
  // 모든 반복에서 연한구역에 블록이 없을 때까지 내리기 때문에 블록의 시작점은 연한구역으로 함
  if(t == 1) {
    for (int i = 1; i < 6; i++) {
      if(i == 5) BLUE[x][i] = 1;
      else if(BLUE[x][i+1] > 0) { BLUE[x][i] = 1; break; }
    }
  } else if(t == 2) {
    for (int i = 1; i < 6; i++) {
      if(i == 5) BLUE[x][i] = BLUE[x][i-1] = 2;
      else if(BLUE[x][i+1] > 0) { BLUE[x][i] = BLUE[x][i-1] = 2; break; }
    }
  } else if(t == 3) {
    for (int i = 1; i < 6; i++) {
      if(i == 5) BLUE[x][i] = BLUE[x+1][i] = 3;
      else if(BLUE[x][i+1] > 0 || BLUE[x+1][i+1] > 0) { BLUE[x][i] = BLUE[x+1][i] = 3; break; }
    }
  }

  if(t == 1) {
    for (int i = 1; i < 6; i++) {
      if(i == 5) GREEN[i][y] = 1;
      else if(GREEN[i+1][y] > 0) { GREEN[i][y] = 1; break; }
    }
  } else if(t == 2) {
    for (int i = 1; i < 6; i++) {
      if(i == 5) GREEN[i][y] = GREEN[i][y+1] = 2;
      else if(GREEN[i+1][y] > 0 || GREEN[i+1][y+1] > 0) { GREEN[i][y] = GREEN[i][y+1] = 2; break; }
    }
  } else if(t == 3) {
    for (int i = 1; i < 6; i++) {
      if(i == 5) GREEN[i][y] = GREEN[i-1][y] = 3;
      else if(GREEN[i+1][y] > 0) { GREEN[i][y] = GREEN[i-1][y] = 3; break; }
    }
  }
}

int count_blocks(){
  int count = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 6; j++) {
      if(BLUE[i][j] > 0) count++;
    }
  }

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 4; j++) {
      if(GREEN[i][j] > 0) count++;
    }
  }
  return count;
}


int main(){
  cin >> N;
  for (int i = 0; i < N; i++) {
    int t, x, y; // t 도형모양 1:1*1, 2:1*2, 3:2*1
    cin >> t >> x >> y;
    put_block(t, x, y);
    while(tetris_blue()){ push_block_blue(); }
    while(tetris_green()){ push_block_green(); }

    int vagueBlue = check_vague_blue();
    if(vagueBlue > 0) {
      for (int i = 5-vagueBlue; i >= 2-vagueBlue; i--) {
        for (int j = 0; j < 4; j++) {
          BLUE[j][i+vagueBlue] = BLUE[j][i];
        }
      }
      for (int i = 2-vagueBlue; i < 2; i++) {
        for (int j = 0; j < 4; j++) { BLUE[j][i] = 0; }
      }
    }
    int vagueGreen = check_vague_green();
    if(vagueGreen > 0) { // vagueBlue
      for (int i = 5-vagueGreen; i >= 2-vagueGreen; i--) {
        for (int j = 0; j < 4; j++) {
          GREEN[i+vagueGreen][j] = GREEN[i][j];
        }
      }
      for (int i = 2-vagueGreen; i < 2; i++) {
        memset(GREEN[i], 0, sizeof(int)*4);
      }
    }
  }

  cout << score << endl;
  cout << count_blocks();

  return 0;
}
