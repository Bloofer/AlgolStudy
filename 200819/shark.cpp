#include <iostream>
#include <string>
using namespace std;

typedef struct{
    int x, y, dir;
}FISH;

int fishDir[16];
FISH fishArr[16]; // 물고기 번호는 인덱스, 물고기의 위치 및 방향 정보는 엔트리 안에
int arr[4][4];    // 각 배열 내 엔트리는 물고기 번호 나타냄
// FISH의 배열을 4*4 배열에 물고기들 번호로, -1인 위치는 물고기 없음
FISH shark;
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
// dir: ↑, ↖, ←, ↙, ↓, ↘, →, ↗
// dir: 1, 2, 3,  4, 5, 6,  7, 8
int maxFeed = 0;

int get_max(int a, int b){
    return a > b ? a : b;
}

bool available(int x, int y){
    return x >= 0 && y >= 0 && x < 4 && y < 4;
}

char get_dir(int i){
    if(i==0) return '↑';
    else if(i==1) return '↖';
    else if(i==2) return '←';
    else if(i==3) return '↙';
    else if(i==4) return '↓';
    else if(i==5) return '↘';
    else if(i==6) return '→';
    else if(i==7) return '↗';
    else return ' ';
}

void test_print(){
    // for(int i=0; i<16; i++){
    //     if(i%4 == 0) cout << endl;
    //     cout << fishArr[i].x << " " << fishArr[i].y <<  " @" << fishArr[i].dir << " ";
    // }
    cout << endl;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        //string ss = get_dir(fishArr[arr[i][j]].dir);
        cout << arr[i][j]+1 << "|" << fishArr[arr[i][j]].dir+1 << "\t";
      }
      cout << endl;
    }
}

void move_fish(){
    for(int i=0; i<16; i++){
        // 물고기는 한 칸을 이동할 수 있고, 이동할 수 있는 칸은 빈칸과 다른 물고기가 있는 칸 | 이동하지 못하는 칸은 상어가 있거나 경계 바깥

        bool move = false;
        int x = fishArr[i].x;
        int y = fishArr[i].y;

        if(arr[x][y]==-1) continue;

        while(!move){
            // 물고기는 이동할 수 있을때까지 방향을 전환해가며 반복
            int nx = x + dx[fishArr[i].dir];
            int ny = y + dy[fishArr[i].dir];

            if(available(nx, ny) && !(nx==shark.x && ny==shark.y)){ // 이동 가능한 경우, 물고기를 이동하고 while문을 빠져나옴
                move = true;
                int tmpNum = arr[nx][ny];
                if(arr[nx][ny] != -1) { // 1. 만약 해당 위치에 다른 물고기가 있을 시,
                    // 2. 현재 물고기와 해당 위치의 물고기를 바꾸고, 방향도 바꿔줌
                    FISH tmp;
                    tmp.x = fishArr[tmpNum].x;
                    tmp.y = fishArr[tmpNum].y;

                    // swap fish
                    fishArr[tmpNum].x = fishArr[i].x;
                    fishArr[tmpNum].y = fishArr[i].y;
                    arr[nx][ny] = i;

                    fishArr[i].x = tmp.x;
                    fishArr[i].y = tmp.y;
                    arr[x][y] = tmpNum;
                } else { // 3. 해당 위치가 비어있을 시,
                    // 4. 현재 물고기를 해당 위치로 옮김
                    arr[x][y] = -1;
                    fishArr[i].x = nx;
                    fishArr[i].y = ny;
                    arr[x][y] = tmpNum;
                }

            } else { // 이동 불가능한 경우, 물고기 방향을 하나 회전하고 다시 반복 진행
                fishArr[i].dir++;
                fishArr[i].dir%=8;
            }

        }
    }
}

void dfs_shark(int nx, int ny, int feed, int fdir){
    cout << nx << " " << ny << " " << fdir << " | " << feed << endl;

    // 1. 해당 위치에 들어간 상어는 해당 물고기의 방향을 가짐
    shark.x = nx;
    shark.y = ny;
    shark.dir = fdir;
    maxFeed = get_max(maxFeed, feed);

    // 살아남은 물고기에 한해, 모든 물고기는 이동
    move_fish();

    // 2. 해당 방향에서 갈 수 있는 모든 경우에 대해, 다시 재귀적으로 탐사함
    int nextX = nx;
    int nextY = ny;
    for(int i=0; i<3; i++){
        nextX += dx[fdir];
        nextY += dy[fdir];
        if(!available(nextX, nextY)){
            break;
        } else {
            if(arr[nextX][nextY]!=-1){
                int tmpNum = arr[nextX][nextY];
                int tmpDir = fishDir[arr[nextX][nextY]];
                arr[nextX][nextY] = -1;
                dfs_shark(nextX, nextY, feed+tmpNum, tmpDir);
                // 재귀 호출에서 빠져나온 상어는 원래 위치로 원복
                arr[nextX][nextY] = tmpNum;
                shark.x = nx;
                shark.y = ny;
                shark.dir = fdir;
            }
        }
    }
}

int main()
{
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            cin >> arr[i][j]; // 물고기의 위치
            arr[i][j]--;
            cin >> fishDir[arr[i][j]]; // 물고기의 방향
            fishDir[arr[i][j]]--;
            FISH tmpFish;
            tmpFish.x = i;
            tmpFish.y = j;
            tmpFish.dir = fishDir[arr[i][j]];
            fishArr[arr[i][j]] = tmpFish;
        }
    }

    int tmpNum = arr[0][0];
    int tmpDir = fishDir[arr[0][0]];
    arr[0][0] = -1; // DFS함수를 부를 때, 상어가 들어갈 곳의 물고기 배열을 비우고 해당 위치에 상어가 들어감
    dfs_shark(0, 0, tmpNum, tmpDir); // 물고기의 크기를 전달함

    cout << maxFeed << endl;

    return 0;
}
