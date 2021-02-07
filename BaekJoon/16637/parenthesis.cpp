#include <iostream>
#include <string>
#include <climits>
using namespace std;

int N;
int ans = INT_MIN;
string s;

int cal(int x, int y, char op){
  if(op == '+') return x+y;
  else if(op == '*') return x*y;
  else if(op == '-') return x-y;
  else return x;
}

void dfs(int idx, int sum){
  // base case
  if(idx > N-1){
    if(sum > ans) ans = sum;
    return;
  }
  char op;
  if(idx == 0) op = '+';
  else op = s[idx-1];

  // recursive case
  // bind with bracket
  if(idx + 2 < N){
    int bracket = cal(s[idx]-'0', s[idx+2]-'0', s[idx+1]);
    dfs(idx+4, cal(sum, bracket, op));
  }
  // unbind with bracket
  dfs(idx+2, cal(sum, s[idx]-'0', op));
}

int main(){
  cin >> N;
  cin >> s;
  dfs(0,0);
  cout << ans << endl;

  return 0;
}
