#include <iostream>
using namespace std;

int main(){
    int T;
    int days[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    cin >> T;
    int m, d;
    for(int i=0; i<T; i++){
        cin >> m >> d;
        int daysSum = 0;
        for(int j=0; j<m-1; j++){
            daysSum += days[j];
        }
        cout << "#" << i+1 << " " << ((daysSum + d + 3) % 7) << endl;  
    }

    return 0;
}