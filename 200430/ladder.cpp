#include <iostream>
#include <vector>
using namespace std;

int M, N, H;
bool hrz[31][11] = {0,};                // 사다리에 가로선을 놓는 배열
vector< pair<int, int> > hrzs;  // 처음 주어지는 M개의 가로선 배치
typedef enum{
  DOWN = 0,
  LEFT = 1,
  RIGHT = 2
}DIR;
int minVal = 4;

int get_min(int a, int b){
  return a < b ? a : b;
}

// 1. 이중 for문 안에 가로선들을 dfs로 최대 3개씩 배치
// 2. 배치하는 동안 dfs의 base case로 배치 조합이 완성되면 사다리 시뮬레이션 실행
// 3. i번 세로선 결과가 i번이 나오는 결과 확인, 있으면 최소 지점에서 종료, 없으면 3까지 계속 진행
// 사다리 배열
// | | | | | <= 첫번재 세로선이 (0,0)
// _ _ _ _ <= 첫번째 가로선이 (0,0)
// (x,y) 세로선의

DIR move_available(int x, int y){
  // 해당 좌표의 사다리가 아래:0로 내려갈지, 왼쪽:1으로 이동할지, 오른쪽:2으로 이동할지 반환
  if(y+1<=N-1 && hrz[x][y]) return RIGHT;
  else if(y-1>=0 && hrz[x][y-1]) return LEFT;
  else return DOWN;
}

bool ladder_available(int x, int y){
  if(y == 0) return (x >= 0 && y >= 0 && x < H && y < N && !hrz[x][y+1]);
  else if(y == N-1) return (x >= 0 && y >= 0 && x < H && y < N && !hrz[x][y-1]);
  else return (x >= 0 && y >= 0 && x < H && y < N && !hrz[x][y+1] && !hrz[x][y-1]);
}

bool simulate_ladder(){
  // 사다리를 시뮬레이션하여 i번 세로선의 결과가 i번이 나오는지 확인
  int x, y;

  for (int i = 0; i < N; i++) {
    // 각각의 세로선들에 대해서 탐사 시작
    x = 0;
    y = i;
    while(x < H){
      // 사다리를 다 내려갈 동안 계속 가로 사다리 확인하며 탐사
      DIR nextDir = move_available(x, y);
      if(nextDir == LEFT) y--;
      else if(nextDir == RIGHT) y++;
      x++;
    }
    // 맨 마지막으로 내려왔을 때 i번 세로선의 결과가 i번이 아니라면 false 반환후 종료
    if(i != y) return false;
  }

  return true;
}

void dfs(int idx, int x, int y){
  if(simulate_ladder()) minVal = get_min(idx, minVal);

  if(idx == 3){
    return;
  } else {
    for (int i = x; i < H; i++) {
      for (int j = 0; j < N; j++) {
        if(i == x && j <= y) continue;
        else if(!hrz[i][j] && ladder_available(i, j)){
          hrz[i][j] = true;
          dfs(idx + 1, i, j);
          hrz[i][j] = false;
        }
      }
    }
  }
}

int main(){
  cin >> N >> M >> H;
  for (int i = 0; i < M; i++) {
    int x, y;
    cin >> x >> y;
    hrz[x-1][y-1] = true;
  }

  // 사다리 배치 알고리즘
  // 1. 1 -> 2 -> ... -> N개씩 가로선을 추가하여 조합을 만든다.
  // 2. 만약 조합을 만들 수 없다면 -1 반환
  // 3. 만들어진 조합으로 사다리 시뮬레이션을 돌리고, 만약 조건을 통과하면 종료한다.

  // 사다리 놓는 조합 만드는 함수는 dfs로 구현
  // 1. base case (3개가 최대):
  // 2. recursive case: dfs 호출하며 사다리 놓으면서 시뮬레이션

  if(simulate_ladder()) minVal = 0;
  else {
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < N; j++) {
        if(!hrz[i][j] && ladder_available(i, j)){
          hrz[i][j] = true;
          dfs(1, i, j);
          hrz[i][j] = false;
        }
      }
    }
  }

  if(minVal == 4) cout << -1;
  else cout << minVal;

  return 0;
}
