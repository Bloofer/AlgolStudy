#include <iostream>
#include <vector>
using namespace std;

int R, C, M;
vector<int> arr[100][100]; // 각 좌표에 상어 인덱스 저장
int sharkDead[10000] = {0, }; // 상어가 살아있으면 false, 죽으면 true
typedef struct{
  int s, d, z; // s:속력, d:이동방향(1:↑, 2:↓, 3:→, 4:←), z:크기
  int r, c;
}SHARK;

void test_print(){
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      for (auto s:arr[i][j]) cout << s;
      cout << " ";
    }
    cout << endl;
  }
}

void move_shark(SHARK &s){
  int nextR = s.r;
  int nextC = s.c;
  // 1. 이동방향을 보고, s.d가 1/2인 경우 nextR을 움직임, 3/4인 경우 nextC를 움직임
  if(s.d == 1){
    // 2. 남은 이동거리(rem) = s.s로 해놓고 벽만나면 방향 전환되며 이동
    //    s.d는 1/2일때 (s.s / R) 만큼 방향전환, s.r + (s.s % R) 만큼 이동
    if(s.s - s.r < 0){
      nextR -= s.s;
    } else{
      int turn, move;
      turn = (s.s - s.r) / R;
      move = (s.s - s.r) % R;

      if(turn%2 == 0) nextR = move;
      else {
        s.d = 2;
        nextR = R - move;
      }
    }
  } else if(s.d == 2){
    if(s.s + s.r < R){
      nextR += s.s;
    } else{
      int turn, move;
      turn = (s.s + s.r) / R;
      move = (s.s + s.r) % R;

      if(turn%2 == 0) nextR = R - move;
      else {
        s.d = 1;
        nextR = move;
      }
    }
  }

  // 3. 이동 후에는 해당 좌표의 벡터에서 상어 빼고, 새 좌표의 벡터에 삽입
  s.r = nextR;
}

void print_shark(SHARK &s){
  cout << "(" << s.r << ", " << s.c << "): ";
  cout << s.d << endl;
}

int main(){
  cin >> R >> C >> M;
  vector<SHARK> sharkVec;
  for (int i = 0; i < M; i++) {
    SHARK tmpShark;
    cin >> tmpShark.r >> tmpShark.c >> tmpShark.s >> tmpShark.d >> tmpShark.z;
    tmpShark.r--;
    tmpShark.c--;
    arr[tmpShark.r][tmpShark.c].push_back(i+1);
    sharkVec.push_back(tmpShark);
  }

  for (int i = 0; i < C; i++) {
    // 1. 상어들을 전부 이동시킴
    for (auto s:sharkVec) {
      // move_shark(s);
    }

    // 2. 이동한 인덱스의 벡터에 상어가 여러마리 있는경우 그 중 크기가 가장 큰 놈만 남기고 다 죽임

    // 3. 낚시왕은 이동하여 해당 열의 가장 위쪽 상어를 찾고, 있으면 전체 Sum에 추가, 잡은 상어는 벡터에서 제거
  }

  test_print();
  SHARK s;
  s.r = s.c = s.d = 1;
  s.s = 5;
  print_shark(s);
  move_shark(s);
  print_shark(s);
  move_shark(s);
  print_shark(s);
  move_shark(s);
  print_shark(s);

  return 0;
}
