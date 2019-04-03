#include <iostream>
#include <vector>
using namespace std;

int L, N; // 경사로의 길이, 배열의 크기
int arr[100][100];

bool chk_slope(vector<int> v){
    int fst = v[0];
    bool same = true;
    int frt, rear;
    for(int i=1; i<v.size(); i++){
        same &= (fst == v[i]);
        frt = v[i-1];
        rear = v[i];
        if(abs(frt-rear) > 1) return false; // 경사의 차이가 1보다 크면 검사종료
    }
    if(same) return true; // 모두 같은 경우 검사종료

    bool slope[100] = {0, }; // 경사로 설치한 곳을 표시

    int cur, prev;
    for(int i=1; i<v.size(); i++){
        cur = v[i];
        prev = v[i-1];

        if(cur > prev) {
            // 증가하는 경우, 이전 L개들이 같은 지 확인
            if(i-L>=0){
                bool chk = true;
                for(int j=i-L; j<=i-1; j++){
                    chk &= ((prev == v[j]) && !slope[j]);
                }
                if(!chk) return false;
                else {
                    for(int j=i-L; j<=i-1; j++) slope[j] = true;
                }
            } else return false;
        } else if(cur < prev) {
            // 감소하는 경우, 이후 L개들이 같은 지 확인            
            if(i+L-1<v.size()){
                bool chk = true;
                for(int j=i; j<i+L; j++){
                    chk &= ((cur == v[j]) && !slope[j]);
                }
                if(!chk) return false; 
                else {
                    for(int j=i; j<i+L; j++) slope[j] = true;
                }
            } else return false;                        
        } else {
            // 같은 경우, 진행
            continue;
        }
    }
    return true;
}

void test_print(vector<int> &v){
    for(int i=0; i<v.size(); i++) cout << v[i] << " ";
    cout << endl;
}

int main(){
    cin >> N >> L;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> arr[i][j];
        }
    }

    int cnt = 0;
    for(int i=0; i<N; i++){
        vector<int> tmpRow, tmpCol;
        for(int j=0; j<N; j++){
            tmpRow.push_back(arr[i][j]);
            tmpCol.push_back(arr[j][i]);
        }
        if(chk_slope(tmpRow)) { // 모든 행의 경사로 검사
            cnt++;
        }
        if(chk_slope(tmpCol)) { // 모든 열의 경사로 검사
            cnt++;
        }
    }

    cout << cnt << endl;
    return 0;
}