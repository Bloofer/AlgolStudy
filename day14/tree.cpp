#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

char arr[201];
int N;

bool is_num(char c){
    return (c >= '0' && c <= '9');
}

bool has_no_child(char c1, char c2){
    return (arr[c1-'0'] == '-1') && (arr[c2-'0'] == '-1');
}

bool check_valid(vector< vector<char> > &v){
    bool valid = true;
    for(int i=0; i<N; i++){
        if(has_no_child(v[i][2], v[i][3])){
            // 자식이 둘다 없는 경우, Terminal. 숫자이어야 함.
            valid &= is_num(v[i][1]);
        } else {
            // 자식이 하나라도 있는 경우, Non-Terminal. 연산자여야 함.
            valid &= !is_num(v[i][1]);
        }
        //v[i][2] 좌자식
        //v[i][3] 우자식
    }
    return valid;
}

void init(){
    for(int i=0; i<201; i++) arr[i] = '-1';
}

int main(int argc, char** argv){
    ifstream iFile(argv[1]);

    for(int i=0; i<10; i++){
        iFile >> N;
        init();
        vector< vector<char> > inputVec;
        for(int j=0; j<N; j++){
            vector<char> tmp;
            for(int k=0; k<4; k++){
                char a;
                iFile >> a;
                tmp.push_back(a);
            }
            inputVec.push_back(tmp);
            arr[tmp[0]] = tmp[1];
        }
        cout << check_valid(inputVec) << endl;
    }
}