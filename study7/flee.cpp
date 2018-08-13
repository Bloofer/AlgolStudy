#include <iostream>
#include <string>
#include <queue>
using namespace std;

typedef struct{
    bool up, down, left, right;
    bool visited;
}Hole;

typedef struct{
    int row, col, cnt, dir;
}Call;

int T, N, M, R, C, L;

Hole holes[50][50];
queue<Call> callQ;
int input[50][50];
int sol;

void set_hole(int row, int col, int up, int down, int left, int right, int visited){
    holes[row][col].up = up;
    holes[row][col].down = down;
    holes[row][col].left = left;
    holes[row][col].right = right;
    holes[row][col].visited = visited;
}

void init(){
    for(int j=0; j<N; j++){
        for(int k=0; k<M; k++){
            if(input[j][k] == 0) set_hole(j,k,0,0,0,0,0);
            else if(input[j][k] == 1) set_hole(j,k,1,1,1,1,0);
            else if(input[j][k] == 2) set_hole(j,k,1,1,0,0,0);
            else if(input[j][k] == 3) set_hole(j,k,0,0,1,1,0);
            else if(input[j][k] == 4) set_hole(j,k,1,0,0,1,0);
            else if(input[j][k] == 5) set_hole(j,k,0,1,0,1,0);
            else if(input[j][k] == 6) set_hole(j,k,0,1,1,0,0);
            else if(input[j][k] == 7) set_hole(j,k,1,0,1,0,0);
            else {
                cerr << "input error : input must be in between 0~7" << endl;
                return;
            }
        }
    }
    sol = 0;
}

void set_call(Call &c, int row, int col, int cnt, int dir){
    c.row = row;
    c.col = col;
    c.cnt = cnt;
    c.dir = dir;
}

void start_alg(){

    while(!callQ.empty()){

        Call tmpCall = callQ.front();
        callQ.pop();
        if(tmpCall.dir == 1) { if(!holes[tmpCall.row][tmpCall.col].up) continue; }
        else if(tmpCall.dir == 2) { if(!holes[tmpCall.row][tmpCall.col].down) continue; }
        else if(tmpCall.dir == 3) { if(!holes[tmpCall.row][tmpCall.col].left) continue; }
        else if(tmpCall.dir == 4) { if(!holes[tmpCall.row][tmpCall.col].right) continue; }

        if(holes[tmpCall.row][tmpCall.col].visited || tmpCall.cnt < 0) continue;
        else {
            holes[tmpCall.row][tmpCall.col].visited = 1;
            sol++;
            Call pushCall;
            if(holes[tmpCall.row][tmpCall.col].up && tmpCall.row > 0) {
                set_call(pushCall, tmpCall.row-1, tmpCall.col, tmpCall.cnt-1, 2);
                callQ.push(pushCall);
            }
            if(holes[tmpCall.row][tmpCall.col].down && tmpCall.row < N-1) {
                set_call(pushCall, tmpCall.row+1, tmpCall.col, tmpCall.cnt-1, 1);
                callQ.push(pushCall);
            }
            if(holes[tmpCall.row][tmpCall.col].left && tmpCall.col > 0) {
                set_call(pushCall, tmpCall.row, tmpCall.col-1, tmpCall.cnt-1, 4);
                callQ.push(pushCall);
            } 
            if(holes[tmpCall.row][tmpCall.col].right && tmpCall.col < M-1) {
                set_call(pushCall, tmpCall.row, tmpCall.col+1, tmpCall.cnt-1, 3);
                callQ.push(pushCall);
            } 
        }    

    }

}

void get_input(){
    cin >> T;

    for(int i=0; i<T; i++){
        cin >> N >> M >> R >> C >> L;
        for(int j=0; j<N; j++){
            for(int k=0; k<M; k++){
                cin >> input[j][k];
            }
        }
        init();
        Call pushCall;
        set_call(pushCall, R, C, L-1, 0);
        callQ.push(pushCall);
        start_alg();
        cout << "#" << i+1 << " " << sol << endl;
    }
}

int main(int argc, char** argv){

    get_input();

    return 0;

}