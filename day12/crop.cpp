#include <iostream>
#include <cmath>
using namespace std;

int N;
int farm[49][49];
int value;

void cal_value(){

    value = 0;

    for(int i=0; i<N; i++){

        int idx = abs((N/2)-i);

        for(int j=idx; j<=(N-idx-1); j++){
            value += farm[i][j];
        }
    }
}

int main(){
    int testNum;
    cin >> testNum;

    for(int i=0; i<testNum; i++){
        cin >> N;
        string crops;
        for(int j=0; j<N; j++){
            cin >> crops;
            for(int k=0; k<N; k++){
                farm[j][k] = crops.at(k) - '0';
            }
        }

        cal_value();
        cout << "#" << i+1 << " " <<  value << endl;
    }

    return 0;
}