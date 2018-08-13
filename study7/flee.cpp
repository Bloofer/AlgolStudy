#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int T, N, M, R, C, L;
typedef struct{
    bool up, down, left, right;
    bool visited;
}Hole;
Hole holes[50][50];
int input[50][50];
int sol;

void init(){
    for(int j=0; j<N; j++){
        for(int k=0; k<M; k++){
            if(input[j][k] == 0) holes[j][k].up = holes[j][k].down = holes[j][k].left
                                = holes[j][k].right = holes[j][k].visited = 0;
            else if(input[j][k] == 1) { holes[j][k].up = holes[j][k].down = holes[j][k].left
                                = holes[j][k].right = 1; 
                                holes[j][k].visited = 0;
                                }
            else if(input[j][k] == 2) { holes[j][k].up = holes[j][k].down = 1; 
                                holes[j][k].visited = holes[j][k].left
                                = holes[j][k].right = 0;
                                }
            else if(input[j][k] == 3) { holes[j][k].left = holes[j][k].right = 1; 
                                holes[j][k].up = holes[j][k].down
                                = holes[j][k].visited = 0;
                                }
            else if(input[j][k] == 4) { holes[j][k].up = holes[j][k].right = 1; 
                                holes[j][k].left = holes[j][k].down
                                = holes[j][k].visited = 0;
                                }
            else if(input[j][k] == 5) { holes[j][k].down = holes[j][k].right = 1; 
                                holes[j][k].up = holes[j][k].left
                                = holes[j][k].visited = 0;
                                }
            else if(input[j][k] == 6) { holes[j][k].left = holes[j][k].down = 1; 
                                holes[j][k].up = holes[j][k].right
                                = holes[j][k].visited = 0;
                                }
            else if(input[j][k] == 7) { holes[j][k].up = holes[j][k].left = 1; 
                                holes[j][k].down = holes[j][k].right
                                = holes[j][k].visited = 0;
                                }
            else {
                cerr << "input error : input must be in between 0~7" << endl;
                return;
            }
        }
    }
    sol = 0;
}

void test_print(){
    cout << N << " " << M << " " << R << " " << C << " " << L << endl;
    for(int j=0; j<N; j++){
        for(int k=0; k<M; k++){
            cout << input[j][k] << " ";
        }
        cout << endl;
    }
}

void print_holes(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cout << holes[i][j].up << holes[i][j].down << holes[i][j].left 
                 << holes[i][j].right << holes[i][j].visited << " ";
        }
        cout << endl;
    }
}

void start_alg(int row, int col, int cnt, int dir){

    //cout << row+1 << col+1 << "," << L-cnt << dir << " ";
    if(dir == 1) { if(!holes[row][col].up) return; }
    else if(dir == 2) { if(!holes[row][col].down) { return; } }
    else if(dir == 3) { if(!holes[row][col].left) return; }
    else if(dir == 4) { if(!holes[row][col].right) return; }

    if(holes[row][col].visited || cnt < 0) return;
    else {
        //cout << " ! ";
        holes[row][col].visited = 1;
        sol++;
        if(holes[row][col].up && row > 0) start_alg(row-1, col, cnt-1, 2);
        if(holes[row][col].down && row < N-1) start_alg(row+1, col, cnt-1, 1);
        if(holes[row][col].left && col > 0) start_alg(row, col-1, cnt-1, 4);
        if(holes[row][col].right && col < M-1) start_alg(row, col+1, cnt-1, 3);
    }

}

void read_file(string fileName){
    ifstream iFile(fileName.c_str());
    iFile >> T;

    for(int i=0; i<T; i++){
        iFile >> N >> M >> R >> C >> L;
        for(int j=0; j<N; j++){
            for(int k=0; k<M; k++){
                iFile >> input[j][k];
            }
        }
        //test_print();
        init();
        //print_holes();
        start_alg(R, C, L-1, 0);
        cout << sol << endl;
    }
}

int main(int argc, char** argv){

    if(argc < 2){
        cerr << "Usage : ./a.out INPUTFILE" << endl;
        return 1;
    }

    read_file(argv[1]);

    return 0;

}