#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <queue>
#include <limits>
using namespace std;

int T; // 총 테스트 케이스 수
int N; // 배열의 크기
int map[10][10]; // 사무실 지도
int x1, y1, k1; // 계단 1의 x,y좌표, 계단 길이
int x2, y2, k2; // 계단 2의 x,y좌표, 계단 길이

int P1[10]; // 계단 1에 도착할 사람들의 시간
int p1Cnt; // dfs 최종 경로에서 계단 1 사용하는 사람 수
int P2[10]; // 계단 2에 도착할 사람들의 시간
int p2Cnt; // dfs 최종 경로에서 계단 1 사용하는 사람 수
bool P[10]; // 사람들이 선택할 계단 false - 계단1, true - 계단2
vector< pair<int, int> > P_IDX; // 사람들이 배치된 곳의 인덱스 (x, y)

int minT = __INT_MAX__; // 가장 최소가 되는 시간

int cal_time(int pr, int sr, int pc, int sc){
// - 이동 시간(분) = | PR - SR | + | PC - SC | 계산
    return abs(pr - sr) + abs(pc - sc);
}

void pre_calculate(){
// 계단에 내려가는 시간을 미리 계산하는 함수
// - 이동 시간(분) = | PR - SR | + | PC - SC |
// (PR, PC : 사람 P의 세로위치, 가로위치, SR, SC : 계단 입구 S의 세로위치, 가로위치)
    for(int i=0; i<P_IDX.size(); i++){
        P1[i] = cal_time(P_IDX.at(i).first, x1, P_IDX.at(i).second, y1);
        P2[i] = cal_time(P_IDX.at(i).first, x2, P_IDX.at(i).second, y2);
    }
}

int timer(vector<int> unsortedA, int kk){
    // TODO: note this!

    std::sort(unsortedA.begin(), unsortedA.end());
    
    vector<int> goalA;
    for(int i=0; i<unsortedA.size(); i++){
        goalA.push_back(unsortedA.at(i)+kk); // TODO: to change with p1 & p2
    }

    vector<int> Kstacks; // K개씩 계단에 사람 삽입하며 계산하는 스택. 스택에는 해당 원소의 인덱스 가짐.
    int timer = 0; // 1씩 증가하는 타이머
    int done = 0; // 현재까지 계단 밑으로 내려간 사람 수
    int inside = 0; // 현재까지 계단 안에 들어간 사람 수
    int ans = 0;

    while(done < unsortedA.size()){
        // 1. Goal에 도달한 원소들 스택에서 제거
        for(int i=0; i<Kstacks.size(); i++){
            assert(unsortedA.size() > Kstacks.at(i) || goalA.size() > Kstacks.at(i));
            if(unsortedA.at(Kstacks.at(i)) >= goalA.at(Kstacks.at(i))) {
                Kstacks.erase(Kstacks.begin() + i);
                i--; // TODO: remark this!
                done++; // 내려온 사람 한명 증가
                if (done >= unsortedA.size()) ans = timer;
            }
        }

        // 2. 스택이 비어있을 경우, 대기하는 원소 스택에 삽입
        if(Kstacks.size() < kk && inside < unsortedA.size()){
            assert(unsortedA.size() > inside);
            if(unsortedA.at(inside) <= timer) {
                Kstacks.push_back(inside);
                inside++; // 내부자 증가증가
                continue;
                // * 동시에 들어온 원소도 다 넣을때까지 타이머 증가 안시키고 반복
            }
        }

        if(done >= unsortedA.size() && Kstacks.size() == 0) break;

        // 3. 타이머 증가, 스택 내 원소들의 값 증가
        for(int i=0; i<Kstacks.size(); i++){
            assert(unsortedA.size() > Kstacks.at(i) || goalA.size() > Kstacks.at(i) || false);
            unsortedA.at(Kstacks.at(i))++;
        }
        
        timer++; // 하나의 루프 마다 타이머 1 증가
    }

    // 마지막에 timer의 값이 Goal에 모두 도달하였을 때의 최종 시간 값이 된다.

    return timer;

}

int minInt(int a, int b){
    if(a <= 0) return b;
    else if(b <= 0) return a;
    else return a < b ? a : b;
}

int maxInt(int a, int b){
    if(a <= 0) return b;
    else if(b <= 0) return a;
    else return a > b ? a : b;
}

void print_p(){
    for(int i=0; i<P_IDX.size(); i++){
        cout << P[i] << " ";
    }
    cout << endl;
}

void dfs(int cnt){

    // base case
    //assert(cnt < P_IDX.size());
    if(cnt >= P_IDX.size()){
        //return timer() 호출해서 계산한 값의 최대.

        vector<int> P1vec;
        vector<int> P2vec;

        for(int i=0; i<P_IDX.size(); i++){
            if(P[i]) P2vec.push_back(P2[i]);
            else P1vec.push_back(P1[i]);
        }

        //cout << P1vec.size() << P2vec.size() << endl;

        //cout << timer(P1vec, k1) << " " << timer(P2vec, k2) << endl;

        //cout << minT << endl;

        //print_p();

        int min = maxInt(timer(P1vec, k1), timer(P2vec, k2));
        /* if(!P1vec.empty() && !P1vec.empty()) min = maxInt(timer(P1vec, k1), timer(P2vec, k2));
        else if(P1vec.empty()) min = timer(P2vec, k2);
        else if(P2vec.empty()) min = timer(P1vec, k2);
        else { 
            min = __INT_MAX__;
        } */
        
        minT = minInt(min, minT);

        return;

    }

    P[cnt] = false;
    dfs(cnt+1);
    P[cnt] = true; 
    dfs(cnt+1);

}

void start_alg(){

    pre_calculate(); // 미리 P1, P2 계산하고

    dfs(0); // DFS로 경로 찾아서 가장 최소의 시간 찾기

    cout << minT << endl;

}

void test_print(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << "stair#1 " << x1 << " " << y1 << " " << k1 << endl;
    cout << "stair#2 " << x2 << " " << y2 << " " << k2 << endl;
    cout << "people# " << P_IDX.size() << endl;
    cout << "P1 ";
    for(int i=0; i<P_IDX.size(); i++) cout << P1[i] << " ";
    cout << "\nP2 ";
    for(int i=0; i<P_IDX.size(); i++) cout << P2[i] << " ";
    cout << "\n";
}

void read_file(string fileName){
    ifstream iFile(fileName.c_str());
    iFile >> T;
    for(int i=0; i<T; i++){
        iFile >> N;
        bool fnd1 = false;
        P_IDX.clear();
        for(int j=0; j<N; j++){
            for(int k=0; k<N; k++){
                iFile >> map[j][k];
                if(map[j][k] >= 2){
                    if(!fnd1){
                        x1 = j;
                        y1 = k;
                        k1 = map[j][k];
                        fnd1 = true;
                    }
                    else{
                        x2 = j;
                        y2 = k;
                        k2 = map[j][k];
                    }
                } else if(map[j][k] == 1){
                    P_IDX.push_back(pair<int, int>(j, k));
                }
            }
        }
        start_alg();
    }
}

int main(int argc, char **argv){

    if(argc < 2){
        cerr << "Usage : ./a.out INPUTFILE" << endl;
        return 1;
    }

    read_file(argv[1]);

    return 0;

}