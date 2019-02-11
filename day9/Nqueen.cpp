#include <iostream>
#include <fstream>
using namespace std;

int N; // 체스판의 크기와 퀸의 갯수
bool arr[10][10]; // 체스판: 퀸이 있으면 1, 없으면 0
int cnt = 0;

bool chk_queen(int x, int y){
// x,y 좌표를 받아 해당 자리에 퀸을 놓을 수 있는 지 확인
    bool chk = false;
    for(int i=0; i<N; i++) chk |= arr[x][i]; // 같은 행 체크
    for(int i=0; i<N; i++) chk |= arr[i][y]; // 같은 열 체크

    // 대각선 4방향 검사
    int i = x - 1;
    int j = y - 1;
    // (x, y) -> 좌측상단
    while(i >= 0 && j >= 0) {
        chk |= arr[i][j];
        i--;
        j--;
    }
    // (x, y) -> 우측하단
    i = x + 1;
    j = y + 1;
    while(i < N && j < N){
        chk |= arr[i][j];
        i++;
        j++;
    }
    // (x, y) -> 좌측하단
    i = x + 1;
    j = y - 1;
    while(i < N && j >= 0){
        chk |= arr[i][j];
        i++;
        j--;
    }
    // (x, y) -> 우측상단
    i = x - 1;
    j = y + 1;
    while(i >= 0 && j < N){
        chk |= arr[i][j];
        i--;
        j++;
    }

    return chk; // false면 놓을 수 있음. true면 못 놓음
}

void dfs(int cur){
    // Base Case
    if(cur == N) {
        cnt++;
        return;
    }

    // Recursive Case
    for(int i=0; i<N; i++){
        if(chk_queen(cur, i)) {
            continue;
        }
        else {
            arr[cur][i] = true;
            dfs(cur+1);
            arr[cur][i] = false;
        }
    }
}

void read_file(){
    int testNum;
    cin >> testNum;

    for(int i=0; i<testNum; i++){
        cin >> N;
        dfs(0);
        cout << "#" << i+1 << " " << cnt << endl;
        cnt = 0;
    }
}

int main(int argc, char** argv){
    read_file();
    return 0;
}