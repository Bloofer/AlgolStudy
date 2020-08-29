#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int N, M;
int arr[51][51];
bool visited[13];
int numOfChicken;

vector< pair<int, int> > house;		// 집들의 좌표 벡터
vector< pair<int, int> > chicken;	// 치킨집들의 좌표 벡터
int minChickenDist = INT_MAX; 		// 도시의 최소 치킨 거리

int get_min(int a, int b) {
	return a < b ? a : b;
}

int cal_dist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

int cal_city_chicken_dist(vector<int> seq) {
	vector< pair<int, int> > slctChicken;
	for (auto i : seq) slctChicken.push_back(chicken[i]);
	int sum = 0;
	for (auto i : house) {
		int min = INT_MAX;
		for (auto j : slctChicken) {
			min = get_min(min, cal_dist(i.first, i.second, j.first, j.second));
		}
		sum += min;
	}
	return sum;
}

void cal_chicken_dist(int idx, int val, vector<int> seq) {
	if (idx == M) {
		// 조합에 대한 치킨거리를 구해 최소인 것을 업데이트
		minChickenDist = get_min(minChickenDist, cal_city_chicken_dist(seq));
		return;
	}

	for (int i = val+1; i < numOfChicken; i++) {
		// 치킨집 M개의 조합을 모두 구함(벡터의 인덱스)
		if (!visited[i]) {
			visited[i] = true;
			seq.push_back(i);
			cal_chicken_dist(idx + 1, i, seq);
			seq.pop_back();
			visited[i] = false;
		}
	}
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 1) house.push_back(pair<int, int>(i, j));
			else if (arr[i][j] == 2) chicken.push_back(pair<int, int>(i, j));
		}
	}
	numOfChicken = chicken.size();
	cal_chicken_dist(0, -1, vector<int>());

	cout << minChickenDist << endl;

	return 0;
}
