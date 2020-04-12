#include <iostream>
#include <climits>
#include <vector>
#include <string>
using namespace std;

int arr[8][8] = { 0, }; // 처음 방안의 벽과 cctv의 위치 배열
int range[8][8] = { 0, }; // cctv의 동작반경
int N, M; // N * M: 배열크기, C: cctv 갯수
vector< pair<int, int> > cctv; // cctv의 배열
int cctvDir[8];
int minSize = INT_MAX;
int cctvNum;
int wallNcctv = 0;

int min_val(int a, int b) {
	return a < b ? a : b;
}

// 각도에 따른 진행방향
// 0:→, 1:↓, 2:←, 3:↑
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
string dir[6] = {"", "0", "02", "03", "023", "0123"};

// 1: →,  2: ←→,  3: ↑→,  4: ←↑→, 5: ←↑→↓,  6: 벽
// 0, 02, 03, 023, 0123
// 방향정보 + 각도 { {0, 1}, {-1, 0}, {0, -1}, {1, 0} }
// 각 CCTV를 돌리는 경우의 수 고려
// 1:X4, 2:X2, 3:X4:, 4:X4, 5:X1

bool is_valid(int x, int y) {
	bool inScope = (x >= 0 && x < N && y >=0 && y < M);
	bool isEmpty = (arr[x][y] < 6);
	return inScope && isEmpty;
}

void init_range() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			range[i][j] = 0;
		}
	}
}

int calculate_size(string dirs) {
	for (int i = 0; i < cctv.size(); i++) {
		int x;
		int y;
		for(int s = 0; s < dir[cctvDir[i]].size(); s++){
			x = cctv[i].first;
			y = cctv[i].second;
			while (is_valid(x+dx[(dirs[i]+(dir[cctvDir[i]][s]-'0')-'0') % 4], y+dy[(dirs[i]+(dir[cctvDir[i]][s]-'0')-'0') % 4]))
			{
				x += dx[(dirs[i]+(dir[cctvDir[i]][s]-'0') - '0') % 4];
				y += dy[(dirs[i]+(dir[cctvDir[i]][s]-'0') - '0') % 4];
				if(arr[x][y] == 0) range[x][y] = 1;
			}
		}
	}

	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (range[i][j] == 1) sum++;
		}
	}
	return N*M - sum - wallNcctv;
}

void dfs(int idx, string dirs) {
	if (idx == cctvNum) {
		int num = calculate_size(dirs);
		minSize = min_val(minSize, num);
		init_range();
	}
	else {
		if (cctvDir[idx] == 1 || cctvDir[idx] == 3 || cctvDir[idx] == 4) { // 4방향으로 추가하고 재귀 호출
			dfs(idx + 1, dirs + "0");
			dfs(idx + 1, dirs + "1");
			dfs(idx + 1, dirs + "2");
			dfs(idx + 1, dirs + "3");
		}
		else if (cctvDir[idx] == 2) { // 2방향으로 추가하고 재귀 호출
			dfs(idx + 1, dirs + "0");
			dfs(idx + 1, dirs + "1");
		}
		else { // 전방향이므로 회전 X, 재귀로 방향정보만 추가
			dfs(idx + 1, dirs + "0");
		}

	}

}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
		{
			cin >> arr[i][j];
			if (arr[i][j] >= 1 && arr[i][j] <= 5) {
				cctvDir[cctv.size()] = arr[i][j];
				cctv.push_back(pair<int, int>(i, j));
			}
			if (arr[i][j] > 0) wallNcctv++;
		}
	}

	cctvNum = cctv.size();
	dfs(0, "");
	cout << minSize;

	return 0;
}
