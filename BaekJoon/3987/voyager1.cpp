#include <iostream>
#include <cstring>
using namespace std;

int N, M;
char arr[502][502];
bool visit[502][502][4] = {0, };

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1}; // 방향은 U, R, D, L 순
char dirs[4] = {'U', 'R', 'D', 'L'};
int vDir; // 최장 탐사방향

bool available(int x, int y){
  return x >= 0 && y >= 0 && x < N && y < M;
}

int explore(int pr, int pc){
  // 보이저 1호의 탐사 함수, 탐사선의 위치를 받아 최장 탐사시간을 반환, 무한은 -1
  int vTime = 0;
  for (int i = 0; i < 4; i++) {
    memset(visit, false, sizeof(visit));
    int nx = pr;
    int ny = pc;
    int ndir = i;
    int tick = 1;
    visit[pr][pc][ndir] = true;

    while(true){ // 탐사선이 영역 바깥으로 나가거나 블랙홀에 빠지면 탐사종료
      nx += dx[ndir];
      ny += dy[ndir];

      if(!available(nx, ny) || arr[nx][ny] == 'C') break;
      if(visit[nx][ny][ndir]) { vDir = i; return -1; } // 탐사선이 같은 위치에 같은 방향으로 반복에 빠지면 Voyager!
      if(arr[nx][ny] == '/') ndir ^= 1; // /를 만날경우 다음 방향이 XOR 1한 결과가 됨
      else if(arr[nx][ny] == '\\') ndir = 3-ndir; // \를 만날경우 다음 방향이 3-ndir한 결과가 됨

      visit[nx][ny][ndir] = true;
      tick++;
    }
    if(vTime < tick) { vTime = tick; vDir = i; }
  }
  return vTime;
}

int main(){
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> arr[i][j];
    }
  }
  int pr, pc;
  cin >> pr >> pc;

  int vTime = explore(pr-1, pc-1);
  if(vTime == -1) cout << dirs[vDir] << endl << "Voyager";
  else cout << dirs[vDir] << endl << vTime;

  return 0;
}
