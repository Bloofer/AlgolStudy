#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(vector<int> v1, vector<int> v2){
    return v1[1] < v2[1];
}

int solution(vector<vector<int>> routes) {

    sort(routes.begin(), routes.end(), cmp);
    // 경로의 오른쪽을 기준으로 오름차순 정렬

    int answer = 1;
    int lastCam = routes[0][1];
    for(int i=1; i<routes.size(); i++){
        if(lastCam < routes[i][0]) {
            answer++;
            lastCam = routes[i][1];
        }
    }
    return answer;
}

int main(){
    return 0;
}