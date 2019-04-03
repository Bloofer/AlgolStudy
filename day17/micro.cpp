#include <iostream>
#include <climits>
using namespace std;

long long minDay;
long long maxIdx;
long long s, t, a, b;

long long min_val(long long a, long long b){
    return a < b ? a : b;
}

long long max_val(long long a, long long b){
    return a > b ? a : b;
}

void dfs(long long sum, long long days){
    if(sum > t) return;
    else if(sum == t) minDay = min_val(minDay, days);

    dfs(sum+a, days+1);
    dfs(sum*b, days+1);
}

int main(){
    int T;
    cin >> T;

    for(int i=0; i<T; i++){
        cin >> s >> t >> a >> b;
        minDay = INT_MAX;


        dfs(s, 0);
        cout << "#" << i+1 << " ";
        if(minDay == INT_MAX) cout << -1 << endl;
        else cout << minDay << endl;
    }

    return 0;
}