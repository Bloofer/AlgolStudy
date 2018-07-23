#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

int t, n;
int opNum[4];
int numArr[12];
int minVal, maxVal;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void init(){
    for(int i=0; i<4; i++){
        opNum[i] = 0;
    }
    for(int i=0; i<n; i++){
        numArr[i] = 0;
    }

    maxVal = INT_MIN;
    minVal = INT_MAX;
}

void dfs(int remain[4], int now, int N){
    if (N == n){
        maxVal = max(now, maxVal);
        minVal = min(now, minVal);
        return;
    }

    for(int i=0; i<4; i++){
        if(remain[i] > 0){
            remain[i]--;

            if(i == 0) dfs(remain, now + numArr[N], N + 1);
            else if(i == 1) dfs(remain, now - numArr[N], N + 1);
            else if(i == 2) dfs(remain, now * numArr[N], N + 1);
            else dfs(remain, now / numArr[N], N + 1);

            remain[i]++;
        }
    }
}

void test_print(){
    cout << "n : " << n << endl;
    cout << "ops : ";
    for(int i=0; i<4; i++){
        cout << opNum[i] << " ";
    }
    cout << "\nnums : ";
    for(int i=0; i<n; i++){
        cout << numArr[i] << " ";
    }
    cout << endl;
}

void start_alg(){
    cin >> t;
    
    for(int i=0; i<t; i++){
        init();
        cin >> n;
        for(int j=0; j<4; j++) cin >> opNum[j];
        for(int j=0; j<n; j++) cin >> numArr[j];
        dfs(opNum, numArr[0], 1);
        cout << "#" << (i+1) << " " << maxVal - minVal << endl;
    }

}

int main(int argv, char **argc) {

    start_alg();

    return 0;

}