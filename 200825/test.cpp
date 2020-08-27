#pragma GCC optimize ("Ofast")

#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING

#include <bits/stdc++.h>
using namespace std;


int board_green[10][4];
int board_blue[10][4];	// 문제에 써있는거랑 인덱스 같음
int score;

// y, x에 있는 블록 밑으로 쭉 내리기
void pull_down(int y, int x, bool is_green) {
	if (is_green) {
		int target_y = y;
		while (1) {
			if ((target_y + 1 < 10 && board_green[target_y + 1][x] == 0)
				&& (board_green[y][x]&1 || (x<3 && board_green[y][x]==2 && board_green[y][x+1]==2 && board_green[target_y+1][x+1]==0)))
				++target_y;
			else
				break;
		}


		if (y == target_y) return;

		if (board_green[y][x] == 2) {
			swap(board_green[y][x + 1], board_green[target_y][x + 1]);
			swap(board_green[y][x], board_green[target_y][x]);
		}
		else
			swap(board_green[y][x], board_green[target_y][x]);
	}
	else {
		int target_y = y;
		while (1) {
			if ((target_y + 1 < 10 && board_blue[target_y + 1][x] == 0)
				&& (board_blue[y][x] & 1 || (x < 3 && board_blue[y][x] == 2 && board_blue[y][x + 1] == 2 && board_blue[target_y + 1][x + 1] == 0)))
				++target_y;
			else
				break;
		}


		if (y == target_y) return;

		if (board_blue[y][x] == 2) {
			swap(board_blue[y][x + 1], board_blue[target_y][x + 1]);
			swap(board_blue[y][x], board_blue[target_y][x]);
		}
		else
			swap(board_blue[y][x], board_blue[target_y][x]);
	}
}

// type: 1: 한칸, 2: 가로, 3: 세로
void put(int type, int y, int x) {
	// green
	board_green[y][x] = type;
	if (type == 2)		board_green[y][x + 1] = type;
	else if (type == 3)	board_green[y + 1][x] = type;

	if (type == 3) pull_down(y + 1, x, true);
	pull_down(y, x, true);


	swap(y, x);


	// blue
	if (type == 2) type = 3;
	else if (type == 3) type = 2;

	board_blue[y][x] = type;
	if (type == 2)		board_blue[y][x + 1] = type;
	else if (type == 3)	board_blue[y + 1][x] = type;

	if (type == 3) pull_down(y + 1, x, false);
	pull_down(y, x, false);
}

// 연한 부분에 블록 있으면 밀기
void push() {
	// 초록
	int push_cnt = 0;
	push_cnt += (board_green[4][0]+board_green[4][1]+board_green[4][2]+board_green[4][3] > 0) +
		(board_green[5][0]+board_green[5][1]+board_green[5][2]+board_green[5][3] > 0);

	if (push_cnt) {
		for (int i = 9 - push_cnt; i >= 6 - push_cnt; --i) {
			for (int j = 0; j < 4; ++j) {
				board_green[i + push_cnt][j] = board_green[i][j];
			}
		}

		for (int i = 4; i <= 5; ++i)
			for (int j = 0; j < 4; ++j)
				board_green[i][j] = 0;
	}


	// 파랑
	push_cnt = 0;
	push_cnt += (board_blue[4][0] + board_blue[4][1] + board_blue[4][2] + board_blue[4][3] > 0) +
		(board_blue[5][0] + board_blue[5][1] + board_blue[5][2] + board_blue[5][3] > 0);

	if (push_cnt) {
		for (int i = 9 - push_cnt; i >= 6 - push_cnt; --i) {
			for (int j = 0; j < 4; ++j) {
				board_blue[i + push_cnt][j] = board_blue[i][j];
			}
		}

		for (int i = 4; i <= 5; ++i)
			for (int j = 0; j < 4; ++j)
				board_blue[i][j] = 0;
	}
}

// 가득찬 행 or 열 지움
bool erase() {
	int erased_cnt = 0;

	// 초록
	for (int i = 9; i >= 6; --i) {
		bool empty = false;
		for (int j = 0; j < 4 && !empty; ++j)
			if (board_green[i][j] == 0)
				empty = true;

		if (!empty) {
			for (int j = 0; j < 4; ++j)
				board_green[i][j] = 0;

			++erased_cnt;
		}
	}

	// 내리기
	for (int i = 8; i >= 4; --i) {
		for (int j = 0; j < 4; ++j) {
			if (board_green[i][j] == 0) {
				continue;
			}

			pull_down(i, j, true);
		}
	}



	// 파랑
	for (int i = 9; i >= 6; --i) {
		bool empty = false;
		for (int j = 0; j < 4 && !empty; ++j)
			if (board_blue[i][j] == 0)
				empty = true;

		if (!empty) {
			for (int j = 0; j < 4; ++j)
				board_blue[i][j] = 0;

			++erased_cnt;
		}
	}

	// 내리기
	for (int i = 8; i >= 4; --i) {
		for (int j = 0; j < 4; ++j) {
			if (board_blue[i][j] == 0) {
				continue;
			}

			pull_down(i, j, false);
		}
	}

	score += erased_cnt;
	return erased_cnt;
}


void debug_print() {
	// board 출력
	cout << "------\n";
	cout << "score: " << score << '\n';
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			if (i < 4 && j < 4) cout << '-' << ' ';
			else if (i >= 4 && j >= 4) cout << '*' << ' ';
			else if (j >= 4) cout << board_blue[j][i] << ' ';
			else cout << board_green[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n;
	cin >> n;
	while (n--) {
		int t, y, x;
		cin >> t >> y >> x;
		put(t, y, x);

		// loop
		while (erase())
			;

		push();

		debug_print();
	}

	int cnt = 0;

	for (int i = 6; i <= 9; ++i) {
		for (int j = 0; j < 4; ++j) {
			cnt += (board_green[i][j] != 0);
			cnt += (board_blue[i][j] != 0);
		}
	}

	cout << score << '\n' << cnt << '\n';

	return 0;
}
