#include <string>
#include <vector>

using namespace std;

int maxSum = 0; // 경로의 합 중 최대값
vector<vector<int>> tri;

void find_max(int h, int idx, int sum){
    // 모든 행을 순회하며 정수삼각형내 모든 경로를 탐사하고,
    // 해당 경로 값의 합이 최대일 경우 업데이트 하는 함수

    // Base Case
    if(h == tri.size()){
        if(sum > maxSum) maxSum = sum;
        return;
    }

    // Recursive Case
    find_max(h+1, idx, sum+tri[h][idx]);
    find_max(h+1, idx+1, sum+tri[h][idx+1]);
}

int solution(vector<vector<int>> triangle) {

    tri = triangle;
    find_max(0, 0, 0);

    int answer = maxSum;
    return answer;
}