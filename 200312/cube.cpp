#include <iostream>
#include <string>
using namespace std;

enum side{ U, D, F, B, L, R }; // 0:위, 1:아래, 2:앞, 3:뒤, 4:왼, 5:오른
char cube[6][3][3]; // 3 * 3 정육면체
int N;

void init() {
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[U][i][j] = 'w';
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[D][i][j] = 'y';
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[F][i][j] = 'r';
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[B][i][j] = 'o';
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[L][i][j] = 'g';
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[R][i][j] = 'b';
}

void turn_up_cw() {
	char tmp[3] = { cube[F][0][0], cube[F][0][1], cube[F][0][2] };
	for (int i = 0; i < 3; i++) cube[F][0][i] = cube[R][0][i]; // 오른 윗줄 → 앞 윗줄
	for (int i = 0; i < 3; i++) cube[R][0][i] = cube[B][0][i]; // 뒤 윗줄 → 오른 윗줄
	for (int i = 0; i < 3; i++) cube[B][0][i] = cube[L][0][i]; // 왼 윗줄 → 뒤 윗줄
	for (int i = 0; i < 3; i++) cube[L][0][i] = tmp[i]; // 앞 윗줄 → 왼 윗줄

	char tmp2d[3][3] = {
		{ cube[U][2][0], cube[U][1][0], cube[U][0][0] },
		{ cube[U][2][1], cube[U][1][1], cube[U][0][1] },
		{ cube[U][2][2], cube[U][1][2], cube[U][0][2] }
	};
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[U][i][j] = tmp2d[i][j]; // 윗면 시계방향 회전
}

void turn_up_ccw() {
	char tmp[3] = { cube[F][0][0], cube[F][0][1], cube[F][0][2] };
	for (int i = 0; i < 3; i++) cube[F][0][i] = cube[L][0][i]; // 왼 윗줄 → 앞 윗줄
	for (int i = 0; i < 3; i++) cube[L][0][i] = cube[B][0][i]; // 뒤 윗줄 → 왼 윗줄
	for (int i = 0; i < 3; i++) cube[B][0][i] = cube[R][0][i]; // 오른 윗줄 → 뒤 윗줄
	for (int i = 0; i < 3; i++) cube[R][0][i] = tmp[i]; // 앞 윗줄 → 오른 윗줄

	char tmp2d[3][3] = {
		{ cube[U][0][2], cube[U][1][2], cube[U][2][2] },
		{ cube[U][0][1], cube[U][1][1], cube[U][2][1] },
		{ cube[U][0][0], cube[U][1][0], cube[U][2][0] }
	};
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[U][i][j] = tmp2d[i][j]; // 윗면 반시계방향 회전
}

void turn_down_cw() {
	char tmp[3] = { cube[F][2][0], cube[F][2][1], cube[F][2][2] };
	for (int i = 0; i < 3; i++) cube[F][2][i] = cube[L][2][i]; // 왼 윗줄 → 앞 윗줄
	for (int i = 0; i < 3; i++) cube[L][2][i] = cube[B][2][i]; // 뒤 윗줄 → 왼 윗줄
	for (int i = 0; i < 3; i++) cube[B][2][i] = cube[R][2][i]; // 오른 윗줄 → 뒤 윗줄
	for (int i = 0; i < 3; i++) cube[R][2][i] = tmp[i]; // 앞 윗줄 → 오른 윗줄

	char tmp2d[3][3] = {
		{ cube[D][2][0], cube[D][1][0], cube[D][0][0] },
		{ cube[D][2][1], cube[D][1][1], cube[D][0][1] },
		{ cube[D][2][2], cube[D][1][2], cube[D][0][2] }
	};
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[D][i][j] = tmp2d[i][j]; // 아랫면 시계방향 회전
}

void turn_down_ccw() {
	char tmp[3] = { cube[F][2][0], cube[F][2][1], cube[F][2][2] };
	for (int i = 0; i < 3; i++) cube[F][2][i] = cube[R][2][i]; // 오른 아랫줄 → 앞 아랫줄
	for (int i = 0; i < 3; i++) cube[R][2][i] = cube[B][2][i]; // 뒤 아랫줄 → 오른 아랫줄
	for (int i = 0; i < 3; i++) cube[B][2][i] = cube[L][2][i]; // 왼 아랫줄 → 뒤 아랫줄
	for (int i = 0; i < 3; i++) cube[L][2][i] = tmp[i]; // 앞 아랫줄 → 왼 아랫줄

	char tmp2d[3][3] = {
		{ cube[D][0][2], cube[D][1][2], cube[D][2][2] },
		{ cube[D][0][1], cube[D][1][1], cube[D][2][1] },
		{ cube[D][0][0], cube[D][1][0], cube[D][2][0] }
	};
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[D][i][j] = tmp2d[i][j]; // 아랫면 반시계방향 회전
}

