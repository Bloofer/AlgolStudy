#include <iostream>
#include <vector>
using namespace std;

int numComb[9];
char colComb[9];
bool found;
bool visit[9];

bool contains(vector<int> v, int a){
    for(int i=1; i<=3; i++){
        if(numComb[v[i]] == a) return true;
    }
    return false;
}

void test_print(vector< vector<int> > &v){
    for(int i=0; i<3; i++) {
        for(auto j: v[i]) cout << j << " ";
        cout << endl;
    }
}

bool check_comb(vector< vector<int> > &v){
    //test_print(v);
    bool colChk = true;
    for(int i=0; i<3; i++) {
        //cout << v[i].size() << " ";
        char col = colComb[v[i][1]];
        for(int j=0; j<3; j++) {
            colChk &= (colComb[v[i][j+1]] == col);
        }
        if(!colChk) return false;
    }
    cout << endl;

    bool valChk = true;    
    for(int i=0; i<3; i++) {
        bool isSame = true;
        bool isSerial = true;
        int num = numComb[v[i][1]];
        int sum = 0;
        for(int j=0; j<3; j++) {
            isSame &= (numComb[v[i][j+1]] == num);
            sum += numComb[v[i][j+1]];
        }
        isSerial = contains(v[i], sum/3);
        valChk = (isSame || isSerial);
        if(!valChk) return false;
    }

    return (valChk && colChk);
}

void make_comb(vector< vector<int> > v, int idx){
    // base case
    if(found) return;
    for(int i=0; i<3; i++) if(v[i].size()>4) return;
    if(idx==9){
        if(check_comb(v)) {
            test_print(v);
            found = true;}
        return;
    }

    // recursive case
    for(int i=0; i<9; i++){
        for(int j=0; j<3; j++){
            if(!visit[i]){
                vector< vector<int> > tmp = v;
                tmp[j].push_back(i);
                visit[i] = true;
                make_comb(tmp, idx+1);
                visit[i] = false;
            }
        }
    }
}

int main(){
    int T;
    cin >> T;

    for(int i=0; i<T; i++){
        found = false;
        string nums, cols;
        cin >> nums >> cols;
        for(int j=0; j<9; j++){
            numComb[j] = nums.at(j);
            colComb[j] = cols.at(j);
        }

        vector< vector<int> > v = {{-1}, {-1}, {-1}};
        make_comb(v, 0);
        cout << found << endl;
    }

    return 0;
}