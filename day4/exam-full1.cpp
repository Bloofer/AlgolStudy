#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> fst = {1,2,3,4,5};
    vector<int> snd = {2,1,2,3,2,4,2,5};
    vector<int> thd = {3,3,1,1,2,2,4,4,5,5}; // 3명의 수포자가 각각 문제를 찍는 패턴

    vector<int> cnt = {0,0,0};
    for(int i=0; i<answers.size(); i++){
        // 각각의 수포자의 패턴을 패턴 길이 만큼 반복시켜 비교한다.
        if(answers.at(i) == fst.at(i%5)) cnt.at(0)++;
        if(answers.at(i) == snd.at(i%8)) cnt.at(1)++;
        if(answers.at(i) == thd.at(i%10)) cnt.at(2)++; 
    }

    int big = cnt.front();
    vector<int> answer;
    answer.push_back(1);
    // 가장 높은 점수를 받은 학생일 경우 구함. 중복 고려
    for(int i=1; i<cnt.size(); i++){
        if(cnt.at(i) > big) {
            answer.clear();
            big = cnt.at(i);
            answer.push_back(i+1);
        }
        else if(cnt.at(i) == big) answer.push_back(i+1);
    }

    return answer;
}