#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int D, W; // 보호필름의 두께와 너비
int K; // 보호필름의 합격기준
bool film[13][20]; // 보호필름의 특성 (0:A, 1:B)
bool tmpFilm[13][20];
int minCnt = INT_MAX; // 최소약품투입횟수
bool visit[13];

bool chk_vec(vector<bool> &v){
    // 하나의 보호필름 열 검사. K개만큼 특성 같으면 true
    bool prev, cur;
    int cnt = 1;
    
    //for(auto vv:v) cout << vv << ' ';
    //cout << endl;

    for(int i=1; i<v.size(); i++){
        if(cnt >= K) return true;
        prev = v[i-1];
        cur = v[i];

        if(prev==cur) cnt++;
        else cnt = 1;  
    }

    return (cnt >= K);
}

bool chk_film(){
    // 보호필름의 합격기준 검사. K개 이상 세로 셀들이 동일한 특성가질때 합격
    for(int i=0; i<W; i++){
        vector<bool> tmpVec;
        for(int j=0; j<D; j++){
            tmpVec.push_back(tmpFilm[j][i]);
        }
        if(!chk_vec(tmpVec)) return false;
    }

    return true;
}

int min_val(int a, int b){
    return a < b ? a : b;
}

void inject_film(int idx){
    // 보호필름에 약품 주입해서 특성맞추기, 중간에 맞추어지는 특성 발견시 해당 투입횟수 반환후 종료

    /* if(chk_film()) {
        minCnt = min_val(minCnt, idx);
    } */

    if(idx == D){
        // base case
        return;
    }

    for(int i=0; i<D; i++){
        if(!visit[i]){
            for(int j=0; j<W; j++) tmpFilm[i][j] = 0;
            if(chk_film()) {
                minCnt = min_val(minCnt, idx+1);
                return;
            }
            for(int j=0; j<W; j++) tmpFilm[i][j] = 1;
            if(chk_film()) {
                minCnt = min_val(minCnt, idx+1);
                return;
            }
            for(int j=0; j<W; j++) tmpFilm[i][j] = film[i][j];
        } // 방문되지 않았을 때, 해당 행 변환후 검사하고 넘기기
    }

    for(int i=0; i<D; i++){
        if(!visit[i]){
            visit[i] = true;
            for(int j=0; j<W; j++) tmpFilm[i][j] = 0;
            inject_film(idx+1);
            for(int j=0; j<W; j++) tmpFilm[i][j] = 1;
            inject_film(idx+1);
            for(int j=0; j<W; j++) tmpFilm[i][j] = film[i][j];
            visit[i] = false;
        } // 방문되지 않았을 때, 해당 행 변환후 검사하고 넘기기
    }

    /* for(int i=0; i<D; i++){
        if(!visit[i]){
            visit[i] = true;
            for(int j=0; j<W; j++) tmpFilm[i][j] = 0;
            inject_film(idx+1);
            for(int j=0; j<W; j++) tmpFilm[i][j] = 1;
            inject_film(idx+1);
            for(int j=0; j<W; j++) tmpFilm[i][j] = film[i][j];
            visit[i] = false;
        } // 방문되지 않았을 때, 해당 행 변환후 검사하고 넘기기
    } */

}

int main(){

    // unit test
    /* K=3;
    vector<bool> v = {1,1,0,0,1,1,0};
    cout << chk_vec(v) << endl; */

    int T;
    cin >> T;

    for(int i=0; i<T; i++){
        cin >> D >> W >> K;
        for(int j=0; j<D; j++){
            for(int k=0; k<W; k++){
                cin >> film[j][k];
                tmpFilm[j][k] = film[j][k];
            }
        }
        if(chk_film()) minCnt = 0;
        inject_film(0);
    }

    cout << minCnt << endl;

    return 0;
}