#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

int N; // 배열의 크기
int teamNum = 0; // 영역마다 주어지는 팀번호
int height = 3;

typedef struct{
    int team = -1;
    int val;
}Cell;
vector< vector<Cell> > map; // 전역 맵 생성

void read_file(string fileName){
    ifstream iFile(fileName.c_str());

    iFile >> N;
    for(int i=0; i<N; i++){
        vector<Cell> cellVec;
        for(int j=0; j<N; j++){
            Cell tmp;
            iFile >> tmp.val;
            cellVec.push_back(tmp);
        }
        map.push_back(cellVec);
    }
}

queue< pair<int, int> > bfsQ;

void bfs(int x, int y){
    if(map[x][y].team!=-1) return; // 팀 선정이 안된 영역만 탐사
    
    while(!bfsQ.empty()){
        if(x < N-1) if(abs(map[x][y].val-map[x+1][y].val) < height) bfs(x+1, y);
        if(x > 0) if(abs(map[x][y].val-map[x-1][y].val) < height) bfs(x-1, y);
        if(y < N-1) if(abs(map[x][y].val-map[x][y+1].val) < height) bfs(x, y+1);
        if(y > 0) if(abs(map[x][y].val-map[x][y-1].val) < height) bfs(x, y-1);
    }
}

int main(int argc, char **argv){
    if(argc < 2) return 1;
    read_file(argv[1]);

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << map[i][j].val << "," << map[i][j].team << " ";
        }
        cout << endl;
    }

    return 0;
}