void turn_front_cw() {
	char tmp[3] = { cube[R][0][0], cube[R][1][0], cube[R][2][0] };
	for (int i = 0; i < 3; i++) cube[R][i][0] = cube[U][2][i]; // 오른 왼줄 → 위 아랫줄
	for (int i = 0; i < 3; i++) cube[U][2][i] = cube[L][2-i][2]; // 위 아랫줄 → 왼 오른줄
	for (int i = 0; i < 3; i++) cube[L][2-i][2] = cube[D][0][2-i]; // 왼 오른줄 → 아래 윗줄
	for (int i = 0; i < 3; i++) cube[D][0][2-i] = tmp[i]; // 아래 윗줄 → 오른 왼줄

	char tmp2d[3][3] = {
		{ cube[F][2][0], cube[F][1][0], cube[F][0][0] },
		{ cube[F][2][1], cube[F][1][1], cube[F][0][1] },
		{ cube[F][2][2], cube[F][1][2], cube[F][0][2] }
	};
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[F][i][j] = tmp2d[i][j]; // 앞면 시계방향 회전
}

void turn_front_ccw() {
	char tmp[3] = { cube[R][0][0], cube[R][1][0], cube[R][2][0] };
	for (int i = 0; i < 3; i++) cube[R][i][0] = cube[D][0][2-i]; // 오른 왼줄 → 아래 윗줄
	for (int i = 0; i < 3; i++) cube[D][0][2-i] = cube[L][2-i][2]; // 아래 윗줄 → 왼 오른줄
	for (int i = 0; i < 3; i++) cube[L][2-i][2] = cube[U][2][i]; // 왼 오른줄 → 위 아랫줄
	for (int i = 0; i < 3; i++) cube[U][2][i] = tmp[i]; // 위 아랫줄 → 오른 왼줄

	char tmp2d[3][3] = {
		{ cube[F][0][2], cube[F][1][2], cube[F][2][2] },
		{ cube[F][0][1], cube[F][1][1], cube[F][2][1] },
		{ cube[F][0][0], cube[F][1][0], cube[F][2][0] }
	};
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[F][i][j] = tmp2d[i][j]; // 앞면 반시계방향 회전
}

void turn_back_cw() {
	char tmp[3] = { cube[R][0][2], cube[R][1][2], cube[R][2][2] };
	for (int i = 0; i < 3; i++) cube[R][i][2] = cube[D][2][2 - i]; // 오른 오른줄 → 아래 아랫줄
	for (int i = 0; i < 3; i++) cube[D][2][2 - i] = cube[L][2 - i][0]; // 아래 아랫줄 → 왼 왼줄
	for (int i = 0; i < 3; i++) cube[L][2 - i][0] = cube[U][0][i]; // 왼 왼줄 → 위 윗줄
	for (int i = 0; i < 3; i++) cube[U][0][i] = tmp[i]; // 위 윗줄 → 오른 오른줄

	char tmp2d[3][3] = {
		{ cube[B][2][0], cube[B][1][0], cube[B][0][0] },
		{ cube[B][2][1], cube[B][1][1], cube[B][0][1] },
		{ cube[B][2][2], cube[B][1][2], cube[B][0][2] }
	};
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[B][i][j] = tmp2d[i][j]; // 뒷면 시계방향 회전
}

void turn_back_ccw() {
	char tmp[3] = { cube[R][0][2], cube[R][1][2], cube[R][2][2] };
	for (int i = 0; i < 3; i++) cube[R][i][2] = cube[U][0][i]; // 오른 오른줄 → 위 윗줄
	for (int i = 0; i < 3; i++) cube[U][0][i] = cube[L][2-i][0]; // 위 윗줄 → 왼 왼줄
	for (int i = 0; i < 3; i++) cube[L][2-i][0] = cube[D][2][2-i]; // 왼 왼줄 → 아래 아랫줄
	for (int i = 0; i < 3; i++) cube[D][2][2-i] = tmp[i]; // 아래 아랫줄 → 오른 오른줄

	char tmp2d[3][3] = {
		{ cube[B][0][2], cube[B][1][2], cube[B][2][2] },
		{ cube[B][0][1], cube[B][1][1], cube[B][2][1] },
		{ cube[B][0][0], cube[B][1][0], cube[B][2][0] }
	};
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[B][i][j] = tmp2d[i][j]; // 뒷면 반시계방향 회전
}

