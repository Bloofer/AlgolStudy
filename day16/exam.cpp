#include <iostream>
using namespace std;

long long int N, B, C;

int main(){

    cin >> N;
    long long int ans = N;
    long long int a[N]; // 응시자 수

    for(int i=0; i<N; i++){
        cin >> a[i];
    }
    cin >> B >> C;

    for(int i=0; i<N; i++){
        a[i] -= B; // NOTE: unsigned 타입을 사용하면 여기서 integer underflow 발생. 
                   // signed 타입 사용하기.
        if(a[i] <= 0) continue;
        else {
            long long int qt = a[i]/C;
            ans+=qt;
            if((a[i]%C)!=0) ans++; 
        }
    }
    cout << ans << endl;

    return 0;
}