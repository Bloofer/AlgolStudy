#include <string>
#include <vector>
using namespace std;

int cnt = 0;        // 숫자들과 연산자로 만들 수 있는 조합 갯수
vector<int> nums;   // 숫자 인풋
int tgt;            // 타켓 인풋

void make_comb(int i, int sum){
    // Base Case
    if(i == nums.size()) {
        if(sum == tgt) cnt++;    
        return;
    }

    // Recursive Case
    make_comb(i+1, sum+nums[i]);
    make_comb(i+1, sum-nums[i]);
}

int solution(vector<int> numbers, int target) {
    nums = numbers;
    tgt = target;
    make_comb(0, 0);

    return cnt;
}