void turn_right_cw() {
	char tmp[3] = { cube[B][0][0], cube[B][1][0], cube[B][2][0] };
	for (int i = 0; i < 3; i++) cube[B][i][0] = cube[U][2-i][2]; // 뒤 왼줄 → 위 오른줄
	for (int i = 0; i < 3; i++) cube[U][2-i][2] = cube[F][2-i][2]; // 위 오른줄 → 앞 오른줄
	for (int i = 0; i < 3; i++) cube[F][2-i][2] = cube[D][2-i][2]; // 앞 오른줄 → 아래 오른줄
	for (int i = 0; i < 3; i++) cube[D][2-i][2] = tmp[i]; // 아래 오른줄 → 뒤 왼줄

	char tmp2d[3][3] = {
		{ cube[R][2][0], cube[R][1][0], cube[R][0][0] },
		{ cube[R][2][1], cube[R][1][1], cube[R][0][1] },
		{ cube[R][2][2], cube[R][1][2], cube[R][0][2] }
	};
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[R][i][j] = tmp2d[i][j]; // 오른면 시계방향 회전
}

void turn_right_ccw() {
	char tmp[3] = { cube[B][0][0], cube[B][1][0], cube[B][2][0] };
	for (int i = 0; i < 3; i++) cube[B][i][0] = cube[D][2-i][2]; // 뒤 왼줄 → 아래 오른줄
	for (int i = 0; i < 3; i++) cube[D][2-i][2] = cube[F][2-i][2]; // 아래 오른줄 → 앞 오른줄
	for (int i = 0; i < 3; i++) cube[F][2-i][2] = cube[U][2-i][2]; // 앞 오른줄 → 위 오른줄
	for (int i = 0; i < 3; i++) cube[U][2-i][2] = tmp[i]; // 위 오른줄 → 뒤 왼줄

	char tmp2d[3][3] = {
		{ cube[R][0][2], cube[R][1][2], cube[R][2][2] },
		{ cube[R][0][1], cube[R][1][1], cube[R][2][1] },
		{ cube[R][0][0], cube[R][1][0], cube[R][2][0] }
	};
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[R][i][j] = tmp2d[i][j]; // 오른면 반시계방향 회전
}

void turn_left_cw() {
	char tmp[3] = { cube[B][0][2], cube[B][1][2], cube[B][2][2] };
	for (int i = 0; i < 3; i++) cube[B][i][2] = cube[D][2 - i][0]; // 뒤 오른줄 → 아래 왼줄
	for (int i = 0; i < 3; i++) cube[D][2 - i][0] = cube[F][2 - i][0]; // 아래 왼줄 → 앞 왼줄
	for (int i = 0; i < 3; i++) cube[F][2 - i][0] = cube[U][2 - i][0]; // 앞 왼줄 → 위 왼줄
	for (int i = 0; i < 3; i++) cube[U][2 - i][0] = tmp[i]; // 위 왼줄 → 뒤 오른줄

	char tmp2d[3][3] = {
		{ cube[L][2][0], cube[L][1][0], cube[L][0][0] },
		{ cube[L][2][1], cube[L][1][1], cube[L][0][1] },
		{ cube[L][2][2], cube[L][1][2], cube[L][0][2] }
	};
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[L][i][j] = tmp2d[i][j]; // 왼면 시계방향 회전
}

void turn_left_ccw() {
	char tmp[3] = { cube[B][0][2], cube[B][1][2], cube[B][2][2] };
	for (int i = 0; i < 3; i++) cube[B][i][2] = cube[U][2-i][0]; // 뒤 오른줄 → 위 왼줄
	for (int i = 0; i < 3; i++) cube[U][2-i][0] = cube[F][2-i][0]; // 위 왼줄 → 앞 왼줄
	for (int i = 0; i < 3; i++) cube[F][2-i][0] = cube[D][2-i][0]; // 앞 왼줄 → 아래 왼줄
	for (int i = 0; i < 3; i++) cube[D][2-i][0] = tmp[i]; // 아래 왼줄 → 뒤 오른줄

	char tmp2d[3][3] = {
		{ cube[L][0][2], cube[L][1][2], cube[L][2][2] },
		{ cube[L][0][1], cube[L][1][1], cube[L][2][1] },
		{ cube[L][0][0], cube[L][1][0], cube[L][2][0] }
	};
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cube[L][i][j] = tmp2d[i][j]; // 왼면 반시계방향 회전
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		init();
		int num;
		cin >> num;
		string dir;

		for (int j = 0; j < num; j++) {
			cin >> dir;
			switch (dir[0]) {
				case 'U': (dir[1] == '+') ? turn_up_cw() : turn_up_ccw(); break;
				case 'D': (dir[1] == '+') ? turn_down_cw() : turn_down_ccw(); break;
				case 'F': (dir[1] == '+') ? turn_front_cw() : turn_front_ccw(); break;
				case 'B': (dir[1] == '+') ? turn_back_cw() : turn_back_ccw(); break;
				case 'L': (dir[1] == '+') ? turn_left_cw() : turn_left_ccw(); break;
				case 'R': (dir[1] == '+') ? turn_right_cw() : turn_right_ccw(); break;
			}
		}

		for (int p = 0; p < 3; p++) {
			for (int q = 0; q < 3; q++) cout << cube[U][p][q];
			cout << endl;
		}
	}

	return 0;
}
