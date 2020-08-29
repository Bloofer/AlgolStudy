#include <iostream>
using namespace std;

int N, M;
bool arr[50][50] = {0, }; // 0:빈칸, 1:벽
bool clean[50][50] = {0, }; // 0:청소안됨 1:청소됨
int dir = 0; // 0:↑, 1:→, 2:↓, 3:←
             // 현재 방향의 왼쪽은 (dir+3)%4
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int x, y; // 로봇의 좌표

bool vacuum(){
  clean[x][y] = true;
  //현재 위치에서 현재 방향을 기준으로 왼쪽방향부터 차례대로 탐색
  for (int i = 0; i < 4; i++) {
    //왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면, 그 방향으로 회전한 다음 한 칸을 전진
    dir = (dir + 3) % 4;
    if(!arr[x+dx[dir]][y+dy[dir]] && !clean[x+dx[dir]][y+dy[dir]]) {
      x += dx[dir];
      y += dy[dir];
      return false; // 청소가 안끝났을 시 false 반환
    }
  }

  //네 방향 모두 청소가 이미 되어있거나 벽인 경우에는, 바라보는 방향을 유지한 채로 한 칸 후진
  int backDir = (dir + 2) % 4;
  if(!arr[x+dx[backDir]][y+dy[backDir]]){
    x += dx[backDir];
    y += dy[backDir];
    return false; // 청소가 안끝났을 시 false 반환
  }

  //네 방향 모두 청소가 이미 되어있거나 벽이면서, 뒤쪽 방향이 벽이라 후진도 할 수 없는 경우에는 작동을 멈춘다.
  return true;
}

int main(){
  cin >> N >> M;
  cin >> x >> y >> dir;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> arr[i][j];
    }
  }

  bool end;
  do{
    end = vacuum();
  } while(!end);

  int cnt = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if(clean[i][j]) cnt++;
    }
  }
  cout << cnt << endl;

  return 0;
}
