#include <iostream>
#include <fstream>
using namespace std;

int N; // 테스트케이스 길이
int arr[1000]; // 건물 배열

int min(int a, int b){
    return a < b ? a : b;
}

bool valid(int x){
// 건물 배열 인덱스 확인함수    
    if(x < 2 || x > N-3) return false; // 양끝 두개는 건물 X
    else if(arr[x] == 0) return false; // 건물이 없는 경우 X
    return true;
}

int start_alg(){
    int totalViews = 0;

    for(int i=0; i<N; i++){
        int height = arr[i];
        int views = arr[i];
        for(int j=0; j<5; j++){
            if(j==2) continue; // 자기자신은 빼고
            if(height == 0) continue;
            if(valid(i+j-2)){
                if(arr[i+j-2] >= height) {
                    views = 0;
                    continue; // 옆 건물이 더 크면 조망권 X
                }
                else{
                    views = min(views, height - arr[i+j-2]); // 가능한 조망권 업데이트
                }
            } 
        }
        totalViews += views;
    }
    return totalViews;
}

void read_file(){
    for(int i=0; i<10; i++){
        cin >> N;
        for(int j=0; j<N; j++){
            cin >> arr[j];
        }
        cout << "#" << i+1 << " " << start_alg() << endl;

    }
}

int main(int argc, char** argv){
    read_file();
    return 0;
}