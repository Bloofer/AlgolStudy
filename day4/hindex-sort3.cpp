#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool cmp(int a, int b) { return (a>b); }

int solution(vector<int> citations) {
    // 논문 인용수 벡터 내림차순으로 정렬
    sort(citations.begin(), citations.end(), cmp);

    int answer = 0;
    for(int i=0; i<citations.size(); i++){
        // h-인덱스는 h번 이상 인용된 논문이 h편 이상이 되는 값이므로
        // 큰 수부터 내림차순으로 정렬된 인용횟수와 인덱스(논문편수)를 비교하여 조건이 깨질때 바로 이전이 h-인덱스가 됨
        if((i+1)<=citations.at(i)) {
            answer = i+1;
        } else break;
    }
    return answer;
}

int main(){return 0;}