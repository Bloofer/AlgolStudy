#include <iostream>
#include <climits>
using namespace std;

int N;
int jobs[2][15];
int maxVal = INT_MIN;

int max_val(int a, int b){
    return a > b ? a : b;
}

void dfs(int idx, int sum){
    if(idx >= N) {
        maxVal = max_val(maxVal, sum);
        return;
    }
    for(int i=idx; i<N; i++) dfs(i+jobs[0][i], sum+jobs[1][i]);
}

int main(){
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> jobs[0][i] >> jobs[1][i];
        if(jobs[0][i] + i > N) jobs[1][i] = 0; // 작업 종료 기간이 퇴사이후면 못하는 작업
    }
    dfs(0, 0);
    cout << maxVal << endl;

    return 0;
}