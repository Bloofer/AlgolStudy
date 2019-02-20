#include <iostream>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

int arr[8][8];
int N, M;
int safeZone = INT_MIN;
int dx[4] = {-1,1,0,0}; // 상하좌우 이동
int dy[4] = {0,0,-1,1};

int max_val(int a, int b){
    return a > b ? a : b;
}

int cal_safe_zone(vector< vector<int> > &v){
    // 안전지역 계산 함수
    int sum = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(v[i][j]==0) sum++;
        }
    }
    return sum;
}

bool valid(int x, int y){
    // 탐사 좌표의 유효성 판단 함수
    if(x < 0 || y < 0 || x >= N || y >= M) return false;
    else return true;
}

void spread_germ(){
    // BFS로 세균 퍼트리는 함수
    queue< pair<int, int> > germQ;
    vector< vector<int> > map;
    for(int i=0; i<N; i++){
        vector<int> tmp;
        for(int j=0; j<M; j++) {
            tmp.push_back(arr[i][j]);
            if(arr[i][j]==2) germQ.push(pair<int, int>(i, j));
        } 
        map.push_back(tmp);
    }

    while(!germQ.empty()){
        pair<int, int> germ = germQ.front();
        germQ.pop();

        // 갈 수 있는 지역(벽없고, 빈땅) 최대한 탐사하여 큐가 빌때까지 세균 증식
        for(int i=0; i<4; i++){
            int x = germ.first+dx[i];
            int y = germ.second+dy[i];
            if(valid(x, y)){
                if(map[x][y]==0){
                    map[x][y] = 2;
                    germQ.push(pair<int, int>(x, y));
                }
            }
        }
    }

    safeZone = max_val(safeZone, cal_safe_zone(map));
}

void place_wall(int cnt){
    // 벽 세개를 DFS+백트랙킹으로 놓으면서 모든 경우 탐사하는 함수
    if(cnt==3){
        spread_germ(); // 벽 세개 다 세우면 세균 퍼뜨림
        return;
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(arr[i][j] == 0){
                arr[i][j] = 1;
                place_wall(cnt+1);
                arr[i][j] = 0;
            }
        }
    }    
}

int main(){
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> arr[i][j];
        }
    }

    place_wall(0);
    cout << safeZone << endl;
}
