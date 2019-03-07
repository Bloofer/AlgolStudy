#include <iostream>
#include <algorithm>
using namespace std;

int maxVal, swapNum;
string moneyStr;

int get_max(int a, int b){
    return (a > b ? a : b);
}

void swap_num(int idx, int cur){
    if(idx == swapNum){
        // base case
        maxVal = get_max(maxVal, stoi(moneyStr));
        return;
    }

    // cur은 이전에 전달되어 이미 바꿔본 조합 이후로 탐사하기 위함.
    for(int i=cur; i<moneyStr.size()-1; i++){ 
        for(int j=i+1; j<moneyStr.size(); j++){
            if(moneyStr[i] <= moneyStr[j]){ // 바꾸었을 때 더 커지는 경우만 바꾸도록
                swap(moneyStr[i], moneyStr[j]);
                swap_num(idx+1, i);
                swap(moneyStr[j], moneyStr[i]);
            }
        }
    }
}

int main(){
    int testNum;
    cin >> testNum;

    for(int i=0; i<testNum; i++){
        cin >> moneyStr >> swapNum;
        maxVal = stoi(moneyStr);
        swap_num(0, 0);
        cout << "#" << i+1 << " " << maxVal << endl;
    }
}