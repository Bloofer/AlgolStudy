#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int N;
struct dragonCurve {
	int x, y, g;
	string d;
} dc[20];

int hrz[101][100] = {0, }; // 가로선 배열
int vtc[100][101] = {0, }; // 세로선 배열
int arr[101][101] = {0, }; // 드래곤 커브 좌표판

string get_next_gen(string gen) {
	string revGen = gen;
	reverse(revGen.begin(), revGen.end());
	for (int i = 0; i < revGen.size(); i++) {
		if (revGen.at(i) == '3') revGen.at(i) = '0';
		else revGen.at(i) = revGen.at(i) + 1;
	}

	return gen + revGen;
}

void mark_dragon_curve(int x, int y, string drg) {
	int curX = x;
	int curY = y;
	for (int i = 0; i < drg.size(); i++) {
		if (drg.at(i) == '0') hrz[curX][curY++] = 1;
		else if (drg.at(i) == '1') vtc[--curX][curY] = 1;
		else if (drg.at(i) == '2') hrz[curX][--curY] = 1;
		else if (drg.at(i) == '3') vtc[curX++][curY] = 1;
	}
}

void mark_array() {
	for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 99; j++) {
			if(hrz[i][j] == 1) {
				arr[i][j] = 1;
				arr[i][j + 1] = 1;
			}
			if(vtc[j][i] == 1) {
				arr[j][i] = 1;
				arr[j + 1][i] = 1;
			}
		}
	}
}

int count_square() {
	int cnt = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if(arr[i][j] == 1 && arr[i][j+1] == 1 && arr[i+1][j] == 1 && arr[i+1][j+1] == 1) cnt++;
		}
	}
	return cnt;
}

int main() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> dc[i].y;
		cin >> dc[i].x;
		cin >> dc[i].d;
		cin >> dc[i].g;
		string dir = dc[i].d;
		for (int j = 0; j < dc[i].g; j++) dir = get_next_gen(dir);
		mark_dragon_curve(dc[i].x, dc[i].y, dir);
	}

	mark_array();
	cout << count_square() << endl;
	return 0;
}
