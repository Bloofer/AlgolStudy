#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int A[101][101] = { 0, };
int R, C, K;
int rowSiz, colSiz; // 매 턴마다의 |row|, |col|을 비교하여 R/C 연산을 선택
int ans = 0;
enum OpType {
	ROp = 0, // R 연산
	COp = 1  // C 연산
};

int max_val(int a, int b) {
	return a > b ? a : b;
}

int sort_arr(vector<int> &v, int idx, OpType ot) {
	if (v.empty()) return 0;

	// 1. 배열 내 숫자의 등장 횟수를 계수
	map<int, int> m;
	for (auto i : v) {
		if (m.find(i) == m.end()) m.insert(map<int, int>::value_type(i, 1)); // 해당 숫자가 맵에 없을 때, 새로 맵을 생성
		else m[i]++; // 해당 숫자가 맵에 있을 때, 등장횟수 증가
	}

	// 2. 맵을 배열로 옮겨서 정렬 (A. 숫자의 등장 횟수를 우선으로 오름차순정렬, B. 숫자 등장횟수가 같으면, 숫자의 크기를 기준으로 오름차순정렬)
	vector< pair<int, int> > mvec;
	copy(m.begin(), m.end(), back_inserter< vector< pair<int, int> > >(mvec));
	sort(mvec.begin(), mvec.end(),
		[](const pair<int, int>& a, const pair<int, int>& b) {
		if (a.second != b.second)
			return a.second < b.second;
		else
			return a.first < b.first;
	});

	// 3. 정렬된 배열을 모두 채워줌 (A. 빈 자리는 모두 0으로, B. 배열이 넘치면 100번째 인덱스까지만 사용)
	int cnt = 0;
	for (auto i : mvec) {
		if (cnt >= 100) break;
		if (ot == ROp) {
			A[idx][cnt] = i.first;
			A[idx][cnt + 1] = i.second;
		}
		else {
			A[cnt][idx] = i.first;
			A[cnt + 1][idx] = i.second;
		}
		cnt += 2;
	}
	int siz = cnt;
	for (; cnt < 100; cnt++) {
		if (ot == ROp) A[idx][cnt] = 0;
		else A[cnt][idx] = 0;
	}

	return siz;
}

void run_turn(OpType ot) {
	if (ot == ROp) {
		for (int i = 0; i < rowSiz; i++) {
			vector<int> v;
			for (int j = 0; j<100; j++) if (A[i][j] != 0) v.push_back(A[i][j]);
			int siz = sort_arr(v, i, ot);
			colSiz = max_val(siz, colSiz);
		}
	}
	else {
		for (int i = 0; i < colSiz; i++) {
			vector<int> v;
			for (int j = 0; j<100; j++) if (A[j][i] != 0) v.push_back(A[j][i]);
			int siz = sort_arr(v, i, ot);
			rowSiz = max_val(siz, rowSiz);
		}
	}
}

int main() {
	cin >> R >> C >> K;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> A[i][j];
		}
	}

	rowSiz = colSiz = 3;
	if (A[R - 1][C - 1] != K) {
		for (int i = 1; i <= 100; i++) {
			// 행/열의 크기에 따라 R/C 연산을 수행
			if (rowSiz >= colSiz) run_turn(ROp);
			else run_turn(COp);

			if (A[R - 1][C - 1] == K) {
				ans = i;
				break;
			}
			else if (i == 100) ans = -1;
		}
	}

	cout << ans << endl;
	return 0;
}
