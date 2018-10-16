#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int t, n, m, c;
int map[10][10]; // 벌꿀 지도
int d[10][10]; // 꿀통으로 모을 수 있는 벌꿀 최대값 지도

// 각각 벌통에 대해 올 수 있는 최댓값을 저장시킨 후 m개 씩 2개 골라 최대값 찾기

// 최대값 계산하기
int calc(vector<int> &v, int n, int sum, int val){
    if(sum > c) return 0; // c보다 큰 값은 꿀통에 못넣음
    if(n == v.size()) return val; // 가능한 인접 꿀통 탐색 완료시

    return max(calc(v, n+1, sum+v[n], val+v[n]*v[n]), calc(v, n+1, sum, val));
}

// 최대값 찾기
int getMaxPrice(int x, int y){
    vector<int> v;
    for(int i=0; i<m; i++){ // m은 벌꿀을 담을 꿀통의 범위
        v.push_back(map[x][y+i]);
    }
    return calc(v,0,0,0);
}

int dfs(int x, int y){
    // 꿀통 하나를 잡고, 이윤이 최대가 되는 다른 꿀통을 찾기 위해 지도 전체를 DFS로 탐사
    int ans = 0;
    // 같은 라인
    for(int i=y+m; i<n-m+1; i++){
        ans = max(ans, d[x][i]);
    }
    // 다른 라인
    for(int i=x+1; i<n; i++){
        for(int j=0; j<n; j++){
            ans = max(ans, d[i][j]);
        }
    }
    return ans;
}

int main(){
    cin >> t;
    for(int tc = 1; tc<= t; ++tc){
        cin >> n >> m >> c;
        for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) d[i][j] = 0;
        for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) cin >> map[i][j];

        // d배열에 그칸부터 m칸까지의 최대값 저장
        for(int i=0; i<n; i++){
            for(int j=0; j<n-m+1; j++){
                d[i][j] = getMaxPrice(i, j);
            }
        }

        // i,j를 선택한 상태에서 찾을 수 있는 나머지 벌꿀통 하나를 비교하며 최대값 찾는다.
        int res = 0;
        for(int i=0; i<n; i++){
            for(int j=0; j<n-m+1; j++){
                res = max(res, dfs(i,j)+d[i][j]);
            }
        }
        cout << "#" << tc << " " << res << endl;
    }
}