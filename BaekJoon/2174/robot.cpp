#include <iostream>
#include <algorithm>
using namespace std;

int A, B, N, M;
int arr[100][100] = {0, };
int dx[4] = {1, 0, -1 ,0}; // ↓ → ↑ ←
int dy[4] = {0, 1, 0, -1};

typedef struct{
  int x, y, d;
}STAT;
STAT rsta[101]; // 로봇의 현상태를 나타내는 배열

int dir_to_int(char d){
  if(d == 'N') return 0;
  else if(d == 'E') return 1;
  else if(d == 'S') return 2;
  else if(d == 'W') return 3;
  else return -1;
}

int main(){
  cin >> A >> B >> N >> M;
  for (int i = 1; i <= N; i++) {
    int x, y; char d;
    cin >> x >> y >> d;
    arr[y-1][x-1] = i;
    rsta[i] = {y-1, x-1, dir_to_int(d)};
  }

  for (int i = 1; i <= M; i++) {
    int n, r; char c;
    cin >> n >> c >> r;
    for (int j = 0; j < r; j++) {
      if(c == 'L') rsta[n].d = (rsta[n].d + 3) % 4;
      else if(c == 'R') rsta[n].d = (rsta[n].d + 1) % 4;
      else if(c == 'F') {
        int nx = rsta[n].x + dx[rsta[n].d];
        int ny = rsta[n].y + dy[rsta[n].d];
        if(nx < 0 || ny < 0 || nx >= B || ny >= A) { printf("Robot %d crashes into the wall\n", n); return 0; }
        else if(arr[nx][ny] > 0) { printf("Robot %d crashes into robot %d\n", n, arr[nx][ny]); return 0; }
        else {
          swap(arr[nx][ny], arr[rsta[n].x][rsta[n].y]);
          rsta[n].x = nx;
          rsta[n].y = ny;
        }
      }
    }
  }
  cout << "OK\n";
  return 0;
}
