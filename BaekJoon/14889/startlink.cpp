#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

int N; // 직원 수
int stats[20][20]; // 직원들 능력치 배열
int minVal = INT_MAX; // 두 팀간 최소 능력치 차
bool visited[20]; // dfs에서 방문된 노드 마킹용 배열

int get_min(int a, int b){
    return a < b ? a : b;
}

int cal_stats(){
    // 두 팀의 능력치 합을 계산, 차를 반환한다
    int stat1 = 0;
    int stat2 = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(visited[i] && visited[j]) stat1 += stats[i][j];
            else if(!visited[i] && !visited[j]) stat2 += stats[i][j];
        }
    }

    return abs(stat1-stat2);
}

void dfs(int cur, int marked){
    // Base Case
    if(marked == N/2){
        minVal = get_min(minVal, cal_stats());
        return;
    }
    if(cur == N) return;

    // Recursive Case
    visited[cur] = true;
    dfs(cur+1, marked+1);
    visited[cur] = false;
    dfs(cur+1, marked);
}

void read_file(string fileName){
    ifstream iFile(fileName.c_str());

    iFile >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) iFile >> stats[i][j];
    }
}

int main(int argc, char** argv){

    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> stats[i][j];
    }

    dfs(1, 0);
    cout << minVal << endl;

    return 0;
}