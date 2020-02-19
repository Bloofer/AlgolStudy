#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int N, K;
int dir[11]; // →:1, ←:2, ↑:3, ↓:4
int board[12][12]; // 0:흰, 1:빨, 2:파
int exitTurn = -1; // 말 4개가 쌓이는 종료턴
bool exitCond = false; // 말 4개가 쌓이는 종료조건

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

pair<int, int> piece[10]; // 말들의 좌표 벡터
vector<int> cell[20][20]; // 각각의 셀 안에 쌓이는 말정보 저장

bool check_next(int i) {
	int r = piece[i].first;
	int c = piece[i].second;

	if (dir[i] == 1) { if (c + 1 >= N || board[r][c + 1] == 2) return false; }
	else if (dir[i] == 2) { if (c - 1 < 0 || board[r][c - 1] == 2) return false; }
	else if (dir[i] == 3) { if (r - 1 < 0 || board[r -1][c] == 2) return false; }
	else if (dir[i] == 4) { if (r + 1 >= N || board[r + 1][c] == 2) return false; }

	return true;
}

int flip_dir(int d) {
	if (d == 1) return 2;
	else if (d == 2) return 1;
	else if (d == 3) return 4;
	else if (d == 4) return 3;
	return 0;
}

void move_piece(int i) {
	int r = piece[i].first;
	int c = piece[i].second;

	if (dir[i] == 1) { if (c + 1 >= N || board[r][c + 1] == 2) return; }
	else if (dir[i] == 2) { if (c - 1 < 0 || board[r][c - 1] == 2) return; }
	else if (dir[i] == 3) { if (r - 1 < 0 || board[r - 1][c] == 2) return; }
	else if (dir[i] == 4) { if (r + 1 >= N || board[r + 1][c] == 2) return; }

	int pos = 0;
	// 1. 해당 셀에서 말이 업힌 스택 위치 찾음
	for (int p = 0; p < cell[r][c].size(); p++) {
		if (cell[r][c].at(p) == i) {
			pos = p;
			break;
		}
	}
	// 2. 업힌 위치 뒤로의 벡터 다음 위치로 옮겨줌
	int rr = r + dx[dir[i] - 1];
	int cc = c + dy[dir[i] - 1];
	vector<int> tmp;
	for (int p = pos; p < cell[r][c].size(); p++) { 
		int pNum = cell[r][c].at(p);
		tmp.push_back(pNum);
	
		piece[pNum].first = rr;
		piece[pNum].second = cc;
	}

	// 3. 만약 다음 위치가 빨간색이면 말들의 업힌 순서를 뒤집고, 하얀색이면 그대로 둠
	// * 뒤집을 때의 로직, 기존에 있던 빨간색 셀 안의 말들은 그대로 두고 새로 들어온 스택의 말들만 뒤집어서 넣는다.
	// * 뒤집을 때의 조건을 셀 안의 전체 말을 뒤집는 것으로 하면 원하는 결과가 나오지 않음
	if (board[rr][cc] == 1) reverse(tmp.begin(), tmp.end());
	for (int i = 0; i < tmp.size(); i++) {
		cell[rr][cc].push_back(tmp.at(i));
	}
	
	if (cell[rr][cc].size() >= 4) exitCond = true;

	int siz = cell[r][c].size();
	for (int p = pos; p < siz; p++) cell[r][c].pop_back();
}

void run_turn() {
	// 하나의 턴 수행(k개의 말 이동)
	for (int i = 0; i < K; i++) {
		if (exitCond) break;

		// 1. i번째 말이 현재 위치에서 이동방향을 보고 이동 가능한지 확인
		if (!check_next(i)) dir[i] = flip_dir(dir[i]); // 이동불가하면 현재 위치 유지하며 방향 뒤집음
		
		// 2. 이동가능하면 현재 위치에서 업은 말들 포함하여 다음 위치로 이동
		//	  다음 위치에 있는 말들 위에 업힌다.
		move_piece(i);		
	}
}

int main() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}

	for (int i = 0; i < K; i++) {
		cin >> piece[i].first >> piece[i].second;
		piece[i].first--;
		piece[i].second--;
		cin >> dir[i];
		cell[piece[i].first][piece[i].second].push_back(i);
	}
	
	for (int i = 0; i < 1000; i++) {
		run_turn();

		if (exitCond) {
			exitTurn = i + 1;
			break;
		}
	}

	cout << exitTurn << endl;
	return 0;
}
