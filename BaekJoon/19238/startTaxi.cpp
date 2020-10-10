#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

int N, M, Fuel; // Fuel: 잔여연료량
int arr[21][21];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

typedef struct {
  int idx, x, y, dist, dest; // dist:택시와의 거리, dest:목적지까지의 거리
} USER;
vector<USER> userVec;
vector<pair<int, int>> destVec;
int taxiX, taxiY;

bool available(int x, int y){ return x > 0 && y > 0 && x <= N && y <= N && arr[x][y] == 0; }

typedef struct {
  int x, y, d;
} ELEM;

int get_dest_bfs(int i){
  queue<ELEM> bfsQ;
  bfsQ.push(ELEM{userVec[i].x, userVec[i].y, 0});
  bool visit[21][21] = {0, };

  while(!bfsQ.empty()){
    ELEM qTop = bfsQ.front();
    bfsQ.pop();

    if(qTop.x == destVec[i].first && qTop.y == destVec[i].second) return qTop.d;
    else {
      for (int j = 0; j < 4; j++) {
        int nx = qTop.x + dx[j];
        int ny = qTop.y + dy[j];
        if(available(nx, ny) && !visit[nx][ny]) {
          bfsQ.push(ELEM{nx, ny, qTop.d+1});
          visit[nx][ny] = true;
        }
      }
    }
  }
  return -1;
}

void get_dist_to_dest(){
  // 각 손님의 위치에서부터 목적지까지의 거리를 미리 계산
  for (int i = 0; i < M; i++) {
    userVec[i].dest = get_dest_bfs(i);
  }
}

int get_taxi_dist_bfs(int i){
  queue<ELEM> bfsQ;
  bfsQ.push(ELEM{userVec[i].x, userVec[i].y, 0});
  bool visit[21][21] = {0, };

  while(!bfsQ.empty()){
    ELEM qTop = bfsQ.front();
    bfsQ.pop();

    if(qTop.x == taxiX && qTop.y == taxiY) return qTop.d;
    else {
      for (int j = 0; j < 4; j++) {
        int nx = qTop.x + dx[j];
        int ny = qTop.y + dy[j];
        if(available(nx, ny) && !visit[nx][ny]) {
          bfsQ.push(ELEM{nx, ny, qTop.d+1});
          visit[nx][ny] = true;
        }
      }
    }
  }
  return -1;
}

bool cmp_user(USER &u1, USER &u2){
  if(u1.dist == u2.dist && u1.x == u2.x) return u1.y < u2.y;
  else if(u1.dist == u2.dist) return u1.x < u2.x;
  else return u1.dist < u2.dist;
}

int start_taxi(){
  for (int i = 0; i < M; i++) {
    // 1. BFS로 택시 to 시민거리 모두 구함
    for (int j = 0; j < userVec.size(); j++) userVec[j].dist = get_taxi_dist_bfs(j);
    // 2. 택시-시민거리, 행번호, 열번호 순으로 정렬
    sort(userVec.begin(), userVec.end(), cmp_user);
    // 3. 잔여 연료량 체크해서 나머지 목적지까지 도달 못하면 -1 반환
    if(userVec.front().dist + userVec.front().dest > Fuel) return -1;
    else if(userVec.front().dist == -1) return -1; // 반례: 도달 불가능한 목적지가 하나라도 있다면 완전한 택시영업 불가능
    else {
      // 4. 도달 가능하면 잔여연료량 업데이트 후 나머지 순회
      taxiX = destVec[userVec.front().idx].first;
      taxiY = destVec[userVec.front().idx].second;
      Fuel = Fuel - userVec.front().dist + userVec.front().dest;
      reverse(userVec.begin(), userVec.end());
      userVec.pop_back();
    }
  }
  return Fuel;
}

int main(){
  cin >> N >> M >> Fuel;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> arr[i+1][j+1];
    }
  }
  cin >> taxiX >> taxiY;

  for (int i = 0; i < M; i++) {
    USER user;
    cin >> user.x >> user.y;
    user.idx = i;
    userVec.push_back(user);
    int destX, destY;
    cin >> destX >> destY;
    destVec.push_back(pair<int, int>(destX, destY));
  }

  get_dist_to_dest();
  cout << start_taxi() << endl;

  return 0;
}
