#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int res;
vector<int> moves;

typedef struct{
    bool up, down, left, right; // 현재의 셀에서 경로가 지나갔는지 여부 판별
}Path;

Path map[1000][1000]; // 표 위의 움직임을 그리는 지도
int x = 500;
int y = 500; // 초기값은 맵의 중간부터 시작

void read_file(string fileName){
    ifstream iFile(fileName.c_str());

    int n;
    char c;
    iFile >> n;
    for(int i=0; i<n; i++){
        iFile >> c;
        // 0:상, 1:하, 2:좌, 3:우
        if(c=='U') moves.push_back(0);
        else if(c=='D') moves.push_back(1);
        else if(c=='L') moves.push_back(2);
        else if(c=='R') moves.push_back(3);
    }
    iFile >> res;
}

void write_map(){
    for(int i=0; i<moves.size(); i++){
        if(moves[i]==0) {
            // 1. 상단 이동
            x--;
            // 2. 현재 셀의 left, 좌측 셀의 right 마킹
            map[x][y].left = true;
            map[x][y-1].right = true;
        }
        else if(moves[i]==1) {
            // 1. 현재 셀의 left, 좌측 셀의 right 마킹
            map[x][y].left = true;
            map[x][y-1].right = true;
            // 2. 하단 이동
            x++;
        }
        else if(moves[i]==2) {
            // 1. 좌측 이동
            y--;
            // 2. 현재 셀의 up, 상단 셀의 down 마킹
            map[x][y].up = true;
            map[x-1][y].down = true;
        }
        else if(moves[i]==3) {
            // 1. 현재 셀의 up, 상단 셀의 down 마킹
            map[x][y].up = true;
            map[x-1][y].down = true;
            // 2. 우측 이동
            y++;
        }
    }
}

int main(int argc, char** argv){
    if(argc < 2) return 1;
    read_file(argv[1]);

    // 지도위에 경로를 따라 마킹함
    write_map();

    // 지도위에 있는 1*1 정사각형 수 계수
    int cnt = 0;
    for(int i=0; i<1000; i++){
        for(int j=0; j<1000; j++){
            if(map[i][j].up && map[i][j].down && map[i][j].left && map[i][j].right) cnt++;
        }    
    }

    cout << cnt << endl;

    return 0;
}