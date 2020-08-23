#include <iostream>
#include <vector>
using namespace std;

int score = 0;
int blocks;
int N;
int RED[4][4] = {0, };
int BLUE[4][6] = {0, };
int GREEN[6][4] = {0, };

typedef enum {
  BLU,
  GRN
} BOARD;

void input_red(int t, int x, int y){
  if (t == 1) {
    RED[x][y] = 1;
  } else if (t == 2) {
    RED[x][y] = 1;
    RED[x][y+1] = 1;
  } else if (t == 3) {
    RED[x][y] = 1;
    RED[x+1][y] = 1;
  }
}

void init(){
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 10; j++) {
      if(j < 4) RED[i][j] = 0;
    }
  }
}

void count_blocks(){
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 6; j++) {
      if(BLUE[i][j] == 1) blocks++;
      if(GREEN[j][i] == 1) blocks++;
    }
  }
}

void test_print(){
  cout << "===== Test Print =====" << endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 10; j++) {
      if(j < 4) cout << RED[i][j] << " ";
      else if(j >= 4) cout << BLUE[i][j-4] << " ";
    }
    cout << endl;
  }
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 4; j++) {
      cout << GREEN[i][j] << " ";
    }
    cout << endl;
  }
  cout << "======================" << endl;
}

bool check_tetris(BOARD b, vector<int> &tetNum){
  bool isTetris = false;
  if(b == GRN){
    // GREEN의 테트리스 적용
    for (int i = 0; i < 6; i++) {
      bool chk = true;
      for (int j = 0; j < 4; j++) {
        chk &= (GREEN[i][j] == 1);
      }
      if(chk) tetNum.push_back(i);
    }
    if(!tetNum.empty()) isTetris = true;
  } else if(b == BLU){
    // BLUE의 테트리스 적용
    for (int i = 0; i < 6; i++) {
      bool chk = true;
      for (int j = 0; j < 4; j++) {
        chk &= (BLUE[j][i] == 1);
      }
      if(chk) tetNum.push_back(i);
    }
    if(!tetNum.empty()) isTetris = true;
  }
  return isTetris;
}

void push_opaque(){
  // 각각의 BLUE와 GREEN의 도형들에 대해, 0,1행/열에 도형이 있는 경우 전체 행/열을 그만큼 내림
  // GREEN의 적용
  int cnt = 0;
  for (int i = 0; i < 2; i++) {
    int chk = false;
    for (int j = 0; j < 4; j++) {
      chk |= (GREEN[i][j] == 1);
    }
    if(chk) cnt++;
  }

  if(cnt > 0){
    for (int i = 5; i >= cnt; i--) {
      for (int j = 0; j < 4; j++) {
        GREEN[i][j] = GREEN[i-cnt][j];
      }
    }
    for (int i = 0; i < cnt; i++) {
      for (int j = 0; j < 4; j++) {
        GREEN[i][j] = 0;
      }
    }
  }

  // BLUE의 적용
  cnt = 0;
  for (int i = 0; i < 2; i++) {
    int chk = false;
    for (int j = 0; j < 4; j++) {
      chk |= (BLUE[j][i] == 1);
    }
    if(chk) cnt++;
  }

  if(cnt > 0){
    for (int i = 5; i >= cnt; i--) {
      for (int j = 0; j < 4; j++) {
        BLUE[j][i] = BLUE[j][i-cnt];
      }
    }
    for (int i = 0; i < cnt; i++) {
      for (int j = 0; j < 4; j++) {
        BLUE[j][i] = 0;
      }
    }
  }
}

