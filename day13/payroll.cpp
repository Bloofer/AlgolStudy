#include <iostream>
using namespace std;

int N;

int main(){
    int testNum;
    cin >> testNum;

    for(int p=0; p<testNum; p++){
        cin >> N;
        long double sum = 0;

        long double pi, xi;
        for(int i=0; i<N; i++){
            cin >> pi >> xi;
            sum += (pi * xi);
        }

        cout.precision(6);
        cout << "#" << fixed << p+1 << " " << sum;
    }
}