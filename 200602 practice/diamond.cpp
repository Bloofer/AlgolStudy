#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int N, K;
vector<int> diaVec;
int bigSize = INT_MIN;

int get_big(int a, int b){
  return a > b ? a : b;
}

int main(){
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    cin >> N >> K;
    for (int j = 0; j < N; j++) {
      int d;
      cin >> d;
      diaVec.push_back(d);
    }
    // 1. diaVec에 넣은 크기들을 오름차순으로 정렬
    sort(diaVec.begin(), diaVec.end());

    // 2. Sliding Window를 이용,
    //    for loop안에서 idx 1부터 N까지
    //    head와 tail을 K 범위 안에 늘려가며 최대 크기를 업데이트
    int head = 0;
    int tail = 0;
    for (int j = 0; j < N; j++) {
      tail = j;
      if(diaVec[tail] - diaVec[head] <= K) {
        bigSize = get_big(bigSize, tail-head+1);
        continue;
      }
      else head++;
    }

    // 3. 끝으로 가장 큰 size를 반환
    cout << "#" << i+1 << " " << bigSize << endl;
    diaVec.clear();
    bigSize = INT_MIN;
  }

  return 0;
}
