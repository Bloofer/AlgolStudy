#include <iostream>
#include <string>
#include <climits>
using namespace std;

int N;
int nums[11];
int ops[4];
int cnt[4];
int maxVal = INT_MIN;
int minVal = INT_MAX;
// { + - x % }

int get_min(int a, int b){ return a < b ? a : b; }
int get_max(int a, int b){ return a > b ? a : b; }

void eval_expr(string cmb){
  int sum = nums[0];
  for (int i = 0; i < N - 1; i++) {
    if(cmb[i] == '0') sum += nums[i + 1];
    else if(cmb[i] == '1') sum -= nums[i + 1];
    else if(cmb[i] == '2') sum *= nums[i + 1];
    else if(cmb[i] == '3') sum /= nums[i + 1];
  }
  maxVal = get_max(maxVal, sum);
  minVal = get_min(minVal, sum);
}

void dfs(int idx, string cmb){
  if(idx == N-1){
    eval_expr(cmb);
    return; // base case
  } else {
    if (cnt[0] < ops[0]) { cnt[0]++; dfs(idx+1, cmb+'0'); cnt[0]--; }
    if (cnt[1] < ops[1]) { cnt[1]++; dfs(idx+1, cmb+'1'); cnt[1]--; }
    if (cnt[2] < ops[2]) { cnt[2]++; dfs(idx+1, cmb+'2'); cnt[2]--; }
    if (cnt[3] < ops[3]) { cnt[3]++; dfs(idx+1, cmb+'3'); cnt[3]--; }
  }
}

// 1. 연산자 배열 선정(DFS)
// 2. 연산자에 맞추어 연산식 계신
int main(){
  cin >> N;
  for (int i = 0; i < N; i++) cin >> nums[i];
  for (int i = 0; i < 4; i++) cin >> ops[i];
  dfs(0, "");

  cout << maxVal << endl << minVal;
  return 0;
}
