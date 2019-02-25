#include <iostream>
using namespace std;

int nums[100];
bool sums[10001];
int N;

int eval(){
    int cnt = 0;
    for(int i=0; i<=10000; i++){
        if(sums[i]) {
            cnt++;
            sums[i] = false;
        }
    }
    return cnt;
}

int main(){
    int T;
    cin >> T;
    for(int i=0; i<T; i++){  
        cin >> N;
        int visit[100] = {0, };
        int sum = 0;
        for(int j=0; j<N; j++) {
            cin >> nums[j];
            sum += nums[j];
        }

        sums[0] = true;
        for(int j=0; j<N; j++){
            for(int k=sum; k>=0; k--){
                if(sums[k]) sums[k + nums[j]] = true;
            }
        }
        
        cout << "#" << i+1 << " " << eval() << endl;
    }

    return 0;
}