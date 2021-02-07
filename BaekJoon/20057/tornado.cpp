#include <iostream>
using namespace std;

int arr[500][500] = {0, };
int tmp[500][500] = {0, };
int N;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

bool available(int x, int y){ return x >= 0 && y >= 0 && x < N && y < N; }

int move_sand(int x, int y, int dir){
  int val = arr[x][y];
  int sum = 0;
  int sandFall = 0;

  int nx = x+2*dx[dir]; int ny = y+2*dy[dir];
  if(available(nx, ny)) { arr[nx][ny]+=val/20; tmp[nx][ny]+=val/20; sum+=val/20; }
  else { sandFall+=val/20; sum+=val/20; }

  nx = x+dx[dir]+dx[(dir+1)%4]; ny = y+dy[dir]+dy[(dir+1)%4];
  if(available(nx, ny)) { arr[nx][ny]+=val/10; tmp[nx][ny]+=val/10; sum+=val/10; }
  else { sandFall+=val/10; sum+=val/10; }

  nx = x+dx[dir]+dx[(dir+3)%4]; ny = y+dy[dir]+dy[(dir+3)%4];
  if(available(nx, ny)) { arr[nx][ny]+=val/10; tmp[nx][ny]+=val/10; sum+=val/10; }
  else { sandFall+=val/10; sum+=val/10; }

  nx = x+2*dx[(dir+1)%4]; ny = y+2*dy[(dir+1)%4];
  if(available(nx, ny)) { arr[nx][ny]+=val/50; tmp[nx][ny]+=val/50; sum+=val/50; }
  else { sandFall+=val/50; sum+=val/50; }

  nx = x+2*dx[(dir+3)%4]; ny = y+2*dy[(dir+3)%4];
  if(available(nx, ny)) { arr[nx][ny]+=val/50; tmp[nx][ny]+=val/50; sum+=val/50; }
  else { sandFall+=val/50; sum+=val/50; }

  nx = x+dx[(dir+1)%4]+dx[(dir+2)%4]; ny = y+dy[(dir+1)%4]+dy[(dir+2)%4];
  if(available(nx, ny)) { arr[nx][ny]+=val/100; tmp[nx][ny]+=val/100; sum+=val/100; }
  else { sandFall+=val/100; sum+=val/100; }

  nx = x+dx[(dir+2)%4]+dx[(dir+3)%4]; ny = y+dy[(dir+2)%4]+dy[(dir+3)%4];
  if(available(nx, ny)) { arr[nx][ny]+=val/100; tmp[nx][ny]+=val/100; sum+=val/100; }
  else { sandFall+=val/100; sum+=val/100; }

  nx = x+dx[(dir+1)%4]; ny = y+dy[(dir+1)%4];
  if(available(nx, ny)) { arr[nx][ny]+=((double)val/(double)100)*(double)7; tmp[nx][ny]+=((double)val/(double)100)*(double)7; sum+=((double)val/(double)100)*(double)7; }
  else { sandFall+=((double)val/(double)100)*(double)7; sum+=((double)val/(double)100)*(double)7; }

  nx = x+dx[(dir+3)%4]; ny = y+dy[(dir+3)%4];
  if(available(nx, ny)) { arr[nx][ny]+=((double)val/(double)100)*(double)7; tmp[nx][ny]+=((double)val/(double)100)*(double)7; sum+=((double)val/(double)100)*(double)7; }
  else { sandFall+=((double)val/(double)100)*(double)7; sum+=((double)val/(double)100)*(double)7; }

  val -= sum;
  nx = x+dx[dir]; ny = y+dy[dir];
  if(available(nx, ny)) { arr[nx][ny]+=val; tmp[nx][ny]+=val;}
  else { sandFall+=val; }

  return sandFall;
}

int spiral(int x, int y){
  int dblCnt = 0;
  int moveCnt = 1;
  int dir = 0;
  int sandFall = 0;
  while(1){
    for (int i = 0; i < moveCnt; i++) {
      if(x == 0 && y == 0) return sandFall;
      x += dx[dir];
      y += dy[dir];
      sandFall += move_sand(x,y,dir);
    }
    if(dblCnt == 1) { dblCnt = 0; moveCnt++; }
    else dblCnt++;
    dir = (dir+1)%4;
  }
}

int main(){
  cin >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> arr[i][j];
    }
  }

  // move_sand(N/2,N/2-1,0);
  // for (int i = 0; i < N; i++) {
  //   for (int j = 0; j < N; j++) {
  //     cout << tmp[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  cout << spiral(N/2,N/2) << endl;

  return 0;
}