void tetris_block(){
  // 각각의 BLUE와 GREEN의 도형들에 대해, 테트리스를 적용

  // GREEN의 테트리스 적용
  vector<int> tetNumGrn; // 테트리스에 해당되는 행 번호를 저장

  // 1. while (테트리스 조건에 해당시; 각 행/열에 모든 칸 1 존재)
  while(check_tetris(GRN, tetNumGrn)){
    score += tetNumGrn.size();
    //cout << "TETRIS! on Green #";
    //for(auto t:tetNumGrn) cout << t << ",";
    //cout << endl;
    // 2. 모든 테트리스 행/열을 찾아, 해당 칸을 모두 없앰
    int lowestTet = tetNumGrn.back();
    for(auto i:tetNumGrn){
      for (int j = 0; j < 4; j++) {
        GREEN[i][j] = 0;
      }
    }

    if(lowestTet == 0) break; // 테트리스가 일어난 가장 높은행이 0행이면 떨어질게 없음. 따라서 종료
    else {
      // 3. 없앤 칸의 가장 낮은 행/열 바로 윗칸부터 적용하여, 블록이 존재한다면 내려갈 수 있는 만큼 내림
      // 3-1. 각 열별로 lowestTet의 윗 인덱스부터 1의 갯수를 계수
      int blkCnts[4] = {0, };
      for (int j = 0; j < 4; j++) {
        int blkCnt = 0;
        for (int i = lowestTet-1; i >= 0; i--) {
          if(GREEN[i][j] == 1) {
            GREEN[i][j] = 0;
            blkCnt++;
          }
        }
        blkCnts[j] = blkCnt;
      }
      // 3-2. lowestTet의 아래 인덱스부터 1이 존재하는 행 번호를 찾음(없으면 5행이 됨)
      for (int j = 0; j < 4; j++) {
        int blkIdx = 5;
        for (int i = lowestTet+1; i < 6; i++) {
          if(GREEN[i][j] == 1){
            blkIdx = i-1;
            break;
          }
        }
        // 3-3. 3-2에서 찾은 행번호부터 3-1에서 찾은 블록 갯수를 쌓아줌
        for (int i = blkIdx; i > blkIdx - blkCnts[j]; i--) {
          GREEN[i][j] = 1;
        }
      }
      // NOTE: 여기서 주의할 점은 해당 알고리즘은 블록이 크기 1이거나 2이거나 상관없이 모두 바닥까지 블록 한개 단위로
      //       내리도록 구현되었다. 따라서 출제의 의도가 만약, 블록의 크기를 유지하며 내려야 하는 것이라면 틀림
    }
    tetNumGrn.clear();
  }

  // BLUE의 테트리스 적용
  vector<int> tetNumBlu; // 테트리스에 해당되는 행 번호를 저장

  // 1. while (테트리스 조건에 해당시; 각 행/열에 모든 칸 1 존재)
  while(check_tetris(BLU, tetNumBlu)){
    score += tetNumBlu.size();
    //cout << "TETRIS! on Blue #";
    //for(auto t:tetNumBlu) cout << t << ",";
    //cout << endl;
    // 2. 모든 테트리스 행/열을 찾아, 해당 칸을 모두 없앰
    int lowestTet = tetNumBlu.back();
    for(auto i:tetNumBlu){
      for (int j = 0; j < 4; j++) {
        BLUE[j][i] = 0;
      }
    }

    if(lowestTet == 0) break; // 테트리스가 일어난 가장 높은행이 0행이면 떨어질게 없음. 따라서 종료
    else {
      // 3. 없앤 칸의 가장 낮은 행/열 바로 윗칸부터 적용하여, 블록이 존재한다면 내려갈 수 있는 만큼 내림
      // 3-1. 각 열별로 lowestTet의 윗 인덱스부터 1의 갯수를 계수
      int blkCnts[4] = {0, };
      for (int j = 0; j < 4; j++) {
        int blkCnt = 0;
        for (int i = lowestTet-1; i >= 0; i--) {
          if(BLUE[j][i] == 1) {
            BLUE[j][i] = 0;
            blkCnt++;
          }
        }
        blkCnts[j] = blkCnt;
      }
      // 3-2. lowestTet의 아래 인덱스부터 1이 존재하는 행 번호를 찾음(없으면 5행이 됨)
      for (int j = 0; j < 4; j++) {
        int blkIdx = 5;
        for (int i = lowestTet+1; i < 6; i++) {
          if(BLUE[j][i] == 1){
            blkIdx = i-1;
            break;
          }
        }
        // 3-3. 3-2에서 찾은 행번호부터 3-1에서 찾은 블록 갯수를 쌓아줌
        for (int i = blkIdx; i > blkIdx - blkCnts[j]; i--) {
          BLUE[j][i] = 1;
        }
      }
      // 내릴 때 블록의 크기 고려
      // 1. t = 2,3인 블록의 경우 블록을 내릴 때, 같이 내려와야 한다.
      // 2. 만약 두 블록중 한 부분에 테트리스가 발생할 때 행/열이 없어지면서 쪼개지는 경우
      // 3. 각 게임판에 블록의 번호(1,2,3)으로 표기하여 테트리스로 블록이 없어져 쪼개지는 경우로 고려
      // 4. 테트리스 후 블록이 내려올 때, 1X1 블록은 그냥 내려오지만 2크기의 블록은 내릴 때의 옆칸도 고려

    }
    tetNumBlu.clear();
  }

}

