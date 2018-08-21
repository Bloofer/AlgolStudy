#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int T, N;
int dst[20][20];
int sol;
bool chk[101];
bool dirs[4];
int way[4][2] = 
    { {-1, -1},
      {1, -1}, 
      {-1, 1}, 
      {1, 1} };

void init(){
    for(int i=0; i<101; i++) chk[i] = 0;
    for(int i=0; i<4; i++) dirs[i] = 0;
}

int get_rev(int i){
    if(i == 0) return 3; // if left & up
    else if (i == 1) return 2; // if left & down
    else if (i == 2) return 1; // if right & down
    else if (i == 3) return 0; // if right & up
    else return -1; // error case
}

int max(int a, int b){
    return a > b ? a : b;
}

bool in_range(int x, int y){
    return (x >= 0) && (y >= 0) && (x < N) && (y < N);
}

void dfs(int bgnX, int bgnY, int x, int y, int cnt, int dir){

    if (x == bgnX && y == bgnY){
        sol = max(sol, cnt);
        return;
    }

    for(int i=0; i<4; i++) {
        // skip the opposite direction which you came from
        if (i == get_rev(dir)) continue;

        if (i != dir && dirs[i]) continue;

        int nextX, nextY;
        nextX = x + way[i][0];
        nextY = y + way[i][1]; 

        if (!in_range(nextX, nextY)) continue;

        int nextDst = dst[nextX][nextY];

        if (bgnX == nextX && bgnY == nextY) dfs(bgnX, bgnY, nextX, nextY, cnt, i);

        if (chk[nextDst]) continue;

        dirs[i] = chk[nextDst] = true;
        dfs(bgnX, bgnY, nextX, nextY, cnt+1, i);
        dirs[i] = chk[nextDst] = false;
    }

}

void start_alg(){

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            init(); // init path and check array
            int nextX, nextY;
            nextX = i + way[3][0];
            nextY = j + way[3][1]; 

            if(!in_range(nextX, nextY)) continue;

            int bgnDst = dst[i][j];
            int nxtDst = dst[nextX][nextY];

            if (bgnDst != nxtDst){
                chk[bgnDst] = chk[nxtDst] = dirs[3] = true;
                dfs(i, j, nextX, nextY, 2, 3);
                chk[bgnDst] = chk[nxtDst] = dirs[3] = false;
            }
        }
    }

}

void test_print(){

    cout << N << endl;
    for(int j = 0; j < N; j++) { 
        for(int k = 0; k < N; k++) {
            cout << dst[j][k] << " ";
        } 
        cout << endl;
    }

}

//void read_file(string fileName){
void read_file(){

    //ifstream iFile(fileName.c_str());

    //iFile >> T;
    cin >> T;

    for(int i = 0; i < T; i++){
        //iFile >> N;
        cin >> N;
        for(int j = 0; j < N; j++) { for(int k = 0; k < N; k++) /* iFile >> dst[j][k]; */ cin >> dst[j][k]; }
        sol = -1;
        start_alg();
        cout << "#" << i+1 << " " << sol << endl;
    }

}

int main(int argc, char **argv) {

    /* if(argc < 2){
        cerr << "Usage : ./a.out INPUTFILE" << endl;
        return 1;    
    } */

    //read_file(argv[1]);
    read_file();

    return 0;

}