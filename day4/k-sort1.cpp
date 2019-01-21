#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<int> cut(vector<int> &arr, int a, int b){
// 배열 arr을 a부터 b까지 자른 것을 반환하는 함수
    vector<int> cutArr;
    for(int i=a-1; i<=b-1; i++) {
        cutArr.push_back(arr.at(i));
    }
    return cutArr;
}

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    for(int i=0; i<commands.size(); i++){
        vector<int> cutArr = cut(array, commands.at(i).at(0), commands.at(i).at(1));
        // i에서 j까지 자른 새로운 배열 만듦

        sort(cutArr.begin(), cutArr.end());
        answer.push_back(cutArr.at(commands.at(i).at(2) - 1));
        // 해당 배열 자른 후, k번째 크기의 배열 벡터에 삽입
    }
    return answer;
}

int main(){return 0;}