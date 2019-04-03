#include <iostream>

using namespace std;

int N;
int arr[20][20];

void update(){

    int tmpArr[N][N];
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            tmpArr[i][j] = arr[i][j];
        }
    }

}

int main(){

    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> arr[i][j];
        }
    }

    bool possible = true;

    while(possible){
        // 1. 상어 이동

        // 2. 물고기 먹고 상태 갱신 (위치, 크기(누적먹이 포함))

        // 3. possible 갱신
    }

    return 0;
}