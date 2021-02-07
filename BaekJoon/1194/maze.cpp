#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

int N, M;
bool visit[50][50][64] = {0, }; // N*M*2^KEY
char arr[50][50];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

typedef struct{
  int x, y, kBit, d;
} ENTRY;

int char_to_bit(char c){ return pow(2,c-'a'); }
bool bit_check(int b, char c){
  // b:kBit 입력, c:확인하고자 하는 key(소문자), 가지고 있으면 true 반환
  bool bArr[6];
  int num = 32;
  for (int i = 0; i < 6; i++) {
    bArr[i] = (b/num);
    b%=num;
    num/=2;
  }
  return bArr[5-(int)(c-'a')];
}
bool available(int x, int y){ return x>=0 && y>=0 && x<N && y<M; }

int bfs(int x, int y){
  queue<ENTRY> bfsQ;
  bfsQ.push(ENTRY{x,y,0,0});

  while(!bfsQ.empty()){
    ENTRY e = bfsQ.front();
    bfsQ.pop();

    for (int i = 0; i < 4; i++) {
      int nx = e.x + dx[i];
      int ny = e.y + dy[i];
      if(available(nx, ny)){
        if((arr[nx][ny]=='.' || arr[nx][ny]=='0') && !visit[nx][ny][e.kBit]){
          // 1. 다음 위치가 .인 경우: 그대로 진행
          visit[nx][ny][e.kBit] = true;
          bfsQ.push(ENTRY{nx,ny,e.kBit,e.d+1});
        } else if((arr[nx][ny]>='a' && arr[nx][ny]<='f')){
          // 2. 다음 위치가 a-f인 경우: bit count하고 구조체에 추가하고 push
          if(bit_check(e.kBit, arr[nx][ny]) && !visit[nx][ny][e.kBit]){
            // 만약 해당 열쇠를 가지고 있는 경우
            visit[nx][ny][e.kBit] = true;
            bfsQ.push(ENTRY{nx,ny,e.kBit,e.d+1});
          } else if(!bit_check(e.kBit, arr[nx][ny]) && !visit[nx][ny][e.kBit+char_to_bit(arr[nx][ny])]){
            // 해당 열쇠가 없는 경우
            visit[nx][ny][e.kBit+char_to_bit(arr[nx][ny])] = true;
            bfsQ.push(ENTRY{nx,ny,e.kBit+char_to_bit(arr[nx][ny]),e.d+1});
          }
        } else if((arr[nx][ny]>='A' && arr[nx][ny]<='F')){
          // 3. 다음 위치가 A-F인 경우: 현재 구조체에서 bit 계산시 있으면 push
          if(bit_check(e.kBit, (char)tolower(arr[nx][ny])) && !visit[nx][ny][e.kBit]){
            // 만약 해당 열쇠를 가지고 있는 경우
            visit[nx][ny][e.kBit] = true;
            bfsQ.push(ENTRY{nx,ny,e.kBit,e.d+1});
          }
        }  else if(arr[nx][ny]=='1'){
          // 4. 다음 위치가 1인 경우: +1 return
          return e.d+1;
        }
      }
    }
  }
  return -1;
}

int main(){
  int x, y;
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> arr[i][j];
      if(arr[i][j] == '0') { x=i; y=j; }
    }
  }
  cout << bfs(x, y);

  return 0;
}
