#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, K, L;
int arr[100][100] = {0, }; // 0: 빈칸, 1: 사과, 2: 뱀
vector< pair<int, int> > appleVec;
vector< pair<int, char> > moveVec;

int currentDir = 0; // 0: →, 1: ↓, 2: ←, 3: ↑
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
pair<int, int> head = pair<int, int>(0, 0);
pair<int, int> tail = pair<int, int>(0, 0);
queue<int> snakeMoves; // front: tail쪽 이동방향, back: head쪽 이동방향

bool available(int x, int y){
  // 해당 위치에 뱀이 있거나 범위 바깥이면 이동불가
  return (arr[x][y] != 2 && x >= 0 && y >= 0 && x < N && y < N);
}

int main(){
  cin >> N;
  cin >> K;
  for (int i = 0; i < K; i++) {
    int x, y;
    cin >> x >> y;
    arr[x-1][y-1] = 1;
  }
  cin >> L;
  for (int i = 0; i < L; i++) {
    int x;
    char c;
    cin >> x >> c;
    moveVec.push_back(pair<int, char>(x, c));
  }

  int idx = 0;
  int tick = 1;
  arr[0][0] = 2;
  snakeMoves.push(0);
  while(1){
    if(idx < moveVec.size() && moveVec[idx].first + 1 == tick){
      if(moveVec[idx].second == 'L') {
        currentDir = (currentDir + 3) % 4;
      } else if(moveVec[idx].second == 'D') {
        currentDir = (currentDir + 1) % 4;
      }
      if(snakeMoves.size() == 1) snakeMoves.front() = currentDir;
      idx++;
    }
    int nextX = head.first + dx[currentDir];
    int nextY = head.second + dy[currentDir];
    if(!available(nextX, nextY)) break;
    else{
      head.first += dx[currentDir];
      head.second += dy[currentDir];
      if(arr[head.first][head.second] == 0) {
        arr[tail.first][tail.second] = 0;
        snakeMoves.push(currentDir);
        snakeMoves.pop();
        tail.first += dx[snakeMoves.front()];
        tail.second += dy[snakeMoves.front()];
      } else if(arr[head.first][head.second] == 1) {
        snakeMoves.push(currentDir);
      }
      arr[head.first][head.second] = 2;
    }
    tick++;
  }

  cout << tick << endl;
  return 0;
}
