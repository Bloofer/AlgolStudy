#include <string>
#include <vector>
#include <map>
using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    map<string, int> cMap;
    for(int i=0; i<completion.size(); i++){
        cMap[completion.at(i)]++;
    }

    string answer = "";
    for(int i=0; i<participant.size(); i++){
        if(cMap[participant.at(i)] > 0){
            // 맵이 비어있지 않다면, 감소시킴
            cMap[participant.at(i)]--;
        } else {
            // 비어있다면, 답을 찾은 것
            answer = participant.at(i);
            break;
        }
    }
    return answer;
}

//int main(){return 0;} // DUMMY for test compilation

// Map 사용하여, completion의 이름 계수 후, participant에서 하나씩 빼면서 남는 것 찾기
