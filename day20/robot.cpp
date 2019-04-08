#include <iostream>
using namespace std;

bool arr[50][50]; // 전체 지도
int N, M; // 지도의 크기 N * M
bool clean[50][50]; // 청소된 셀 상태 지도

bool idx_valid(int x, int y){
    // 해당 좌표가 지도에서 유효한지 검사
    return (x >= 0) && (y >= 0) && (x < N) && (y < M);
}

pair<int, int> get_dir_idx(int x, int y, int dir){
    // 해당 좌표와 방향에 따른 다음 위치 반환 함수
    if(dir == 0) return pair<int, int>(x-1, y);
    else if(dir == 1) return pair<int, int>(x, y+1);
    else if(dir == 2) return pair<int, int>(x+1, y);
    else return pair<int, int>(x, y-1);
}

void start_clean(int a, int b, int d){
    // 로봇청소기가 더이상 이동못할때까지 청소하는 함수

    // 로봇청소기 현상태 초기화
    int x = a;
    int y = b;
    int dir = d;

    bool finish = false;
    int cnt = 0;
    while(!finish){
        // 로봇청소기가 더이상 청소할 수 없을때까지 진행
        
        // 1. 현재 위치를 청소
        clean[x][y] = true;

        int dirCnt = 0;
        for(int i=0; i<4; i++){
            // 2. 현재 위치에서 현재 방향을 기준으로 왼쪽부터 탐색
            dir = (dir + 3) % 4;
            // 2-1. 왼쪽 방향에 청소안된 공간 있으면, 회전 및 한칸 전진후 1번 진행
            pair<int, int> nextIdx = get_dir_idx(x, y, dir);
            if(idx_valid(nextIdx.first, nextIdx.second) && !arr[nextIdx.first][nextIdx.second]) {
                // 해당 좌표가 범위를 벗어나지 않고, 벽이 없는 공간이면서
                if(!clean[nextIdx.first][nextIdx.second]) {
                    // 청소되지 않은 공간이라면, 한칸 전진
                    x = nextIdx.first;
                    y = nextIdx.second;
                    break;
                }
            }
            dirCnt++;       
            // 2-2. 왼쪽 방향에 청소할 공간이 없다면, 그 방향으로 회전후, 2번으로 돌아감
        }

        if(dirCnt==4){
            // 네방향 모두 청소가 되어있을때
            int rearDir = (dir + 2) % 4;
            pair<int, int> rearIdx = get_dir_idx(x, y, rearDir);
            if(idx_valid(rearIdx.first, rearIdx.second) && !arr[rearIdx.first][rearIdx.second]){
                // 2-3. 뒤 좌표가 유효하며, 뒤에 벽이 없는 경우 뒤로 한칸 후진한다.
                x = rearIdx.first;
                y = rearIdx.second;
            } else {
                // 2-4. 뒤 좌표가 유효하지 않거나, 뒤에 벽이 있는 경우 종료한다.
                finish = true;
                break;
            }
        }
    }
}

int main(){
    
    /*
     * 시뮬레이션 문제
     * 문제에서 주어진 로봇청소기의 탐색알고리즘을 그대로 구현
     */

    cin >> N >> M;

    int r,c,d;
    cin >> r >> c >> d;

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> arr[i][j];
        }
    }

    start_clean(r, c, d);
    int cnt = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(clean[i][j]) cnt++;
        }
    }
    cout << cnt << endl; 

    return 0;
}