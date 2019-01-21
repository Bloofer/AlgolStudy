#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool cmp(vector<int> &v1, vector<int> &v2){
    // 정렬 비교함수. 스트라이크, 볼 많은 것 기준
    if(v1.at(1) > v2.at(1)) return true;
    else if(v1.at(1) < v2.at(1)) return false;
    else {
        if(v1.at(2) > v2.at(2)) return true;
        else if(v1.at(2) < v2.at(2)) return false;
    }
    return true;
}

bool cmp_str(string &s1, string &s2){
    return stoi(s1) < stoi(s2);
}

static int to_char(int value)
 {
    return '0' + value;
 }

vector<string> make_comb(){
    // 세자리 숫자 조합을 만드는 함수. 중복 된 숫자 사용 X
    vector<string> comb;
    for(int i=123; i<1000; i++){
        string tmp = to_string(i);
        if(tmp.at(0) == tmp.at(1) || tmp.at(0) == tmp.at(2) || tmp.at(1) == tmp.at(2)) continue;
        if(tmp.at(0) == '0' || tmp.at(1) == '0' || tmp.at(2) == '0') continue;
        comb.push_back(tmp);
    }
    return comb;
}

bool has_num(string &s, char &c){
    // 스트링 s가 문자 c를 가졌는지 확인하는 함수
    return (s.find(c) != string::npos);
}

int cnt_strike(string &s, string &condS){
    // 스트라이크 수를 계수
    int cnt = 0;
    for(int i=0; i<3; i++){
        if(s.at(i) == condS.at(i)) cnt++;
    }
    return cnt;
}

int cnt_ball(string &s, string &condS){
    // 볼 수를 계수. 스트라이크는 제외
    int cnt = 0;
    for(int i=0; i<3; i++) {
        if(has_num(s, condS.at(i)) && s.at(i) != condS.at(i)) cnt++;
    }
    return cnt;    
}

bool check_cond(string &s, vector<int> &cond){
// 해당 숫자 조합이 질문 조건에 맞는지 확인. 맞으면 true, 아니면 false
    string condS = to_string(cond.front());
    if((cond.at(1) == cnt_strike(s, condS)) && (cond.at(2) == cnt_ball(s, condS))) return true;
    else return false;
}

int solution(vector<vector<int>> baseball) {
    // 조건 순으로 질문 정렬
    sort(baseball.begin(), baseball.end(), cmp);

    // 가능한 조합 만들기
    vector<string> v = make_comb();

    // 질문 리스트 iter하면서 불가능한 조합 빼기
    for(int i=0; i<baseball.size(); i++){
        vector<string> newV;
        for(int j=0; j<v.size(); j++){
            if(check_cond(v.at(j), baseball.at(i))) newV.push_back(v.at(j));
        }
        v = newV;
    }
    
    int answer = v.size();
    return answer;
}

int main(){return 0;}