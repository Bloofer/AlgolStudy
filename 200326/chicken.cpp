#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int N, M;
int arr[51][51];
bool visited[13];
int numOfChicken;

// 살려놓을 M개의 치킨집을 모두 구함
// ㄴ 모든 조합의 M개의 치킨집 경우의 수에서 도시의 치킨거리를 계산
// ㄴ 해당 치킨 거리 중 가장 작은 것을 저장한다.
// 치킨거리 = 집과 도시와의 거리
// 집 벡터, 치킨집 벡터를 저장해놓고 모든 치킨거리를 구해놓은 후, 정렬하기?

vector< pair<int, int> > house;
vector< pair<int, int> > chicken;
int minChickenDist = INT_MAX; // 도시의 최소 치킨 거리

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
	// 각 집에서 가장 가까운 치킨집 거리?
	// 1. 치킨집 M개의 조합을 모두 구함 (벡터의 인덱스)
	// 2. 해당 조합에 대한 치킨거리를 모두 구함
	// 3. 그 중에 최소를 반환
	if (idx == M) {
		//for (auto a : seq) cout << a << " ";
		//cout << endl;
		minChickenDist = get_min(minChickenDist, cal_city_chicken_dist(seq));
		return;
	}
	
	for (int i = val+1; i < numOfChicken; i++) {
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
