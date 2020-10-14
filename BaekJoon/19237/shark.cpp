#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, K;
typedef struct{
  int n, sec; // n: 상어 냄새 번호, sec: 해당 냄새가 체류한 시간
  vector<int> sharks;
}ENTRY;
ENTRY arr[21][21] = {0, }; // 상어 냄새 체크 배열
bool deadCheck[441] = {0, }; // 상어 생존 체크 배열; 1일때 죽음

typedef struct{
  int x, y, dir;
}SHARK;
SHARK sharkPos[441];  // 상어 위치정보 배열
int priority[441][5][5] = {0, }; // 상어번호 1~M, 현재방향 1~4에서의, 방향정보 1~4
int dx[5] = {0, -1, 1, 0, 0}; // 1:상, 2:하, 3:좌, 4:우
int dy[5] = {0, 0, 0, -1, 1};

bool available(int x, int y) { return x >= 0 && y >= 0 && x < N && y < N; }

vector<int> pop_vec(vector<int> &sharks, int val){
  vector<int> tmp;
  for(auto s:sharks) {
    if(s != val) tmp.push_back(s);
  }
  return tmp;
}

int move_shark(){
  int sharkCnt = M;
  int tick = 0;
  while(sharkCnt > 1 && tick <= 1000){
    // 1. 각 상어는 이동한 칸에 냄새를 뿌리고, K초가 지난 냄새는 사라짐
    for (int i = 1; i <= M; i++) {
      if(!deadCheck[i]) {
        arr[sharkPos[i].x][sharkPos[i].y].n = i;
        arr[sharkPos[i].x][sharkPos[i].y].sec = K;
      }
    }

    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        if(arr[j][k].n > 0) {
          arr[j][k].sec--;
          if(arr[j][k].sec < 0) arr[j][k].n = arr[j][k].sec = 0;
        }
      }
    }

    // 2. 1~M번 상어까지 상어 카운트가 1보다 크거나 현재 시간이 1000초 이하면 반복
    for (int i = 1; i <= M; i++) {
      if(deadCheck[i]) continue; // 죽은 상어에 대해서는 이동 제외

      // 3. 각 상어는 인접칸 중 아무 냄새가 없는 칸(방향)을 찾아 벡터에 모은다.
      vector<int> freePos;
      for (int j = 1; j <= 4; j++) {
        int nx = sharkPos[i].x + dx[j];
        int ny = sharkPos[i].y + dy[j];
        if(available(nx, ny) && arr[nx][ny].n == 0) freePos.push_back(j);
      }

      // 4. 만약, 인접칸 중 그런 칸이 없다면 자신의 냄새가 있는 칸을 찾아 벡터에 모은다.
      if(freePos.empty()){
        for (int j = 1; j <= 4; j++) {
          int nx = sharkPos[i].x + dx[j];
          int ny = sharkPos[i].y + dy[j];
          if(available(nx, ny) && arr[nx][ny].n == i) freePos.push_back(j);
        }
      }

      if(freePos.size() == 1){
        // 5. 2/3에서 벡터에 모은 방향이 하나인 경우 그대로 이동 진행
        arr[sharkPos[i].x][sharkPos[i].y].sharks = pop_vec(arr[sharkPos[i].x][sharkPos[i].y].sharks, i);
        sharkPos[i].x += dx[freePos.front()];
        sharkPos[i].y += dy[freePos.front()];
        sharkPos[i].dir = freePos.front();
        arr[sharkPos[i].x][sharkPos[i].y].sharks.push_back(i);
      } else if(!freePos.empty()) {
        // 6. 만약 방향이 여러개라면, 해당 상어번호의 현재 방향을 기준으로 우선순위를 적용하여 우선순위 가장 높은 방향으로 이동
        int d = sharkPos[i].dir;
        for (int j = 1; j <= 4; j++) {
          if(find(freePos.begin(), freePos.end(), priority[i][d][j]) != freePos.end()) {
            arr[sharkPos[i].x][sharkPos[i].y].sharks = pop_vec(arr[sharkPos[i].x][sharkPos[i].y].sharks, i);
            sharkPos[i].x += dx[priority[i][d][j]];
            sharkPos[i].y += dy[priority[i][d][j]];
            sharkPos[i].dir = priority[i][d][j];
            arr[sharkPos[i].x][sharkPos[i].y].sharks.push_back(i);
            break;
          }
        }
      }

    }
    // 7. 이동 후, 만약 해당 칸에 상어가 존재한다면 해당 상어를 제거
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        if(arr[j][k].sharks.size() > 1){
          sort(arr[j][k].sharks.begin(), arr[j][k].sharks.end());
          for (int l = 1; l < arr[j][k].sharks.size(); l++) {
            deadCheck[arr[j][k].sharks[l]] = true;
            sharkCnt--;
          }
          int primeShark = arr[j][k].sharks.front();
          arr[j][k].sharks.clear();
          arr[j][k].sharks.push_back(primeShark);
        }
      }
    }

    tick++;
  }

  if(tick > 1000) return -1;
  else return tick;
}

int main(){
  cin >> N >> M >> K;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> arr[i][j].n;
      if (arr[i][j].n > 0) {
        sharkPos[arr[i][j].n].x = i;
        sharkPos[arr[i][j].n].y = j;
      }
    }
  }
  for (int i = 1; i <= M; i++) cin >> sharkPos[i].dir;
  for (int i = 1; i <= M; i++) {
    for (int j = 1; j <= 4; j++) {
      for (int k = 1; k <= 4; k++) {
        cin >> priority[i][j][k];
      }
    }
  }

  cout << move_shark() << endl;
  return 0;
}
