#include <iostream>
#include <fstream>
#include <limits.h>
using namespace std;

bool check[16];
int S[16][16];
int t, n, ans;

int abs(int a) {
    return a > 0 ? a : -a;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void recursion(int N, int cnt, int select){

    if (cnt == N) {

        int A = 0, B = 0;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if (i == j) continue;
                if (check[i] && check[j]) A += S[i][j];
                if (!check[i] && !check[j]) B += S[i][j];
            }
        }
        ans = min(ans, abs(A - B));
        return;
    }

    if (select > 0) {
        check[cnt] = true;
        recursion(N, cnt + 1, select - 1);
        check[cnt] = false;
    }
    
    recursion(N, cnt + 1, select);

}

//void start_alg(string fileName){
void start_alg(){
    //fstream cFile(fileName.c_str());
    //cFile >> t;
    cin >> t;

    for(int i=0; i<t; i++){
        //cFile >> n;
        cin >> n;

        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                //cFile >> S[j][k];
                cin >> S[j][k];
            }
        }

        ans = INT_MAX;
        recursion(n, 0, n/2);
        cout << "#" << i+1 << " " << ans << endl; 
    }
}

int main(int argc, char **argv){
    
    //start_alg(argv[1]);
    start_alg();

    return 0;

}

