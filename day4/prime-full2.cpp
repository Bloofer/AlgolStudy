#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> nums;
bool idxBool[7] = {0,0,0,0,0,0,0}; // 0부터 9까지 숫자 조합을 만들때 중복을 피하기 위해 사용하는 배열

void comb_nums(string numbers, int i, string new_str){
    // 주어진 숫자 종이 조각을 중복되지 않게 조합으로 생성하는 재귀함수

    if(i == numbers.size()) { // 베이스 케이스
        nums.push_back(stoi(new_str));
        return;
    }
    
    for(int p=0; p<numbers.size(); p++){
        if(i == 0 && numbers.at(p) == '0') continue; // 맨 앞 문자는 0이 될 수 없음
        if(!idxBool[p]) {
            // 재귀 호출부분. idxBool을 체크하며 선택되지 않은 숫자 종이를 선택하여 스트링에 이어붙이고 DFS로 스트링을 만들어 나간다.
            idxBool[p] = true;
            if(new_str != "") nums.push_back(stoi(new_str));
            comb_nums(numbers, i+1, new_str+numbers.at(p));
            idxBool[p] = false;
        }
    }
}

bool is_prime(int n) {
    // 소수 판별 함수
    if( n <= 1 ) return false; // 1은 소수 X
         
    if( n == 2) return true; // 2는 소수지만, 2의 배수는 소수 X
    else if( (n % 2) == 0 ) return false;
        
    for(int i=3; i*i<=n; i+=2) { // 3부터 root(n)까지의 홀수 체크
        if( n % i == 0) {
            return false; // i가 n의 약수라면 소수 X
        }
    }

    return true; // 이 조건에 모두 걸리지 않으면 소수
}

int solution(string numbers) {
    // 먼저 입력으로 받은 숫자 스트링으로 숫자 조합을 만든다.
    comb_nums(numbers, 0, "");
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());

    // 만든 숫자 조합내 소수 판정
    int answer = 0;
    for(int i=0; i<nums.size(); i++){
        if(is_prime(nums.at(i))) answer++;
    }
    return answer;
}

int main(){return 0;}