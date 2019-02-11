#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

typedef struct{
    int x, y; // 명령어 좌표
    int mem;  // 메모리 값(0~15)
    int dir;  // 0:상 1:하 2:좌 3:우
}Status;

char ops[21][21];
int r, c;
queue<Status> statQueue;    // 현재 탐지 상태 나타내는 큐
bool halt;                  // 종료 조건

void move(Status &stat){
// 주어진 stat의 이동방향에 따라 움직임
    if(stat.dir == 0){
        if(stat.x==0) stat.x=r-1;
        else stat.x--;
    } else if(stat.dir == 1){
        if(stat.x==r-1) stat.x=0;
        else stat.x++;
    } else if(stat.dir == 2){
        if(stat.y==0) stat.y=c-1;
        else stat.y--;
    } else if(stat.dir == 3){
        if(stat.y==c-1) stat.y=0;
        else stat.y++;
    } 
}

void bfs(){
    bool visited[20][20][4][16] = {0, }; // 좌표 * 방향 * 메모리 값이 탐지된 지역인지 체크

    while(!statQueue.empty()){
        Status stat = statQueue.front();
        statQueue.pop();
        char op = ops[stat.x][stat.y];

        // 이미 탐사한 지역이면 종료, 아니면 마킹
        if(visited[stat.x][stat.y][stat.dir][stat.mem]) continue;
        else visited[stat.x][stat.y][stat.dir][stat.mem] = true;

        if(op=='<'){
            stat.dir = 2;
        } else if(op=='>'){
            stat.dir = 3;
        } else if(op=='^'){
            stat.dir = 0;
        } else if(op=='v'){
            stat.dir = 1;
        } else if(op=='_'){
            if(stat.mem == 0) stat.dir = 3;
            else stat.dir = 2;
        } else if(op=='|'){
            if(stat.mem == 0) stat.dir = 1;
            else stat.dir = 0;
        } else if(op=='?'){
            // 상하좌우 탐사 모두 큐에 삽입
            Status tmp = stat;
            tmp.dir = 0;
            move(tmp);
            statQueue.push(tmp);
            
            tmp = stat;
            tmp.dir = 1;
            move(tmp);
            statQueue.push(tmp);

            tmp = stat;
            tmp.dir = 2;
            move(tmp);
            statQueue.push(tmp);
            
            tmp = stat;
            tmp.dir = 3;
            move(tmp);
            statQueue.push(tmp);
            continue;
        } else if(op=='@'){
            // 종료조건 발견
            halt = true;
            return;
        } else if(op>='0'&&op<='9'){
            stat.mem = op - '0';
        } else if(op=='+'){
            if(stat.mem == 15) stat.mem = 0;
            else stat.mem++;
        } else if(op=='-'){
            if(stat.mem == 0) stat.mem = 15;
            else stat.mem--;
        }

        move(stat);
        statQueue.push(stat);            
    }
}

void read_file(){
    int N;
    cin >> N;

    for(int p=0; p<N; p++){
        cin >> r >> c;
        for(int i=0; i<r; i++){
            for(int j=0; j<c; j++) cin >> ops[i][j];
        }
        Status stat;
        stat.dir = 3;
        stat.mem = 0;
        stat.x = stat.y = 0;
        statQueue.push(stat);
        bfs();
        cout << "#" << p+1 << " ";
        if(halt) cout << "YES" << endl;
        else cout << "NO" << endl;
        halt = false;
        while(!statQueue.empty()) statQueue.pop();
    }
}

int main(int argc, char** argv){
    read_file();
    return 0;
}