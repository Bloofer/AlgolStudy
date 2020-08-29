#include <iostream>
#include <vector>
using namespace std;

int N, M, K;
int arr[20][20] = {0, };
vector<int> instVec;
int dice[6] = {0, };

void roll_south(){
  int tmp = dice[0];
  dice[0] = dice[1];
  dice[1] = dice[5];
  dice[5] = dice[4];
  dice[4] = tmp;
}

void roll_north(){
  int tmp = dice[0];
  dice[0] = dice[4];
  dice[4] = dice[5];
  dice[5] = dice[1];
  dice[1] = tmp;
}

void roll_east(){
  int tmp = dice[0];
  dice[0] = dice[3];
  dice[3] = dice[5];
  dice[5] = dice[2];
  dice[2] = tmp;
}

void roll_west(){
  int tmp = dice[0];
  dice[0] = dice[2];
  dice[2] = dice[5];
  dice[5] = dice[3];
  dice[3] = tmp;
}

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

bool available(int a, int b){
  return a >= 0 && b >= 0 && a < N && b < M;
}

int main(){
  int x, y;
  cin >> N >> M >> x >> y >> K;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> arr[i][j];
    }
  }
  int n;
  for (int i = 0; i < K; i++) {
    cin >> n;
    instVec.push_back(n - 1);
  }

  for (auto i:instVec) {
    // 1. 이동 가능한 경우에 한 해 주사위 이동
    if(available(x + dx[i], y + dy[i])){
      x += dx[i];
      y += dy[i];
      // 2. 각 주사위의 이동 명령에 따라 뒤집고 좌표 이동
      if(i == 0) roll_east();
      else if(i == 1) roll_west();
      else if(i == 2) roll_north();
      else if(i == 3) roll_south();
      if(arr[x][y] == 0) { // 3. 이동한 칸에 쓰여 있는 수가 0이면, 바닥면의 수가 칸에 복사
        arr[x][y] = dice[5];
        cout << dice[0] << endl;
      } else { // 4. 0이 아니면 칸에 쓰여 있는 수가 주사위의 바닥면으로 복사, 칸에 쓰여 있는 수는 0 입력
        dice[5] = arr[x][y];
        arr[x][y] = 0;
        cout << dice[0] << endl;
      }
    }
  }

  return 0;
}
