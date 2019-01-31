#include <string>
#include <vector>
#include <iostream>
using namespace std;

int pathNum = 0;
int N, M;
bool path[100][100];

void find_path(int x, int y){
    // Base Case
    if((x == N-1) && (y == M-1)) {
        pathNum++;
        return;
    }

    // Recursive Case
    if(x < N-1 && !path[x+1][y]) find_path(x+1,y);
    if(y < M-1 && !path[x][y+1]) find_path(x,y+1);
}

int solution(int m, int n, vector<vector<int>> puddles) {
    N = n;
    M = m;
    for(int i=0; i<puddles.size(); i++){
        path[puddles[i][1]-1][puddles[i][0]-1] = true; // 웅덩이 있는 곳 마킹
    }
    
    find_path(0,0);
    return pathNum;
}