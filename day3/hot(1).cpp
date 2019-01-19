#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void heap_push(vector<int> &v, int i){
    // 힙에 원소를 push
    v.push_back(-i); // max heap을 min heap처럼 사용하기 위해 음수로 뒤집어 넣는다.
    push_heap(v.begin(), v.end());
}

int heap_pop(vector<int> &v){
    // 힙의 원소를 pop
    int frt = -v.front(); // 음수화된 숫자를 다시 꺼낼땐 양수화시킨다.
    pop_heap(v.begin(), v.end());
    v.pop_back();
    return frt;
}

int solution(vector<int> scoville, int K) {
    int answer = 0;
    for(int i=0; i<scoville.size(); i++) scoville.at(i) = -scoville.at(i);
    // max heap을 min heap으로 쓰기 위해 음수로 만듦

    make_heap(scoville.begin(), scoville.end());
    while(-scoville.front() < K) {
    // 스코빌 지수가 하나라도 K보다 낮은 경우 반복
        if(scoville.size() == 1) return -1;
        int fstLow = heap_pop(scoville);
        int sndLow = heap_pop(scoville);
        heap_push(scoville, fstLow + sndLow * 2);
        answer++;
    }

    return answer;
}