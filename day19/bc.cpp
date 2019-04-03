#include <iostream>
#include <vector>
using namespace std;

int T; // 테스트케이스 수
int M, A; // 총 이동시간(M), BC의 개수(A)
int moves[2][100]; // 두 사람의 이동동선
bool bcs[8][10][10]; // 각 BC들의 영향범위지도
int performs[8]; // 각 BC들의 충전량

int max_val(int a, int b){
    return a > b ? a : b;
}

// TODO: 이동방향 조심
void move(int &x, int &y, int dir){
    // 이동 방향에 따라 사람좌표 이동
    if(dir == 0) return;
    else if (dir == 1) x--;
    else if (dir == 2) y++;
    else if (dir == 3) x++;
    else if (dir == 4) y--;
}

int charge(int x1, int y1, int x2, int y2){
    // 해당 순간의 사람좌표를 받아, 가능한 배터리 충전량중 최대를 반환하는 함수
    int sum = 0;
    vector<int> v1, v2;

    for(int i=0; i<A; i++){
        if(bcs[i][x1][y1]) v1.push_back(i);
        if(bcs[i][x2][y2]) v2.push_back(i);
    }

    if(v1.empty() && v2.empty()) return sum;
    else if(!v1.empty() && v2.empty()){
        // v1이 비어있지 않은 경우
        for(auto vv:v1) sum = max_val(sum, performs[vv]);
    } else if(v1.empty() && !v2.empty()){
        // v2가 비어있지 않은 경우
        for(auto vv:v2) sum = max_val(sum, performs[vv]);
    } else {
        // 둘다 비어있지 않은 경우
        for(auto vv1:v1){
            for(auto vv2:v2){
                if(vv1==vv2) sum = max_val(sum, performs[vv1]);
                else sum = max_val(sum, performs[vv1]+performs[vv2]);
            }
        }
    }
    return sum;
}

int func_d(int xa, int ya, int xb, int yb){
    // BC로부터의 영향거리 구할때 사용하는 함수
    return abs(xa-xb) + abs(ya-yb);
}

void init_bc(int x, int y, int c, int idx){
    // 해당 인덱스의 BC지도에 좌표와 충전범위 정보를 받아 그리는 함수
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            if(func_d(y,x,j,i)<=c) bcs[idx][j][i] = true; // 가용범위 안에 들어오는 셀만 체크
            else bcs[idx][j][i] = false;
        }
    }
}

int main(){
    cin >> T;
    for(int i=0; i<T; i++){
        cin >> M >> A;
        for(int j=0; j<M; j++) cin >> moves[0][j];
        for(int j=0; j<M; j++) cin >> moves[1][j];
        for(int j=0; j<A; j++){
            int a, b, c, p;
            cin >> a >> b >> c >> p;
            init_bc(a-1,b-1,c,j);
            performs[j]=p;
        }
    
        int x1 = 0;
        int y1 = 0;
        int x2 = 9;
        int y2 = 9; // 두 사람의 초기지정좌표
        int sum = 0; // 두 사람의 배터리충전량 합

        sum += charge(x1,y1,x2,y2);
        for(int j=0; j<M; j++){
            // 사람이동
            move(x1, y1, moves[0][j]);
            move(x2, y2, moves[1][j]);
            // 배터리 최대충전량 적용하기
            int cg = charge(x1,y1,x2,y2);
            sum += cg;
        }
        cout << "#" << i+1 << " " << sum << endl;
    }

    return 0;
}