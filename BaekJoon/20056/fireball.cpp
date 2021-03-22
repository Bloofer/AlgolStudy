#include <iostream>
#include <vector>
using namespace std;

int N, M, K;
// 각 방향 정보에 따른 좌표이동방향
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
vector<int> arr[50][50];
typedef struct{
  int r, c, m, d, s;
} FIREBALL;
vector<FIREBALL> fVec;

bool available(int x, int y){ return x >= 0 && y >= 0 && x < N && y < N; }

void move_fireball(){
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) arr[i][j].clear(); // arr 배열 초기화
  for (int i = 0; i < fVec.size(); i++) {
    // 1. fVec내 파이어볼들이 들어갈 다음 위치를 arr 엔트리 내 벡터에 삽입
    int nr = (fVec[i].r + fVec[i].s * dx[fVec[i].d]) % N;
    int nc = (fVec[i].c + fVec[i].s * dy[fVec[i].d]) % N;
    if(nr < 0) nr += N;
    if(nc < 0) nc += N;
    arr[nr][nc].push_back(i);
  }

  // 2. 모든 파이어볼들을 arr에 삽입한 후, arr에서 각 파이어볼들을 로직에 따라 합치고 나눔
  // 질량은 ⌊(합쳐진 파이어볼 질량의 합)/5⌋이다.
  // 속력은 ⌊(합쳐진 파이어볼 속력의 합)/(합쳐진 파이어볼의 개수)⌋이다.
  // 합쳐지는 파이어볼의 방향이 모두 홀수이거나 모두 짝수이면, 방향은 0, 2, 4, 6이 되고, 그렇지 않으면 1, 3, 5, 7이 된다.
  vector<FIREBALL> tmpVec;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++){
      if(arr[i][j].empty()) continue;
      else if(arr[i][j].size() == 1) {
        fVec[arr[i][j].front()].r = i; // 새로 이동한 파이어볼의 좌표를 업데이트
        fVec[arr[i][j].front()].c = j;
        tmpVec.push_back(fVec[arr[i][j].front()]); // 파이어볼이 한개인 경우 tmpVec에 그냥 바로 삽입한다.
      } else { // 파이어볼이 두개 이상일 경우, arr내 모든 파이어볼들을 합치고 나눔
        int sumM = 0;
        int sumS = 0;
        bool allOdds = true;
        bool allEvens = true;
        for (auto a:arr[i][j]){
          sumM += fVec[a].m;
          sumS += fVec[a].s;
          allOdds &= (fVec[a].d%2 == 1);
          allEvens &= (fVec[a].d%2 == 0);
        }
        if(sumM/5 > 0){ // 질량이 0보다 크게 나누어지는 파이어볼에 대해서 벡터 삽입
          if(allOdds || allEvens){
            tmpVec.push_back(FIREBALL{i,j,sumM/5,0,sumS/arr[i][j].size()});
            tmpVec.push_back(FIREBALL{i,j,sumM/5,2,sumS/arr[i][j].size()});
            tmpVec.push_back(FIREBALL{i,j,sumM/5,4,sumS/arr[i][j].size()});
            tmpVec.push_back(FIREBALL{i,j,sumM/5,6,sumS/arr[i][j].size()});
          } else {
            tmpVec.push_back(FIREBALL{i,j,sumM/5,1,sumS/arr[i][j].size()});
            tmpVec.push_back(FIREBALL{i,j,sumM/5,3,sumS/arr[i][j].size()});
            tmpVec.push_back(FIREBALL{i,j,sumM/5,5,sumS/arr[i][j].size()});
            tmpVec.push_back(FIREBALL{i,j,sumM/5,7,sumS/arr[i][j].size()});
          }
        }
      }
    }
  }

  // 3. 새로 나누어진 파이어볼들을 포함하여 새로 fVec을 업데이트
  fVec = tmpVec;
}

int main(){
  cin >> N >> M >> K;
  for (int i = 0; i < M; i++) {
    int r, c, m, s, d;
    cin >> r >> c >> m >> s >> d;
    fVec.push_back(FIREBALL{r-1,c-1,m,d,s});
  }
  for (int i = 0; i < K; i++) move_fireball();

  int sum = 0;
  for (auto f:fVec) sum += f.m;
  cout << sum << endl;

  return 0;
}
