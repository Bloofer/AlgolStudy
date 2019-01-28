#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool wghtChk[10000]; // 주어진 추의 배열 조합 체크
vector<int> wghtComb; // 추로 만들수있는 무게 조합

void make_comb(vector<int> weight, int idx, int totalWght){
    // base case
    if(idx == weight.size()) {
        return;
        }

    // recursive case
    for(int i=0; i<weight.size(); i++){
        if(!wghtChk[i]){            
            wghtChk[i] = true;
            totalWght += weight[i];
            wghtComb.push_back(totalWght);
            make_comb(weight, idx+1, totalWght);
            totalWght -= weight[i];
            wghtChk[i] = false;
        }
    }

}

int solution(vector<int> weight) {
    // 1. 먼저 추 배열을 정렬
    sort(weight.begin(), weight.end());

    // 2. 정렬된 추 배열을 이용해 만들수 있는 모든 무게 조합 만들기
    make_comb(weight, 0, 0);

    // 3. 만들어진 무게 조합 중복 제거 및 정렬
    sort(wghtComb.begin(), wghtComb.end());
    auto last = unique(wghtComb.begin(), wghtComb.end());
    wghtComb.erase(last, wghtComb.end()); 

    /* for(int i=0; i<wghtComb.size(); i++){
        cout << wghtComb[i] << " ";
    }
    cout << endl; */

    // 4. 무게 조합 벡터 순회하면서 측정할수 없는 무게 최소값 찾음
    int answer = 0;
    for(int i=0; i<wghtComb.size(); i++){
        if(wghtComb[i] != i+1){
            answer = i+1;
            break;
        } else if(i == wghtComb.size()-1){
            answer = wghtComb.size();
        }
    }

    return answer;
}