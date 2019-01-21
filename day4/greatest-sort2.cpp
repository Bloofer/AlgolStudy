#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool str_cmp(string &a, string &b){
    // 스트링화 된 문자를 비교
    // ex) 30과 3040 비교시 303040과 304030을 만들어 두개를 비교함
    if(a == b) return false;

    string ab = a + b;
    string ba = b + a;
    if(ab > ba) return true;
    else return false;
}

string solution(vector<int> numbers) {
    // 일단 int 벡터를 string 벡터로 변환
    vector<string> sNums;
    for(int i=0; i<numbers.size(); i++) sNums.push_back(to_string(numbers.at(i)));

    // 그 후, 스트링 정렬 함수 호출
    sort(sNums.begin(), sNums.end(), str_cmp);
    
    // 마지막으로 정렬된 스트링 이어붙이면 최대의 수 만들어짐
    int zeros = 0;
    string answer = "";
    for(int i=0; i<sNums.size(); i++) {
        answer += sNums.at(i);
        if(sNums.at(i) == "0") zeros++;
    }

    // 0으로 쭉 이어진 경우 000...이 아니라 0 리턴
    if(zeros == sNums.size()) answer = "0";
    return answer;
}

int main(){return 0;}