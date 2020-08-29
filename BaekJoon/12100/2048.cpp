#include <iostream>
#include <climits>
#include <vector>
using namespace std;
// 1. 같은 수의 이동은 횡이나 축으로 이동할 때 병합됨
// 2. 한번의 이동에서는 한번의 병합만 이루어짐
// 3. 도형이 3개일 경우 병합의 우선순위는 해당 방향에 가까운 쪽부터
// 4. 최대 다섯번 이동해서 나올 수 있는 가장 큰 수 구하기

int arr[20][20] = {0, };
int N;
int bigNum = INT_MIN;
vector<string> moveCmb;

// 1. 먼저 dfs로 이동 조합을 모두 구함
// 2. 구해진 해당 이동 조합으로 도형 이동 시뮬레이션
// 3. 가장 큰 수를 업데이트

int get_big(int a, int b){
  return a > b ? a : b;
}

// 0:→ 1:← 2:↑ 3:↓
void dfs(int idx, string cmb){
  if (idx == 5) moveCmb.push_back(cmb);
  else {
    dfs(idx+1, cmb+"0");
    dfs(idx+1, cmb+"1");
    dfs(idx+1, cmb+"2");
    dfs(idx+1, cmb+"3");
  }
}

void move_row(vector<int> &vec, bool front){
  // 앞쪽으로 붙일거면 front = true, 뒤쪽으로 붙일거면 front = false
  vector<int> newRow, tmpRow;
  if(front){ // O O x x x x
    for (int i = 0; i < vec.size(); i++){
      if(vec[i] != 0) newRow.push_back(vec[i]);
    }
  } else {
    for (int i = vec.size()-1; i >= 0; i--){
      if(vec[i] != 0) newRow.push_back(vec[i]);
    }
  }

  if(newRow.size() == 1) tmpRow.push_back(newRow[0]);
  else {
    for (int k = 0; k < newRow.size(); k++) {
      // 1. N == N+1이면 newRow에 Nx2값 푸쉬하고 k+=2
      // 2. N != N+1이면 newRow에 N 푸쉬하고 k++
      //    ㄴ k == newRow.size()-2이면 N+1도 푸쉬함
      if(k == newRow.size()-1){
        tmpRow.push_back(newRow[k]);
      } else if(newRow[k] == newRow[k+1]) {
        tmpRow.push_back(newRow[k] * 2);
        k++;
      } else {
        tmpRow.push_back(newRow[k]);
      }
    }
  }

  for (int i = 0; i < vec.size(); i++) {
    if(front){
      if(i < tmpRow.size()) vec[i] = tmpRow[i];
      else vec[i] = 0;
    } else {
      if(i < tmpRow.size()) vec[vec.size()-1-i] = tmpRow[i];
      else vec[vec.size()-1-i] = 0;
    }
  }
}

void simulate_game(string cmb){
  vector< vector<int> > board;
  for (int i = 0; i < N; i++) {
    vector<int> tmp;
    for (int j = 0; j < N; j++) {
      tmp.push_back(arr[i][j]);
    }
    board.push_back(tmp);
    tmp.clear();
  }

  for (int i = 0; i < cmb.size(); i++) {
    if(cmb[i] == '0'){
      for (int j = 0; j < N; j++) move_row(board[j], false);
    } else if(cmb[i] == '1'){
      for (int j = 0; j < N; j++) move_row(board[j], true);
    } else if(cmb[i] == '2'){
      for (int j = 0; j < N; j++){
        vector<int> colVec;
        for (int k = 0; k < N; k++) colVec.push_back(board[k][j]);
        move_row(colVec, true);
        for (int k = 0; k < N; k++) board[k][j] = colVec[k];
      }
    } else if(cmb[i] == '3'){
      for (int j = 0; j < N; j++){
        vector<int> colVec;
        for (int k = 0; k < N; k++) colVec.push_back(board[k][j]);
        move_row(colVec, false);
        for (int k = 0; k < N; k++) board[k][j] = colVec[k];
      }
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      bigNum = get_big(bigNum, board[i][j]);
    }
  }
}

int main(){
  cin >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> arr[i][j];
    }
  }

  dfs(0, "");
  for(auto s:moveCmb) simulate_game(s);
  cout << bigNum << endl;

  return 0;
}
