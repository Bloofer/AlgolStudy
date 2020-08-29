#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

typedef struct{
    int x, y, dir;
    bool dead;
}FISH;

FISH fishArr[16]; // 물고기 번호는 인덱스, 물고기의 위치 및 방향 정보 배열
int arr[4][4];    // 각 배열 내 엔트리는 물고기 번호 나타냄
                  // FISH의 배열을 4*4 배열에 물고기들 번호로, -1인 위치는 물고기 없음, -2인 위치는 상어 존재
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int maxFeed = 0;

int get_max(int a, int b){ return a > b ? a : b; }
bool available(int x, int y){ return x >= 0 && y >= 0 && x < 4 && y < 4; }

void move_fish(){
    for(int i=0; i<16; i++){
        // 1. 1번 물고기부터 16번 물고기까지 모든 물고기 이동 시작
        bool move = false;
        int cnt = 0;
        int x = fishArr[i].x;
        int y = fishArr[i].y;
        if(arr[x][y]<0 || fishArr[i].dead) continue; // 물고기가 죽거나 상어가 위치한 배열의 경우 제외

        while(!move && cnt <= 8){ // 이동 가능한 경우, 물고기를 이동하고 while문을 빠져나옴
            cnt++;
            if(move) break;
            // 2. 물고기는 이동할 수 있을때까지 8-방향을 전환해가며 반복
            int nx = x + dx[fishArr[i].dir];
            int ny = y + dy[fishArr[i].dir];

            if(available(nx, ny) && arr[x][y]>=0 && arr[nx][ny]!=-2){
                if(arr[nx][ny] >= 0) {
                    // 3. 만약 해당 위치에 다른 물고기가 있을 시, 현재 물고기와 해당 위치의 물고기를 서로 바꿈
                    move = true;
                    swap(fishArr[arr[nx][ny]].x, fishArr[i].x);
                    swap(fishArr[arr[nx][ny]].y, fishArr[i].y);
                    swap(arr[x][y], arr[nx][ny]);
                    break;
                } else if(arr[nx][ny]==-1) {
                    // 4. 해당 위치가 비어있을 시, 현재 물고기를 해당 위치로 옮김
                    move = true;
                    fishArr[i].x = nx;
                    fishArr[i].y = ny;
                    swap(arr[x][y], arr[nx][ny]);
                    break;
                    // *반례: N번째의 물고기가 비어있는 N+1번째 물고기의 칸으로 이동했을 때, i=N+1의 반복문에서 한번 이동한 물고기가 다시 이동할 수 있기에 예외처리
                }

            } else { // 5. 이동 불가능한 경우, 물고기 방향을 하나 회전하고 다시 반복 진행
                fishArr[i].dir++;
                fishArr[i].dir%=8;
            }
        }
    }
}

void copy_arr(int fromArr[][4], int toArr[][4], FISH fromFish[], FISH toFish[]){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            toArr[i][j] = fromArr[i][j];
            toFish[4*i+j] = fromFish[4*i+j];
        }
    }
}

void dfs_shark(int nx, int ny, int feed, int fdir){
    // 1. 해당 위치에 들어간 상어는 해당 물고기의 방향을 가짐
    maxFeed = get_max(maxFeed, feed);

    FISH tmpFishArr[16];
    int tmpArr[4][4];
    copy_arr(arr, tmpArr, fishArr, tmpFishArr);
    // 2. 살아남은 물고기에 한해, 모든 물고기는 이동
    move_fish();

    // 3. 해당 방향에서 갈 수 있는 모든 경우에 대해, 다시 재귀적으로 탐사함
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
                int tmpDir = fishArr[tmpNum].dir;
                arr[nx][ny] = -1;
                arr[nextX][nextY] = -2;
                fishArr[tmpNum].dead = true;
                dfs_shark(nextX, nextY, feed+tmpNum+1, tmpDir);
                fishArr[tmpNum].dead = false;
                arr[nextX][nextY] = tmpNum;
                arr[nx][ny] = -2;
                // 4. 재귀 호출에서 빠져나온 상어와 물고기 상태를 원래로 원복
            }
        }
    }
    copy_arr(tmpArr, arr, tmpFishArr, fishArr);
}

int main()
{
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            int dir;
            cin >> arr[i][j]; // 물고기의 위치
            arr[i][j]--;
            cin >> dir; // 물고기의 방향
            FISH tmpFish {i, j, dir-1, false};
            fishArr[arr[i][j]] = tmpFish;
        }
    }

    int tmpNum = arr[0][0];
    int tmpDir = fishArr[arr[0][0]].dir;
    fishArr[arr[0][0]].dead = true;
    arr[0][0] = -2; // DFS함수를 부를 때, 상어가 들어갈 곳의 물고기 배열을 비우고 해당 위치에 상어가 들어감
    dfs_shark(0, 0, tmpNum+1, tmpDir); // 물고기의 크기와 방향을 전달함

    cout << maxFeed << endl;

    return 0;
}
