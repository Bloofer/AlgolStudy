#include <iostream>
#include <algorithm>
using namespace std;

int N, K;
int conveyorDurable[200]; // 각 엔트리: 컨베이어 벨트 내구도
bool conveyorRobots[200]; // 각 엔트리: 로봇의 존재 유무

int main(){
  int cnt = 0; // 내구도 0인 칸의 갯수
  cin >> N >> K;
  for (int i = 0; i < 2 * N; i++) {
    cin >> conveyorDurable[i];
    if(conveyorDurable[i] == 0) cnt++;
  }

  int steps = 0; // 진행 단계의 수
  while(true){
    // 1. 벨트가 한 칸 회전
    int tmpDur = conveyorDurable[2*N-1];
    int tmpRob = conveyorRobots[2*N-1];
    if(conveyorRobots[N-1]) conveyorRobots[N-1] = 0; // 회전 전, 내려가는 위치 로봇 있으면 먼저 내려감
    for (int i = 2*N - 1; i > 0; i--) {
      conveyorDurable[i] = conveyorDurable[i-1];
      conveyorRobots[i] = conveyorRobots[i-1];
    }
    if(conveyorRobots[N-1]) conveyorRobots[N-1] = 0; // 회전 후, 내려가는 위치 로봇 있으면 먼저 내려감
    conveyorDurable[0] = tmpDur;
    conveyorRobots[0] = tmpRob;

    // 2. 가장 먼저 벨트에 올라간 로봇부터, 벨트가 회전하는 방향으로 한 칸 이동할 수 있다면 이동
    for (int i = N - 2; i >= 0; i--) {
      if(conveyorRobots[i] && !conveyorRobots[i+1] && conveyorDurable[i+1]>0) {
        swap(conveyorRobots[i], conveyorRobots[i+1]);
        conveyorDurable[i+1]--;
        if(conveyorDurable[i+1] == 0) cnt++;
      }
    }

    // 3. 올라가는 위치에 로봇이 없다면 로봇을 하나 올림
    if(!conveyorRobots[0] && conveyorDurable[0]>0) {
      conveyorRobots[0] = true;
      conveyorDurable[0]--;
      if(conveyorDurable[0] == 0) cnt++;
    }

    // 4. 내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료. 그렇지 않다면 1번으로 돌아가 반복
    steps++;
    if(cnt >= K) break;
  }

  cout << steps << endl;
  return 0;
}
