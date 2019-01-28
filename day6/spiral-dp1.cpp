#include <string>
#include <vector>
#include <iostream>
using namespace std;

long long fib[80]; // 피보나치 수의 캐시

long long get_fib(int x) {
    // 캐싱을 활용한 피보나치 함수
    if (x == 0) {fib[0] = 0; return 0;}
    else if (x == 1) {fib[1] = 1; return 1;}
    else {
        if(fib[x-1] != 0 && fib[x-2] != 0) {
            fib[x] = fib[x-1] + fib[x-2];
            return fib[x];
        } else if(fib[x-1] != 0) {
            fib[x] = fib[x-1] + get_fib(x-2);
            return fib[x];
        } else if(fib[x-2] != 0) {
            fib[x] = get_fib(x-1) + fib[x-2];
            return fib[x];
        } else {
            fib[x] = get_fib(x-1) + get_fib(x-2);
            return fib[x];
        }
    }
}

long long solution(int N) {
// 나선형으로 이어붙여지는 정사각형의 한 변의 길이는 피보나치 수열로 증가한다.
// 이러한 나선형의 전체 사각형의 둘레를 식으로 나타내면 fib(i)*4 + fib(i-1)*2를 항상 만족한다.(i>=3) 

    long long answer = 0;
    fib[N] = get_fib(N);
    answer = fib[N]*4 + fib[N-1]*2;

    return answer;
}