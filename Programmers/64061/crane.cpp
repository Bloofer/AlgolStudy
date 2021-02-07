#include <iostream>
#include <vector>
using namespace std;

vector<int> basket;
int ans = 0;
int N;

int get_item(vector<vector<int>> &board, int col){
// 열 번호를 받아 해당 열의 가장 윗칸의 인형을 반환하고 해당 칸을 비움, 없으면 -1 반환
  int top = -1;
  for (int i = 0; i < N; i++) {
    if(board[i][col] == 0) continue;
    else {
      top = board[i][col];
      board[i][col] = 0;
      return top;
    }
  }
  return top;
}

int solution(vector<vector<int>> board, vector<int> moves) {
    N = board.size();
    for(auto m:moves){
      int i = get_item(board, m-1); // 크레인의 위치에서의 인형을 찾고, 보드를 업데이트
      if(i == -1) continue;
      else if(!basket.empty()){
        if(basket.back() == i) { basket.pop_back(); ans += 2; }
        // 바구니가 비어있지 않으면서, 새로 뽑은 인형과 바구니 맨 위 인형이 같으면 POP
        else basket.push_back(i);
      } else{
        basket.push_back(i);
        // 그 외의 경우는 바구니에 뽑은 인형을 넣음
      }
    }

    return ans;
}

int main(){
  vector<vector<int>> board = {{0,0,0,0,0},{0,0,1,0,3},{0,2,5,0,1},{4,2,4,4,2},{3,5,1,3,1}}	;
  vector<int> moves = {1,5,3,5,1,2,1,4};

  cout << solution(board, moves) << endl;

  return 0;
}
