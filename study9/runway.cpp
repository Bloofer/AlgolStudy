#include <iostream>
using namespace std;

int map[20][20];
int height[20];
int N, X;

int abs(int n){
    return n > 0 ? n : -n;
}

bool isFlat(int m, int n){
    if(m < 0 || n >= N) return false;

    for(int i=m; i<n; i++){
        if(height[i] != height[i+1]) return false;
    }
    return true;
}

bool flightPossible(){
    for(int i=0; i<N-1; i++){
        if(abs(height[i] - height[i+1]) >= 2) return false;
    }

    bool* upSlope = new bool[N];
    bool* downSlope = new bool[N];

    for(int i=0; i<N; i++){
        upSlope[i] = downSlope[i] = false;
    }

    for(int i=0; i<N-1; i++){
        if(height[i] + 1 == height[i+1]){
            int m = i - X + 1;
            int n = i;

            if(isFlat(m, n)){
                for(int j=m; j<=n; j++){
                    upSlope[j] = true;
                }
            } else {
                return false;
            }
        } else if(height[i] - 1 == height[i + 1]){
            int m = i + 1;
            int n = i + X;

            if(isFlat(m, n)){
                for(int j=m; j<=n; j++){
                    downSlope[j] = true;
                }
            } else {
                return false;
            }
        }
    }

    for(int i=0; i<N; i++){
        if(upSlope[i] && downSlope[i]) return false;
    }

    return true;
}

int main(){

    int T;
    cin >> T;

    for(int tc=0; tc<T; tc++){
        cin >> N >> X;

        for(int j=0; j<N; j++){
            for(int k=0; k<N; k++){
                cin >> map[j][k];
            }
        }

        int rowCnt, colCnt;
        rowCnt = colCnt = 0;

        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                height[j] = map[i][j];
            }
            if(flightPossible()) rowCnt++;
        }

        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                height[j] = map[j][i];
            }
            if(flightPossible()) colCnt++;
        }

        cout << "#" << tc+1 << " " << colCnt + rowCnt << endl;

    }

    return 0;

}