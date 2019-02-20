#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <vector>
using namespace std;

int map[12][12]; // N명의 고객, 회사, 집 간 거리를 나타낸 2차원 배열
bool visit[12];
int N;
int minVal;
vector< pair<int, int> > locVec; // 회사, 집, 고객들 좌표

int min_val(int a, int b){
    return a < b ? a : b;
}

int cal_path(int x1, int y1, int x2, int y2){
    return abs(x1-x2) + abs(y1-y2);
}

void dfs(int cnt, int prev, int sum){
    // Base Case
    if(cnt == N) {
        minVal = min_val(minVal, sum);
    }

    // Recursive Case
    for(int i=0; i<N; i++){
        if(cnt!=N-1 && i==1) continue; // 집 가는 경로는 맨 마지막에만

        if(!visit[i]){
            // 탐사안된 경로를 찾아 DFS
            if(minVal<sum+map[prev][i]){
                visit[i] = true;
                dfs(cnt+1, i, sum+map[prev][i]);
                //cout << cnt+1 << " " << i << " " << map[prev][i] << endl;
                visit[i] = false;
            }
            
        }
    }
}

void build_map(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            map[i][j] = cal_path(locVec[i].first, locVec[i].second, locVec[j].first, locVec[j].second);
        }
    }
}

void init(){
    N += 2;
    minVal = INT_MAX;
    for(int i=0; i<N; i++){
        visit[i] = false;
    }
    locVec.clear();
}

//void read_file(string fileName){
void read_file(){
    //ifstream iFile(fileName.c_str());

    int testNum;
    
    //iFile >> testNum;
    cin >> testNum;
    for(int i=0; i<testNum; i++){
        //iFile >> N;
        cin >> N;
        init();
        for(int j=0; j<N; j++){
            int x, y;
            //iFile >> x >> y;
            cin >> x >> y;
            locVec.push_back(pair<int, int>(x, y));
        }
        build_map();
        
        visit[0] = true;
        dfs(1, 0, 0);
        cout << "#" << i+1 << " " << minVal << endl;
    }
}

int main(int argc, char** argv){
    //read_file(argv[1]);
    read_file();
    return 0;
}