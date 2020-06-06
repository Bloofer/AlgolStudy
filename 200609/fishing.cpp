#include <iostream>
#include <vector>
using namespace std;

int R, C, M;
vector<int> arr[100][100]; // 각 좌표에 상어 인덱스 저장
bool deadShark[10001] = {0, };
typedef struct{
  int s, d, z; // s:속력, d:이동방향(1:↑, 2:↓, 3:→, 4:←), z:크기
  int r, c;
}SHARK;
int fishSum = 0;

void move_shark(SHARK &s, int idx){
  int nextR = s.r;
  int nextC = s.c;
  // 1. 이동방향을 보고, s.d가 1/2인 경우 nextR을 움직임, 3/4인 경우 nextC를 움직임
  if(s.d == 1){
    // 2. 남은 이동거리(rem) = s.s로 해놓고 벽만나면 방향 전환되며 이동
    //    s.d는 1/2일때 (s.s / R) 만큼 방향전환, s.r + (s.s % R) 만큼 이동
    if(s.r - s.s >= 0){
      nextR -= s.s;
    } else{
      int turn, move;
      turn = (s.s - s.r) / (R - 1);
      move = (s.s - s.r) % (R - 1);

      if(turn%2 == 1) {
        nextR = R - 1 - move;
        if(move == 0) s.d = 2;
      } else {
        nextR = move;
        if(move != 0) s.d = 2;
      }
    }
  } else if(s.d == 2){
    if(s.r + s.s < R){
      nextR += s.s;
    } else{
      int turn, move;
      turn = (s.s + s.r) / (R - 1);
      move = (s.s + s.r) % (R - 1);

      if(turn%2 == 0) {
        nextR = move;
        if(move == 0) s.d = 1;
      } else {
        nextR = R - 1 - move;
        if(move != 0) s.d = 1;
      }
    }
  } else if(s.d == 4){
    if(s.c - s.s >= 0){
      nextC -= s.s;
    } else{
      int turn, move;
      turn = (s.s - s.c) / (C - 1);
      move = (s.s - s.c) % (C - 1);

      if(turn%2 == 1) {
        nextC = C - 1 - move;
        if(move == 0) s.d = 3;
      } else {
        nextC = move;
        if(move != 0) s.d = 3;
      }
    }
  } else if(s.d == 3){
    if(s.c + s.s < C){
      nextC += s.s;
    } else{
      int turn, move;
      turn = (s.s + s.c) / (C - 1);
      move = (s.s + s.c) % (C - 1);

      if(turn%2 == 0) {
        nextC = move;
        if(move == 0) s.d = 4;
      } else {
        nextC = C - 1 - move;
        if(move != 0) s.d = 4;
      }
    }
  }

  // 3. 이동 후에는 해당 좌표의 벡터에서 상어 빼고, 새 좌표의 벡터에 삽입
  vector<int> tmp;
  for(auto ss: arr[s.r][s.c]) if(ss != idx) tmp.push_back(ss);
  arr[s.r][s.c] = tmp;
  s.r = nextR;
  s.c = nextC;
  arr[s.r][s.c].push_back(idx);
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
    // 1. 낚시왕은 이동하여 해당 열의 가장 위쪽 상어를 찾고, 있으면 전체 Sum에 추가, 잡은 상어는 벡터에서 제거
    for (int j = 0; j < R; j++) {
      if(arr[j][i].empty()) continue;
      else {
        fishSum += sharkVec[arr[j][i].front()-1].z;
        deadShark[arr[j][i].front()] = true;
        arr[j][i].clear();
        break;
      }
    }

    // 2. 상어들을 전부 이동시킴
    for (int i = 0; i < sharkVec.size(); i++) {
      if(!deadShark[i+1]) move_shark(sharkVec[i], i+1);
    }

    // 3. 이동한 인덱스의 벡터에 상어가 여러마리 있는경우 그 중 크기가 가장 큰 놈만 남기고 다 죽임
    for (int j = 0; j < R; j++) {
      for (int k = 0; k < C; k++) {
        if(arr[j][k].empty()) continue;
        else {
          vector<int> tmp;
          int bigIdx;
          int bigSize = 0;
          for(auto ss: arr[j][k]){
            deadShark[ss] = true;
            if(sharkVec[ss-1].z > bigSize){
              bigSize = sharkVec[ss-1].z;
              bigIdx = ss;
            }
          }
          deadShark[bigIdx] = false;
          tmp.push_back(bigIdx);
          arr[j][k] = tmp;
        }
      }
    }
  }

  cout << fishSum << endl;
  return 0;
}
