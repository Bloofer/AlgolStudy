#include <iostream>
#include <string>
#include <math.h>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

int arr[15][15] = {0, };
int N, M, D;
int maxKill = INT_MIN;

typedef struct{
  int x, y, dist;
} ENEMY;

int get_dist(int x1, int y1, int x2, int y2){
  return abs(x1 - x2) + abs(y1 - y2);
}

int get_max(int a, int b){
  return a > b ? a : b;
}

bool comp(ENEMY e1, ENEMY e2){
  if(e1.dist == e2.dist) return (e1.y < e2.y);
  else return (e1.dist < e2.dist);
}

void simulate_defense(string s){
  int tmpArr[N][M];
  int killedEnemy = 0;
  int defenseTurn = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      tmpArr[i][j] = arr[i][j];
      if(arr[i][j] == 1 && defenseTurn == 0) defenseTurn = N - i;
    }
  }

  // 각 궁수들의 위치를 저장해 놓음
  int archerX[3], archerY[3];
  archerX[0] = archerX[1] = archerX[2] = N;
  int cnt = 0;
  for (int i = 0; i < s.size(); i++) {
    if(s.at(i) == '1'){
      if(cnt == 0) archerY[0] = i;
      else if(cnt == 1) archerY[1] = i;
      else if(cnt == 2) archerY[2] = i;
      cnt++;
    }
  }

  for (int i = 0; i < defenseTurn; i++) {
    // 1. 각각의 궁수는 동시에 적 하나를 공격
    int toKillX[3], toKillY[3];

    vector<ENEMY> enemVec;
    for (int p = N - defenseTurn; p < N; p++) {
      for (int q = 0; q < M; q++) {
        if(tmpArr[p][q] == 1) {
          ENEMY e;
          e.x = p;
          e.y = q;
          enemVec.push_back(e);
        }
      }
    }

    // 1-1. 적들의 위치를 담은 eVec을 생성, 각각의 궁수별로 위치를 계산하여 넣어줌
    vector<ENEMY> eVec[3];
    for (int j = 0; j < 3; j++) {
      for (auto e:enemVec) {
        e.dist = get_dist(archerX[j], archerY[j], e.x, e.y);
        eVec[j].push_back(e);
      }
      // 1-2. 계산된 적 벡터를 궁수와의 거리기준으로, 거리가 같으면 좌측 우선으로 정렬
      sort(eVec[j].begin(), eVec[j].end(), comp);

      // * 여기서 궁수의 사정거리 D안에 못드는 적은 죽이지 못하므로 제외
      // 1-3. 가장 가까운 위치에 있는 적 벡터의 첫번째 원소를 toKill에 저장하여 다음 판부터 제외
      //      죽일 수 있는 적이 없는 경우 toKillX[j]에 -1을 할당하여 필터링
      if(!eVec[j].empty() && eVec[j].front().dist <= D) {
        toKillX[j] = eVec[j].front().x;
        toKillY[j] = eVec[j].front().y;
      } else {
        toKillX[j] = -1;
      }

    }

    // 2. 공격받은 적은 게임에서 제외됨
    for (int j = 0; j < 3; j++) {
      if(toKillX[j] != -1 && tmpArr[toKillX[j]][toKillY[j]] != 0) {
        tmpArr[toKillX[j]][toKillY[j]] = 0;
        killedEnemy++;
      }
    }

    // 3. 궁수의 공격이 끝나면, 적이 이동
    for (int p = N - 1; p >= N - defenseTurn; p--) {
      for (int q = 0; q < M; q++) {
        if(p == 0) tmpArr[p][q] = 0;
        else{
          tmpArr[p][q] = tmpArr[p-1][q];
        }
      }
    }
  }

  // 4. 모든 적이 격자판에서 제외되고 죽인 적이 계수되면 maxKill에 최대값을 업데이트
  maxKill = get_max(maxKill, killedEnemy);
}

void get_archer_pos(string s, int archerCnt){
  if(s.size() > M) return;
  if(s.size() == M && archerCnt == 3) {
    simulate_defense(s);
  } else {
    if(archerCnt < 3) get_archer_pos(s + "1", archerCnt + 1);
    get_archer_pos(s + "0", archerCnt);
  }
}

int main(){
  cin >> N >> M >> D;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> arr[i][j];
    }
  }

  get_archer_pos("", 0);
  cout << maxKill;

  return 0;
}
