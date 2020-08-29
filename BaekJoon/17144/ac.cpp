#include <iostream>
using namespace std;

int R, C, T;
int room[50][50] = { 0, };
int tmp[50][50] = { 0, };
int ac[2]; // 공기청정기 Y 좌표
// { →, ←, ↑, ↓ }
int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

bool available(int x, int y) {
	bool inRange = (x >= 0) && (y >= 0) && (x < R) && (y < C);
	bool notOnAc = !((x == ac[0]) && (y == 0)) && !((x == ac[1]) && (y == 0));
	return inRange && notOnAc; // 먼지가 퍼질 수 있는 위치는 영역내 있으면서, 공기청정기가 없는 곳
}

void clear_tmp() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) tmp[i][j] = 0;
	}
}

void spread_dirt(int a, int b) {
	int spread = room[a][b] / 5;
	int sum = 0;

	// 주변 4방향 중 가용한 방향으로 먼지를 퍼뜨리고, 기존 위치에서 퍼진만큼 먼지를 뺌
	for (int i = 0; i < 4; i++) {
		if (available(a + dx[i], b + dy[i])) {
			sum += spread;
			tmp[a + dx[i]][b + dy[i]] += spread;
		}
	}
	tmp[a][b] += (room[a][b] - sum);
}

void run_ac() { // 매 초마다 미세먼지 확산 및 공기청정기 가동 시뮬레이션 함수
	// 1. 미세먼지 확산
	//		- 확산시 매 위치에서 주변 위치로 퍼뜨리면서 새로 갱신되는 먼지량은 계산량에 포함하지 않도록
	//		- 확산시 퍼지는 위치는 AC, 벽 제외한 먼지 이미 있는 위치 포함
	clear_tmp();
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (room[i][j] < 5) tmp[i][j] += room[i][j];
			else spread_dirt(i, j);
		}
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) { if (room[i][j] != -1) room[i][j] = tmp[i][j]; }
	}

	// 2. AC 작동
	// 상단 AC 반시계 방향 이동
	int val = room[ac[0]][C - 1]; 
	for (int i = C-1; i >= 2; i--) room[ac[0]][i] = room[ac[0]][i - 1]; // → 이동
	room[ac[0]][1] = 0;
	int val2 = room[0][C - 1];
	for (int i = 0; i <= ac[0] - 2; i++) room[i][C - 1] = room[i + 1][C - 1]; // ↑ 이동
	room[ac[0] - 1][C - 1] = val;
	val = room[0][0];
	for (int i = 0; i < C - 2; i++) room[0][i] = room[0][i + 1]; // ← 이동
	room[0][C - 2] = val2;
	for (int i = ac[0] - 1; i >= 2; i--) room[i][0] = room[i - 1][0]; // ↓ 이동
	room[1][0] = val;

	// 하단 AC 시계 방향 이동
	val = room[ac[1]][C - 1];
	for (int i = C - 1; i >= 2; i--) room[ac[1]][i] = room[ac[1]][i - 1]; // → 이동
	room[ac[1]][1] = 0;
	val2 = room[R - 1][C - 1];
	for (int i = R - 1; i >= ac[1] + 2; i--) room[i][C - 1] = room[i - 1][C - 1]; // ↓ 이동
	room[ac[1] + 1][C - 1] = val;
	val = room[R - 1][0];
	for (int i = 0; i < C - 2; i++) room[R - 1][i] = room[R - 1][i + 1]; // ← 이동
	room[R - 1][C - 2] = val2;
	for (int i = ac[1] + 1; i < R - 2; i++) room[i][0] = room[i + 1][0]; // ↑ 이동
	room[R - 2][0] = val;
}

int main() {
	cin >> R >> C >> T;
	int idx = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> room[i][j];
			if (room[i][j] == -1) ac[idx++] = i;
		}
	}

	for (int i = 0; i < T; i++) run_ac();
	int sum = 2;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) sum += room[i][j];
	}
	cout << sum << endl;

	return 0;
}
