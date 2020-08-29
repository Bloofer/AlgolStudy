#include <iostream>
#include <climits>
using namespace std;

int N, M;
char arr[20][20] = {0, }; // 동전:o, 빈칸:., 벽:#
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0}; // →, ↓, ←, ↑
int minCnt = INT_MAX;

typedef enum{
  NO_FALL,
  ONE_FALL,
  TWO_FALL
} COND;

typedef enum{
  EMPTY,
  WALL,
  FALL
} ENTRY;

int get_min(int a, int b){
  return a < b ? a : b;
}

void test_print(int x1, int y1, int x2, int y2){
  cout << x1 << "," << y1 << " | " << x2 << "," << y2 << endl;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cout << arr[i][j] << " ";
    }
    cout << endl;
  }
}

COND chk_cond(int x1, int y1, int x2, int y2){
  bool b1 = (x1>=0 && y1>=0 && x1<N && y1<M);
  bool b2 = (x2>=0 && y2>=0 && x2<N && y2<M); // 두 동전이 판 위에 있는 지 검사 변수
  if(b1 && !b2) return ONE_FALL;
  else if(!b1 && b2) return ONE_FALL;
  else if(!b1 && !b2) return TWO_FALL;
  else return NO_FALL;
}

ENTRY chk_entry(int x, int y){
  if(x<0 || y<0 || x>=N || y>=M) return FALL;
  else if(arr[x][y] == '#') return WALL;
  else return EMPTY;
}

void dfs(int x1, int y1, int x2, int y2, int depth){
  COND fallChk = chk_cond(x1, y1, x2, y2);
  if(fallChk==TWO_FALL || depth==11) return;
  else if(fallChk==ONE_FALL) {
    minCnt = get_min(minCnt, depth);
    return;
  } else if(fallChk==NO_FALL) { // 둘 다 안떨어진 경우

    for (int i = 0; i < 4; i++) {
      int nx1 = x1 + dx[i];
      int ny1 = y1 + dy[i];
      int nx2 = x2 + dx[i];
      int ny2 = y2 + dy[i];

      ENTRY e1 = chk_entry(nx1, ny1);
      if(e1 == WALL){ // 다음 이동 위치를 체크해, 벽인경우 가만히 있도록
        nx1 = x1;
        ny1 = y1;
      }
      ENTRY e2 = chk_entry(nx2, ny2);
      if(e2 == WALL){
        nx2 = x2;
        ny2 = y2;
      }
      dfs(nx1,ny1,nx2,ny2,depth+1);
    }
  }
}

int main(){
  int x1, y1, x2, y2;
  x1 = y1 = x2 = y2 = -1;

  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> arr[i][j];
      if(x1!=-1 && y1!=-1 && arr[i][j]=='o') {
        x2 = i;
        y2 = j;
        arr[i][j] = '.';
      } else if(arr[i][j]=='o') {
        x1 = i;
        y1 = j;
        arr[i][j] = '.';
      }
    }
  }

  dfs(x1, y1, x2, y2, 0);
  if(minCnt == INT_MAX) cout << -1 << endl;
  else cout << minCnt << endl;
  /*
  동전이 이동하려는 칸이 벽이면, 동전은 이동하지 않는다.
  동전이 이동하려는 방향에 칸이 없으면 동전은 보드 바깥으로 떨어진다.
  그 외의 경우에는 이동하려는 방향으로 한 칸 이동한다.이동하려는 칸에 동전이 있는 경우에도 한 칸 이동한다.
  */

  return 0;
}
