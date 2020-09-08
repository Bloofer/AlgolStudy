#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int disc[50][50];
int N, M, T;
typedef struct{
  int x, d, k;
}ROTATE;
vector<ROTATE> rVec;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
typedef struct{
  int x, y, len;
}QSTRUCT;

void test_print(){
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cout << disc[i][j] << " ";
    }
    cout << endl;
  }
}

void rotate_cw(int x, int k){ // x번 원판 k-길이만큼 시계방향 회전
  int tmp[M] = {0, };
  for (int i = 0; i < M; i++) tmp[i] = disc[x][i];
  for (int i = 0; i < M; i++) disc[x][(i+k)%M] = tmp[i];
}

void rotate_ccw(int x, int k){ // x번 원판 k-길이만큼 반시계방향 회전
  int tmp[M] = {0, };
  for (int i = 0; i < M; i++) tmp[i] = disc[x][i];
  for (int i = 0; i < M; i++) disc[x][(i-k+M)%M] = tmp[i];
}

bool available(int x, int y){
  return x >= 0 && y >= 0 && x < N && y < M;
}

bool BFS(int x, int y, bool (*visit)[50]){
  // BFS 함수
  queue<QSTRUCT> bfsQ;
  bfsQ.push(QSTRUCT{x,y,0});
  bool check = false;

  while(!bfsQ.empty()){
    int nx = bfsQ.front().x;
    int ny = bfsQ.front().y;
    int len = bfsQ.front().len;
    int num = disc[nx][ny];
    bfsQ.pop();
    visit[nx][ny] = true;
    if(len > 0) {
      disc[nx][ny] = 0;
      check = true;
    }

    for (int i = 0; i < 4; i++) {
      // 일반적인 BFS로 탐사할 경우 Circular 형태의 원형 구조를 탐사하지 못한다.
      // 그래서 아래와 같이 M-1<->0의 인덱스가 서로 탐사할 수 있도록 y의 인덱싱 처리를 한다.
      int nny = (ny+dy[i]+M)%M;
      if(available(nx+dx[i], nny) && !visit[nx+dx[i]][nny] && disc[nx+dx[i]][nny]!=0 && disc[nx+dx[i]][nny]==num) {
        if(len == 0) disc[nx][ny] = 0;
        bfsQ.push(QSTRUCT{nx+dx[i], nny, len+1});
      }
    }
  }
  return check;
}

bool find_cont_n_id() { // 인접하면서 동일한 수를 찾아 지우는 함수
  bool visit[N][50] = {0, };
  bool check = false;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if(!visit[i][j] && disc[i][j]!=0){
        check |= BFS(i,j,visit);
        visit[i][j] = true;
      }
    }
  }
  return check;
}

void rotate_disc(int x, int d, int k){
  // 1. 번호판 x-배수번호의 원판을 d(0:시계,1:반시계)방향으로 k칸 회전
  for (int i = x; i-1 < N; i+=x) {
    if(d == 0) rotate_cw(i-1, k);
    else rotate_ccw(i-1, k);
  }

  // 2. 원판에 수가 남아있으면 인접하면서 같은수를 찾음
  // 2-1. 인접동일수가 있으면 모두 지움(BFS)
  bool check = find_cont_n_id();
  // 2-2. 없으면 원판 적힌수의 평균을 구하고, 평균보다 큰수는 1빼고, 작은수는 1더함(평균 자료형 캐스팅 조심)
  if(!check){
    int sum = 0;
    int cnt = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if(disc[i][j]>0) {
          cnt++;
          sum+=disc[i][j];
        }
      }
    }
    float mean = (float)sum/(float)cnt;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if(disc[i][j]>mean) disc[i][j]--;
        else if(disc[i][j]>0 && disc[i][j]<mean) disc[i][j]++;
      }
    }
  }
}

int get_sum(){
  int sum = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      sum += disc[i][j];
    }
  }
  return sum;
}

int main(){
  cin >> N >> M >> T;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> disc[i][j];
    }
  }
  for (int i = 0; i < T; i++) {
    int x, d, k;
    cin >> x >> d >> k;
    rotate_disc(x, d, k);
  }

  cout << get_sum() << endl;
  return 0;
}
