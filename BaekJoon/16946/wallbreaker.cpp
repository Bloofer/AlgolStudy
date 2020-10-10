#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <set>
using namespace std;

int N, M;
int arr[1000][1000] = {0, };
int val[1000][1000] = {0, };
bool visit[1000][1000] = {0, };
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
vector<int> hmap;
int hcnt = 0;

bool available(int x, int y){ return x >= 0 && y >= 0 && x < N && y < M; }

int dfs(int x, int y, int i){
  val[x][y] = i;
  int cnt = 1;
  visit[x][y] = true;
  for (int j = 0; j < 4; j++) {
    int nx = x + dx[j];
    int ny = y + dy[j];
    if(available(nx, ny) && !visit[nx][ny] && arr[nx][ny]==0) {
      cnt += dfs(nx,ny,i);
    }
  }
  return cnt;
}

int main(){
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < s.size(); j++) {
      arr[i][j] = s.at(j) - '0';
    }
  }

  // 일반적인 BFS 대신 미리 빈칸에 계산 먼저 다 해놓고, 벽 부술때 계산된 값만 확인
  int idx = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if(arr[i][j]==0 && !visit[i][j]) {
        hcnt = dfs(i,j,++idx);
        hmap.push_back(hcnt);
      }
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if(arr[i][j] > 0){
        int sum = 1;
        set<int> sumSet;
        for (int k = 0; k < 4; k++) {
          int nx = i + dx[k];
          int ny = j + dy[k];
          if(available(nx, ny) && val[nx][ny] != 0) sumSet.insert(val[nx][ny]-1);
        }
        for(set<int>::iterator it=sumSet.begin(); it!=sumSet.end(); ++it){
          sum += hmap[*it];
        }
        cout << sum % 10;
      } else{
        cout << "0";
      }
    }
    cout << endl;
  }

  return 0;
}
