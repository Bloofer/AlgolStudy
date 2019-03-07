#include <iostream>
#include <vector>
using namespace std;

int N, K, L;
int board[101][101];
int apple[101][101];
vector< pair<int, char> > moves;

bool chk_bound(int x, int y){
    return ((x > 0) && (y > 0) && (x < N+1) && (y < N+1));
}

void start_move(){
    int clk = 0;
    bool cnd = false;

    // condition
    pair<int, int> head;
    int dir = 0; // 0: 오른쪽, 1: 아래, 2: 왼쪽, 3: 위

    while(!cnd){
        clk++;

    }

}

int main(){

    cin >> N >> K;
    int x, y;
    for(int i=0; i<K; i++) {        
        cin >> x >> y;
        apple[x][y] = 1;
    }

    cin >> L;
    int n;
    char c;
    for(int i=0; i<L; i++){        
        cin >> n >> c;
        moves.push_back(pair<int, char>(n, c));
    }

    return 0;
}