void move_block(int t, int x, int y){
  // RED에 들어간 도형은 각각 BLUE에는 같은 행을 유지하며 수평으로, GREEN에는 같은 열을 유지하며 수직으로 전달

  // BLUE의 도형 전달
  if(t==1 || t==2){ // 도형의 모양이 ㅁ, ㅁㅁ 일 때
    bool chk = false;
    for (int i = 0; i < 6; i++) {
      // 같은 행에서 0~5열 사이에 도형이 있는지 찾고, 있으면 그 앞에, 없으면 맨 끝에 도형 붙임
      if(BLUE[x][i]){
        chk = true;
        if(t==1) BLUE[x][i-1] = 1;
        else if(t==2) BLUE[x][i-2] = BLUE[x][i-1] = 1;
        break;
      }
    }
    if(!chk){
      if(t==1) BLUE[x][5] = 1;
      else if(t==2) BLUE[x][4] = BLUE[x][5] = 1;
    }
  } else if(t==3){ // 도형 모양이 ㅁ 일 때
                   //            ㅁ
    bool chk = false;
    for (int i = 0; i < 6; i++) {
      // x, x+1 행에서 0~5열 사이에 도형이 있는지 찾고, 있으면 그 앞에, 없으면 맨 끝에 도형 붙임
      if(BLUE[x][i] || BLUE[x+1][i]){
        chk = true;
        BLUE[x][i-1] = BLUE[x+1][i-1] = 1;
        break;
      }
    }
    if(!chk){
      BLUE[x][5] = BLUE[x+1][5] = 1;
    }
  }

  // GREEN의 도형 전달
  if(t==1 || t==3){ // 도형의 모양이 ㅁ, ㅁ 일 때
                    //                  ㅁ
    bool chk = false;
    for (int i = 0; i < 6; i++) {
      // 같은 열에서 0~5행 사이에 도형이 있는지 찾고, 있으면 그 앞에, 없으면 맨 끝에 도형 붙임
      if(GREEN[i][y]){
        chk = true;
        if(t==1) GREEN[i-1][y] = 1;
        else if(t==3) GREEN[i-2][y] = GREEN[i-1][y] = 1;
        break;
      }
    }
    if(!chk){
      if(t==1) GREEN[5][y] = 1;
      else if(t==3) GREEN[4][y] = GREEN[5][y] = 1;
    }
  } else if(t==2){ // 도형의 모양이 ㅁㅁ 일 때
    bool chk = false;
    for (int i = 0; i < 6; i++) {
      // y, y+1 열에서 0~5행 사이에 도형이 있는지 찾고, 있으면 그 앞에, 없으면 맨 끝에 도형 붙임
      if(GREEN[i][y] || GREEN[i][y+1]){
        chk = true;
        GREEN[i-1][y] = GREEN[i-1][y+1] = 1;
        break;
      }
    }
    if(!chk){
      GREEN[5][y] = GREEN[5][y+1] = 1;
    }
  }

}

int main(){
  // 규칙1. RED에 들어간 도형은 각각 BLUE에는 같은 행을 유지하며 수평으로, GREEN에는 같은 열을 유지하며 수직으로 전달된다.
  // 규칙2. 크기가 2인 도형이 이동 중 두 칸중 하나에라도 다른 도형에 닿으면 해당 위치서 멈춘다.
  // 규칙3. 테트리스: BLUE-한 열, GREEN-한 행이 도형으로 가득 찬 경우 해당 지역을 비우고 위에 남은 도형을 아래로 내린다
  // 규칙4. 규칙3 테트리스 적용 후, 다시 테트리스가 가능하면 3번으로 돌아가 다시 테트리스
  // 규칙5. 연한칸 내리기: BLUE-0/1열, GREEN-0/1행에 도형이 있는 경우, 아래로 그 행/열 수만큼 도형을 전부 내림
  // 전체: 1(2는 1의 로직에 포함) -> WHILE(!테트리스) { 3 수행 } -> 5

  cin >> N;
  for (int i = 0; i < N; i++) {
    int t, x, y;
    cin >> t >> x >> y;
    input_red(t,x,y);
    //test_print();
    move_block(t,x,y);
    tetris_block();
    push_opaque();
    init();
  }

  //test_print();
  //tetris_block();
  //test_print();

  count_blocks();
  cout << score << endl << blocks << endl;

  return 0;
}
