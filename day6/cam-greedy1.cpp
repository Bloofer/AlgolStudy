#include <string>
#include <vector>

using namespace std;

vector<vector<int>> get_overlapped(vector<vector<int>> routes){
    // routes 인자로 받아, 겹쳐진 경로(현재 위치에 있는 차량들)의 벡터
    vector<vector<int>> overlapVec[60000]; // 겹쳐진 경로들의 벡터
    // -30,000 ~ 30,000을 0 ~ 60,000로 매핑

    for(int i=0; i<routes.size(); i++){
        for(int j=routes.at(i).at(0); j<=routes.at(i).at(1); j++){
            // 차량의 진입지점부터 진출지점까지 마킹
            

        }
        
        
    }


}

int solution(vector<vector<int>> routes) {

    vector<vector<int>> overlapVec = get_overlapped(routes);

    int answer = 0;
    return answer;
}

int main(){
    return 0;
}