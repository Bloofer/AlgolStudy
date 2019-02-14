#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int cnt1, cnt2, cnt3, cnt4; // (), [], {}, <> 짝 갯수
string chars;
int charCnt;

bool start_alg(){
    cnt1 = cnt2 = cnt3 = cnt4 = 0;
    for(int i=0; i<charCnt; i++){
        if(chars.at(i) == '(') cnt1++;
        else if(chars.at(i) == '[') cnt2++;
        else if(chars.at(i) == '{') cnt3++;
        else if(chars.at(i) == '<') cnt4++;
        else if(chars.at(i) == ')') cnt1--;
        else if(chars.at(i) == ']') cnt2--;
        else if(chars.at(i) == '}') cnt3--;
        else if(chars.at(i) == '>') cnt4--;
    }
    return !(cnt1 || cnt2 || cnt3 || cnt4); // 괄호 짝 갯수가 맞지않으면 0, 맞으면 1
}

void read_file(){
    for(int i=0; i<10; i++){
        cin >> charCnt;
        cin >> chars;
        cout << "#" << i+1 << " " << start_alg() << endl;
    }
}

int main(int argc, char** argv){
    read_file();
    return 0;
}