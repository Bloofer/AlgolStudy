#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector< pair<int, int> > get_aliquot(int m){
    // 직사각형의 넓이 m을 받아서 가능한 x,y의 조합(약수)을 구하는 함수
    vector< pair<int, int> > pVec;

    for(int i=3; i<m/2; i++){
        if((m%i) == 0){
            // 약수인 경우
            pVec.push_back(pair<int, int>(m/i, i));
        }
    }
    return pVec;
}

vector<int> solution(int brown, int red) {
    vector< pair<int, int> > pVec = get_aliquot(brown+red);
    // 전체 넓이의 가로/세로 조합 구함

    vector<int> answer;
    for(int i=0; i<pVec.size(); i++) {
        int x = pVec.at(i).first;
        int y = pVec.at(i).second;
        // 구한 가로/세로 조합 중 가로-2 * 세로-2 가 빨간색 면적이 된다.(테두리를 뺀 직사각형)
        if( (x-2) * (y-2) == red ) {
            answer.push_back(x);
            answer.push_back(y);
            break;
        }
    }
    
    return answer;
}

int main(){return 0;}