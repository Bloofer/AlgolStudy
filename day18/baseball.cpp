#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool possible[1000];

void filter(vector<int> baseball){
    for(int i=123; i<=987; i++){
        if(!possible[i]) continue; // 불가능한 조합은 건너뜀
        int str = 0;
        int ball = 0;
        string n1 = to_string(i);
        string n2 = to_string(baseball.front());
        for(int j=0; j<3; j++){
            if(n1.at(j) == n2.at(j)) str++;
            if(string::npos != n2.find(n1.at(j))) ball++;
        }
        if(ball >= str) ball -= str;

        if(str != baseball[1] || ball != baseball[2]) { possible[i] = false; }
        else { possible[i] = true; }
        // 스트라이크/볼 수를 계산해서 조건 충족못하는 조합 버리기
    }
}

int solution(vector<vector<int>> baseball) {
    for(int i=1; i<=9; i++){
        for(int j=1; j<=9; j++){
            if(j==i) continue;
            for(int k=1; k<=9; k++){
                if(k==j || k==i) continue;
                possible[100*i+10*j+k] = true;
                // 가능한 숫자놀이의 조합을 먼저 만듬
            }
        }
    }

    for(auto v:baseball) filter(v); 
    // 숫자조합을 필터(야구놀이조건)에 놓고 매 조건에 충족못하는 조합을 버림
    
    int cnt = 0;
    for(int i=123; i<=987; i++) if(possible[i]) cnt++;
    return cnt;
}

int main(){
    vector<vector<int>> baseball = {{123, 1, 1}, {356, 1, 0}, {327, 2, 0}, {489, 0, 1}};
    cout << solution(baseball);

    return 0;
}