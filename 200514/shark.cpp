#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int moveCnt = 0;
int N;
int arr[20][20];
bool visit[20][20] = {0, };

struct {
  int x, y;
  int size;
  int feed;
} shark = { .size = 2, .feed = 0 };

typedef struct {
  int x, y;
  int dist;
} FISH; // 물고기 정보
vector<FISH> fishVec; // bfs로 모을 먹을 수 있는 물고기 정보

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

bool fishCmp(FISH a, FISH b){
  if(a.dist != b.dist) return a.dist < b.dist;
  else if(a.x != b.x) return a.x < b.x;
  return a.y < b.y;
}

bool available(int x, int y){
  return (x >= 0) && (y >= 0) && (x < N) && (y < N);
}

void init(){
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      visit[i][j] = false;
    }
  }
}

void bfs(int x, int y){
  queue< pair< pair<int, int>, int> > posQ; // 상어의 위치를 나타내는 큐
  posQ.push(pair< pair<int, int>, int>(pair<int, int>(x, y), 0));

  while(!posQ.empty()) { // 큐가 빌때까지 주변 탐색
    pair< pair<int, int>, int> curPos = posQ.front();
    posQ.pop();
    int posX = curPos.first.first;
    int posY = curPos.first.second;
    int dist = curPos.second;

    for (int i = 0; i < 4; i++) {
      int newPosX = posX + dx[i];
      int newPosY = posY + dy[i];
      if(available(newPosX, newPosY) && !visit[newPosX][newPosY]){
        if(arr[newPosX][newPosY] == 0 || arr[newPosX][newPosY] == shark.size) { // 다음 위치가 0이거나 상어 크기랑 같으면 지나감
          visit[newPosX][newPosY] = true;
          posQ.push(pair< pair<int, int>, int>(pair<int, int>(newPosX, newPosY), dist+1));
        } else if(arr[newPosX][newPosY] < shark.size){ // 다음 위치 물고기가 상어보다 작으면 먹을 수 있는 예비 리스트에 업데이트
          FISH tempFish;
          tempFish.x = newPosX;
          tempFish.y = newPosY;
          tempFish.dist = dist+1;
          fishVec.push_back(tempFish);
          visit[newPosX][newPosY] = true;
        }
      }
    }
  }
}

int main(){
  cin >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> arr[i][j];
      if(arr[i][j] == 9) { arr[i][j] = 0; shark.x = i; shark.y = j; }
    }
  }

  // 1. 먹을 수 있는 물고기 없을 때(fishVec빌 때)까지 반복 진행
  do {
    // 2. 먼저 현재 상어의 위치에서 BFS 돌리고 fishVec 업데이트
    bfs(shark.x, shark.y);
    init();

    // 3. 업데이트 된 fishVec 정렬, 가까운 순부터 shark.size 만큼 먹고 먹으면서 해당 칸 물고기 제거 & 물고기 크기 + 1
    sort(fishVec.begin(), fishVec.end(), fishCmp);

    if(!fishVec.empty()){
      shark.x = fishVec.front().x;
      shark.y = fishVec.front().y;
      shark.feed++;
      moveCnt += fishVec.front().dist;
      arr[shark.x][shark.y] = 0;
      fishVec.clear();
      if(shark.size == shark.feed){
        shark.size++;
        shark.feed = 0;
      }
    } else {
      break;
    }

  } while(true);

  cout << moveCnt << endl;
  return 0;
}
