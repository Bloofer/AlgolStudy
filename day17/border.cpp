#include <iostream>
#include <queue>
using namespace std;

int N, L, R;
int A[50][50];
bool updown[49][50];
bool leftright[50][49]; // 상하좌우 국경선의 열려있는 상태를 표시

bool chk_cond(int a, int b){
    return ((abs(a-b) >= L) && (abs(a-b) <= R));
}

bool chk_possible(){
    bool possible = true;

    // 위 아래 국경 확인
    for(int i=0; i<N-1; i++){
        for(int j=0; j<N; j++){
            updown[i][j] = chk_cond(A[i][j], A[i+1][j]);
            possible &= updown[i][j];
        }    
    }

    // 좌 우 국경 확인
    for(int i=0; i<N; i++){
        for(int j=0; j<N-1; j++){
            leftright[i][j] = chk_cond(A[i][j], A[i][j+1]);
            possible &= leftright[i][j];
        }    
    }

    return possible;
}

void cal_union(){
    queue< pair<int, int> > unionQ;
    bool visit[N][N];  // 연합 계산시 중복 연산 방지용 visit 배열
    bool unions[N][N]; // bfs 탐사시 해당 연합에 해당하는 국가 체크용 배열

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(visit[i][j]) continue; // 이미 계산한 지역이면 넘김
            
            visit[i][j] = true;
            unionQ.push(pair<int, int>(i, j));
            while(!unionQ.empty()){
                pair<int, int> unionIdx = unionQ.front();
                unionQ.pop();
                //if(unionIdx.first < N-1) TODO: 여기서 상하좌우 링크 확인하며 bfs 탐사하고 
                // 탐사 가능한 지역 sum 묶어서 계산한뒤 분배하는 함수 마저 짜기.

            }

        }
    }

}

int migrate(){
    int n = 0;

    bool possible = chk_possible(); // 이주가 가능한지 검사하는 변수
    while(possible){
        n++;



        possible = chk_possible();
    }

    return n;
}

int main(){
    cin >> N >> L >> R;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> A[i][j];
        }
    }

    cout << migrate() << endl;

    return 0;
}