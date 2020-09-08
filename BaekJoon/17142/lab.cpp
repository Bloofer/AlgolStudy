#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
using namespace std;

int N, M;
int arr[50][50] = {0, }; // 0은 빈 칸, 1은 벽, 2는 바이러스
int actArr[50][50] = {0, }; // arr가 활성화된 벽. 벽은 -3, 비활성바이러스는 -2, 빈칸은 -1, 활성바이러스는 0~
bool visit[10] = {0, };
vector< pair<int, int> > virusVec;
typedef struct {
  int x, y, t;
} VIRUS;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int minVal = INT_MAX;

int get_min(int a, int b){
  return a < b ? a : b;
}

bool available(int x, int y){
  return x >= 0 && y >= 0 && x < N && y < N;
}

void copy_arr(){
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (arr[i][j] == 0) actArr[i][j] = -1; // 빈칸
      else if (arr[i][j] == 1) actArr[i][j] = -3; // 벽
      else actArr[i][j] = -2; // 바이러스
    }
  }
}

int check_result(){
  // 바이러스 퍼뜨린 후 판단. 1-바이러스 모두 퍼짐 2-마지막에 비활성에 퍼짐 3-전부 못퍼짐
  int t = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (actArr[i][j] == -1) return INT_MAX; // 못퍼진 칸이 하나라도 있으면 INT_MAX
      if (actArr[i][j] > t) t = actArr[i][j];
    }
  }
  return t;
}

void spread_virus(string s){
  // 2. actArr에 활성바이러스 선택하여 0부터 바이러스 전파(BFS),
  copy_arr();
  queue<VIRUS> virusQ;
  for (int i = 0; i < s.length(); i++) {
    VIRUS tmp;
    tmp.x = virusVec[s[i]-'0'].first;
    tmp.y = virusVec[s[i]-'0'].second;
    tmp.t = 0;
    virusQ.push(tmp);
  }

  // 2-1. 활성이 비활성 만나면 -2->[시간]으로 변환해서 큐에 넣고 다시 전파시작
  // 2-2. 벽을 제외한 모든 영역에 바이러스가 퍼질 때까지 반복
  while(!virusQ.empty()){
    VIRUS v = virusQ.front();
    virusQ.pop();
    if(actArr[v.x][v.y] > 0) continue;
    if(v.t != 0 && arr[v.x][v.y] == 2) actArr[v.x][v.y] = -4; // 비활성화 바이러스인 경우 -4로 따로 표시
    else actArr[v.x][v.y] = v.t;


    for (int i = 0; i < 4; i++) {
      int nx = v.x + dx[i];
      int ny = v.y + dy[i];

      if(available(nx, ny)) {
        if(actArr[nx][ny] == -1 || actArr[nx][ny] == -2) virusQ.push(VIRUS{nx,ny,v.t+1});
      }
    }

  }

  // 2-3. 반복 중 최대의 시간을 출력
  int time = check_result();
  minVal = get_min(minVal, time);
}

void dfs(string s){
  if(s.length() == M) {
    spread_virus(s); // 1. arr에 M수에 따라 바이러스 활성화 조합 선택
  } else {
    int i = 0;
    if(s.length() > 0) i = s.back() - '0';
    for (; i < virusVec.size(); i++) {
      if(!visit[i]){
        visit[i] = true;
        dfs(s+char(i+'0'));
        visit[i] = false;
      }
    }
  }
}

int main(){
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> arr[i][j];
      if(arr[i][j] == 2) virusVec.push_back(pair<int, int>(i, j));
    }
  }

  dfs("");
  if(minVal == INT_MAX) cout << -1 << endl;
  else cout << minVal << endl;

  return 0;
}
