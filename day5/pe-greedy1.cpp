#include <string>
#include <vector>

using namespace std;

typedef struct{
    bool hasUni; // 유니폼 가지고 있는지 여부
    bool hasRsv; // 유니폼 여분 있는지 여부
} Uni;

int solution(int n, vector<int> lost, vector<int> reserve) {
    vector<Uni> uniVec;
    for(int i=0; i<n; i++){
        Uni tmp;
        tmp.hasUni = true;
        tmp.hasRsv = false;
        uniVec.push_back(tmp);
    }

    // 여분 가져온 사람 체크
    for(int i=0; i<reserve.size(); i++) {
        uniVec[reserve[i]-1].hasRsv = true;
    }

    // 도둑맞으면 여분도 잃어버림
    for(int i=0; i<lost.size(); i++) {
        uniVec[lost[i]-1].hasUni = false;
        uniVec[lost[i]-1].hasRsv = false;
    }

    


    int answer = 0;
    return answer;
}