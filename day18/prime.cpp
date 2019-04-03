#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool chk[1000001];

int solution(int n) {
    int cnt = 1;

    for(int i=3; i<=n; i+=2){
        // 2의 배수를 건너뜀. 이게 탐색공간을 반 줄여서 차이큰듯.
        if(chk[i]) continue;
        else{
            chk[i] = true;
            cnt++;
            int m = i;
            // 체크안된수(소수)는 새로 체크하며 n이하의 해당 수의 배수들도 체크
            while(m+i <= n){
                m += i;
                chk[m] = true;
            }
        }
    }

    return cnt;
}

int main(){
    int n;
    cin >> n; 
    cout << solution(n) << endl;
}