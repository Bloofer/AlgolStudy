#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int nutrArr[11][11] = {0, };             // 양분 배열: 각 엔트리에 양분량 저장
int landArr[11][11] = {0, };             // 땅 배열: 각 엔트리에 현재 땅의 양분량 저장
vector<int> treeArr[11][11];     // 나무 배열: 각 엔트리에 나무 나이 벡터 저장
int N, M, K;                     // N: N*N배열크기, M: 나무 숫자, K: 목표 해
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

bool valid_pos(int x, int y){
  return (x >= 1 && y >= 1 && x <= N && y <= N);
}

void sort_tree_arr(){
// 나무 배열을 어린 나이부터 오름 차순으로 정렬
  for(int i=1; i<=N; i++){
    for(int j=1; j<=N; j++){
      if(!treeArr[i][j].empty()) sort(treeArr[i][j].begin(), treeArr[i][j].end());
    }
  }
}

void run_year(){
  //  1. 봄; 나무가 자기 나이만큼 땅에서 양분먹고 나이 1 증가,
  //         한 칸에 나무 여러개 있으면 어린 나무부터 먹음, 양분 못먹는 나무는 죽음
  //  2. 여름; 죽은 나무 → 양분, 각각 [죽은 나무의 나이/2]가 해당칸에 양분으로 추가됨
  for(int i=1; i<=N; i++){
    for(int j=1; j<=N; j++){
      int alvCnt = 0;
      for(int k=0; k<treeArr[i][j].size(); k++){
        if(treeArr[i][j][k] <= landArr[i][j]){
          // 양분 먹을 수 있을 때
          alvCnt++;
          landArr[i][j] -= treeArr[i][j][k];
          treeArr[i][j][k]++;
        }
      }

      int siz = treeArr[i][j].size();
      for(int k=0; k<siz-alvCnt; k++) {
        landArr[i][j] += treeArr[i][j].back() / 2;  // [죽은 나무의 나이/2] 양분 추가
        treeArr[i][j].pop_back();
      }
    }
  }

  //  3. 가을; 나무 번식, 나이가 5배수인 나무에 한해 번식함, 인접 8칸에 나이 1 나무 생성됨. 땅을 벗어나는 경우 제외
  for(int i=1; i<=N; i++){
    for(int j=1; j<=N; j++){
      for(auto p:treeArr[i][j]){
        if((p % 5) == 0 && p != 0){
          for(int k=0; k<8; k++){
            if(valid_pos(i+dx[k], j+dy[k])) treeArr[i+dx[k]][j+dy[k]].push_back(1);
          }
        }
      }
    }
  }

  //  4. 겨울; 각 땅에 A[x][y] 만큼 양분이 추가됨
  for(int i=1; i<=N; i++){
    for(int j=1; j<=N; j++){
      landArr[i][j] += nutrArr[i][j];
    }
  }
}

int main(){
  cin >> N >> M >> K;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      cin >> nutrArr[i][j];
      landArr[i][j] = 5;
    }
  }
  for (int i = 0; i < M; i++) {
    int x, y, age;
    cin >> x >> y >> age;
    treeArr[x][y].push_back(age);
  }

  // K년이 지날 동안 반복
  for (int i = 0; i < K; i++) {
    sort_tree_arr();
    run_year();
  }

  int sum = 0;
  for(int i=1; i<=N; i++){
    for(int j=1; j<=N; j++){
      sum += treeArr[i][j].size();
    }
  }
  cout << sum << endl;

  return 0;
}
