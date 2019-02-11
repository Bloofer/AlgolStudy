#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

unsigned long long N;

unsigned long long get_sqrt_diff(unsigned long long n){

    unsigned long long sqrtN = floor(sqrt(n)); // 내림한 제곱근을 구함
    if(sqrt(n) == sqrtN) return 0;
    else return (((sqrtN+1) * (sqrtN+1)) - n);

}

int find_N(){
    int cnt=0;

    while(N != 2){
        int diff = get_sqrt_diff(N);
        cnt+=(diff+1);
        N=sqrt(N+diff);
    }

    return cnt;
}

void read_file(){

    int testNum;
    cin >> testNum;

    for(int i=0; i<testNum; i++){
        cin >> N;
        cout << "#" << i+1 << " " << find_N() << endl;
    }

}

int main(int argc, char** argv){
    read_file();
    return 0;
}