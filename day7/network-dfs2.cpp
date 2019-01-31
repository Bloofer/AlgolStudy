#include <string>
#include <vector>

using namespace std;

bool chk[200];              // 네트워크에 소속된 컴퓨터 체크
int cnt = 0;                // 네트워크 수
vector<vector<int>> coms;   // 컴퓨터 네트웍 배열

void dfs(int cur){
// cur : 현재 탐사중인 컴퓨터    
    if(chk[cur]) return;    // 중복 탐사 피하기 위해, 탐사된 지역이면 종료
    chk[cur] = true;        // 탐사 안된 지역이면 체크한다.

    // 본인 컴퓨터를 뺀 인접 컴퓨터와 네트웍이 연결되었는지 확인, 연결되어 있으면 따라가 탐사한다.(DFS)
    for(int i=0; i<coms.size(); i++){ 
        if(i == cur) continue;
        if(coms[cur][i]) {
            dfs(i);
        }
    }
}

int solution(int n, vector<vector<int>> computers) {
    coms = computers;
    int answer = 0;
    // 모든 컴퓨터 네트웍 돌면서 탐사하고, 탐사 중 네트워크로 연결 된 지점은 따로 탐사하지 않는다.
    for(int i=0; i<coms.size(); i++){
        if(!chk[i]) {
            answer++;
            dfs(i);
        }
    }
    
    return answer;
}