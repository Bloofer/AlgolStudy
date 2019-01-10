#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool solution(vector<string> phone_book) {
    sort(phone_book.begin(), phone_book.end());
    // 정렬 후

    bool answer = true;
    for(int i=0; i<phone_book.size()-1; i++){
        if(phone_book.at(i) == phone_book.at(i+1).substr(0, phone_book.at(i).size())) {
            // 인접 원소끼리 접두어 비교해서, 같으면 false 반환후 종료
            return false;
        }
    }
    return answer;
}

int main(){ return 0; }