#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int dir; // 0:상, 1:하, 2:좌, 3:우
int N;
int arr[20][20]; // 게임의 보드판

void push_zeros(vector<int> &v){
    // 1. 전처리. 먼저 0없애서 전부 밀어 붙이기
    vector<int> tmp;
    
    for(auto i: v) { if(i!=0) tmp.push_back(i); }
    int tSize = tmp.size();
    for(int i=0; i<(v.size()-tSize); i++) tmp.push_back(0);

    v = tmp;
}

vector<int> push(vector<int> v){
// 가로 배열, 왼쪽 밀기 기준. 다른 방향/세로 배열은 뒤집어서 함수에 넣어야함

    push_zeros(v);

    vector<int> tmp;
    for(int i=0; i<v.size(); i++) tmp.push_back(0);

    int cur = v.front(); // 같은 수를 확인할 변수
    int frt = 0;
    int end = frt;
    for(int i=0; i<v.size(); i++) {
        // 2. 같은 수를 가지는 idx까지 모음
        if(v[i]==0) break;

        if(i==N-1){
            if(frt==end) {
                tmp[i] = v[i];
                break; // 이경우 그냥 끝냄
            } else {
                // 지금까지 모은 frt end 전부 합치기
                int isOdd = (end - frt + 1) % 2;
                int idxGap;
                if(isOdd){
                    // 같은 수의 갯수가 홀수일때
                    idxGap = (end - frt - 2) / 2;
                    for(int j=frt; j<=frt+idxGap; j++){
                        tmp[j] = 2 * v[j];
                    }
                    tmp[frt+idxGap+1] = v[frt+idxGap+1];
                } else{
                    // 같은 수의 갯수가 짝수일때
                    idxGap = (end - frt - 1) / 2;
                    for(int j=frt; j<=frt+idxGap; j++){
                        tmp[j] = 2 * v[j];
                    }
                }
            }
        } else {
            if(v[i] != v[i+1] && frt == end) { 
                tmp[i] = v[i];
                frt = end = i+1;
            } else if(v[i] != v[i+1] && frt != end){
                // 지금까지 모은 frt에서 end까지의 인덱스 전부 합치고 계산
                // 지금까지 모은 frt end 전부 합치기
                int isOdd = (end - frt + 1) % 2;
                int idxGap;
                if(isOdd){
                    // 같은 수의 갯수가 홀수일때
                    idxGap = (end - frt - 2) / 2;
                    for(int j=frt; j<=frt+idxGap; j++){
                        tmp[j] = 2 * v[j];
                    }
                    tmp[frt+idxGap+1] = v[frt+idxGap+1];
                } else{
                    // 같은 수의 갯수가 짝수일때
                    idxGap = (end - frt - 1) / 2;
                    for(int j=frt; j<=frt+idxGap; j++){
                        tmp[j] = 2 * v[j];
                    }
                }
                frt = end = i+1;
            } else if(v[i] == v[i+1]){
                end = i+1; // TODO: 마지막 인덱스에 대한 처리 고려
            }
        }
    }

    push_zeros(tmp);
    return tmp;
}

void move(){
    int ans[20][20] = {0, };

    if(dir==0){
        // 위쪽으로 미는 경우
        for(int i=0; i<N; i++){
            vector<int> v;
            for(int j=0; j<N; j++) v.push_back(arr[j][i]);
            vector<int> pushedV = push(v);
            for(int j=0; j<N; j++) ans[j][i] = pushedV[j];
        }
    } else if(dir==1){
        // 아래쪽으로 미는 경우
        for(int i=0; i<N; i++){
            vector<int> v;
            for(int j=N-1; j>=0; j--) v.push_back(arr[j][i]);
            vector<int> pushedV = push(v);
            for(int j=N-1; j>=0; j--) ans[j][i] = pushedV[N-j-1];
        }
    } else if(dir==2){
        // 좌측으로 미는 경우
        for(int i=0; i<N; i++){
            vector<int> v;
            for(int j=0; j<N; j++) v.push_back(arr[i][j]);
            vector<int> pushedV = push(v);
            for(int j=0; j<N; j++) ans[i][j] = pushedV[j];
        }
    } else if(dir==3){
        // 우측으로 미는 경우
        for(int i=0; i<N; i++){
            vector<int> v;
            for(int j=N-1; j>=0; j--) v.push_back(arr[i][j]);
            vector<int> pushedV = push(v);
            for(int j=N-1; j>=0; j--) ans[i][j] = pushedV[N-j-1];
        }
    }

    for(int j=0; j<N; j++){
        for(int k=0; k<N; k++){
            cout << ans[j][k] << " ";
        }
        cout << endl;
    }      

}

//void read_file(string fileName){
void read_file(){
    //ifstream iFile(fileName.c_str());

    int testNum;
    //iFile >> testNum;
    cin >> testNum;
    for(int i=0; i<testNum; i++){
        //iFile >> N;
        cin >> N;
        string direction;
        //iFile >> direction;
        cin >> direction;
        if(direction == "up") dir = 0;  
        else if(direction == "down") dir = 1;
        else if(direction == "left") dir = 2;
        else if(direction == "right") dir = 3;

        for(int j=0; j<N; j++){
            for(int k=0; k<N; k++){
                //iFile >> arr[j][k];
                cin >> arr[j][k];
            }
        }      

        cout << "#" << i+1 << endl;
        move();
    }

}

int main(int argc, char** argv){
    //read_file(argv[1]);
    read_file();
    return 0;
}