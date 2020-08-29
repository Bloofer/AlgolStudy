#include <iostream>
#include <vector>
using namespace std;

int N, L, R;
int arr[50][50] = { 0, };
bool hrz[50][49] = { 0, }; // 각 인접 나라별 국경개방 여부 (가로축)
bool vtc[49][50] = { 0, }; // 각 인접 나라별 국경개방 여부 (세로축)
bool visit[50][50] = { 0, };
vector< pair<int, int> > groupVec;

// 1. 각 인접국가별 개방가능 여부를 확인
//	  ㄴ open_pop() 함수 사용: L <= |인구차이| <= R 확인하는 함수
// 2. 개방가능 국가 없으면 종료, 있으면 개방 후 인구이동
//	  ㄴ move_pop() 함수 사용: sum(연합의 인구) / 연합 수 반환하는 함수
//	  ㄴ move_pop()은 dfs 이용하여 연합의 인구 배분하고, 배분한 지점은 마킹, 안한 지점들을 마저 찾아가도록
// 3. 마지막까지 이동 후 이동 횟수 반환

bool open_pop() {
	bool opened = false;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1; j++) {
			if (abs(arr[i][j] - arr[i][j + 1]) >= L && abs(arr[i][j] - arr[i][j + 1]) <= R) {
				hrz[i][j] = true;
				opened = true;
			}
			if (abs(arr[j][i] - arr[j + 1][i]) >= L && abs(arr[j][i] - arr[j + 1][i]) <= R) {
				vtc[j][i] = true;
				opened = true;
			}
		}
	}
	return opened;
}

bool is_valid(int i, int j) {
	return (i >= 0 && i < N && j >= 0 && j < N);
}

void divide_pop() {
	int sum = 0;
	for (int i = 0; i < groupVec.size(); i++) sum += arr[groupVec.at(i).first][groupVec.at(i).second];
	int avg = sum / groupVec.size();
	for (int i = 0; i < groupVec.size(); i++) arr[groupVec.at(i).first][groupVec.at(i).second] = avg;
	groupVec.clear();
}

void move_pop(int x, int y) {
	visit[x][y] = true;
	groupVec.push_back(pair<int, int>(x, y));

	if (is_valid(x, y + 1)) { if (hrz[x][y] && !visit[x][y+1]) move_pop(x, y + 1); } // →
	if (is_valid(x + 1, y)) { if (vtc[x][y] && !visit[x+1][y]) move_pop(x + 1, y); } // ↓
	if (is_valid(x, y - 1)) { if (hrz[x][y - 1] && !visit[x][y-1]) move_pop(x, y - 1); } // ←
	if (is_valid(x - 1, y)) { if (vtc[x - 1][y] && !visit[x-1][y]) move_pop(x - 1, y); } // ↑
}

void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1; j++) {
			hrz[i][j] = false;
			vtc[j][i] = false;
			visit[i][j] = false;
		}
	}
	for (int i = 0; i < N; i++) visit[i][N - 1] = false;
}

int main() {
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}

	int cnt = 0;
	while (open_pop() && cnt <= 2000) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!visit[i][j]) {
					move_pop(i, j);
					divide_pop();
				}
			}
		}
		cnt++;
		init();
	}

	cout << cnt;
	return 0;
}
