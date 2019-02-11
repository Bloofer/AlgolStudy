#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

int arr[100][100]; // 사다리 배치 배열
pair<int, int> minPath; // 가장 짧은 배열, 인덱스

bool chk_side(int x, int y){
    // 사다리 양옆을 확인하여 이동가능한지 확인하는 함수
    if(y>0 && y<99) return ((arr[x][y-1]) || arr[x][y+1]);
    else if(y==99) return arr[x][y-1];
    else if(y==0) return arr[x][y+1];
    else return false;
}

void explore(){
    vector<int> startPoint; // 시작 지점 벡터

    for(int i=0; i<100; i++){
        if(arr[0][i]) startPoint.push_back(i);
    }

    minPath = pair<int, int>(0, INT_MAX);
    for(auto i : startPoint){
        bool visit[100][100] = {0, };
        int x = 0;
        int y = i;
        int cnt = 1;
        while(x<99 || chk_side(x,y)){
            if(x!=0 && y>0 && !visit[x][y-1] && arr[x][y-1]) {
                // 왼쪽으로 갈 수 있는 경우
                visit[x][y] = 1;
                y--;
                cnt++;
            } else if(x!=0 && y<99 && !visit[x][y+1] && arr[x][y+1]) {
                // 오른쪽으로 갈 수 있는 경우
                visit[x][y] = 1;
                y++;
                cnt++;
            } else {
                if(x==99) break;
                // 아래로 내려가기
                visit[x][y] = 1;
                x++;
                cnt++;
            }
        }

        if(cnt <= minPath.second) {
            minPath = pair<int, int>(i, cnt);
        }
    }   

}

void read_file(){

    int testNum;

    for(int i=0; i<10; i++){
        cin >> testNum;
        for(int j=0; j<100; j++){
            for(int k=0; k<100; k++){
                cin >> arr[j][k];
            }
        }

        cout << "#" << i+1;
        explore(); // 탐사 시작
        cout << " " << minPath.first << endl;
    }

}

int main(int argc, char** argv){
    //read_file(argv[1]);
    read_file();
    return 0;
}