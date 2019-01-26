#include <vector>
#include <map>
#include <iostream> 
using namespace std;

int solution(vector<vector<int>> board, vector<int> nums) {

    int n = board.size();
    bool visited[n][n]; // 체크되었는지 확인하는 n*n 배열을 만든다.
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) visited[i][j] = false; // visited 배열 초기화

    map<int, pair<int, int>> val2idxMap; // 엔트리 값 -> 인덱스 반환하는 맵

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // 각 보드에 입력된 숫자를 맵으로 옮김  
            val2idxMap.insert( map<int, pair<int, int>>::value_type(board[i][j], pair<int,int>(i,j)) );
        }
    }
    
    // nums에서 숫자 받은 지점 마킹하기
    for(int i=0; i<nums.size(); i++){
        pair<int,int> idx = val2idxMap[nums.at(i)];
        visited[idx.first][idx.second] = true;
    }

    int answer = 0;
    // 빙고 확인하기(가로줄)
    for(int i=0; i<n; i++) {
        bool chk = true;
        for(int j=0; j<n; j++){
            chk &= visited[i][j];
        }
        if(chk) answer++; // 가로줄 하나 모두 마킹되었으면 빙고!
    }

    // 빙고 확인하기(세로줄)
    for(int i=0; i<n; i++) {
        bool chk = true;
        for(int j=0; j<n; j++){
            chk &= visited[j][i];
        }
        if(chk) answer++; // 세로줄 하나 모두 마킹되었으면 빙고!
    }

    // 빙고 확인하기(대각선 좌측상단 -> 우측 하단)
    bool chk = true;
    for(int i=0; i<n; i++) {
        chk &= visited[i][i];        
    }
    if(chk) answer++; // 세로줄 하나 모두 마킹되었으면 빙고!

    // 빙고 확인하기(대각선 우측상단 -> 좌측 하단)
    bool chk2 = true;
    for(int i=0; i<n; i++) {
        /* for(int j=n-1; j>=0; j--){
            chk2 &= visited[i][j];
        } */
        chk2 &= visited[i][n-1-i];
    }
    if(chk2) answer++;  // 세로줄 하나 모두 마킹되었으면 빙고!
    
    return answer;
}