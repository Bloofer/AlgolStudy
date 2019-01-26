#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> rotate(vector<int> arr){
    // 1. 뒤에 있는 원소 pop back
    // 2. 뒤에서 pop한 원소 앞으로 push front 
    vector<int> tmp;
    tmp.push_back(arr.at(arr.size()-1)); // arr의 맨 마지막 원소 앞에 넣음
    for(int i=0; i<arr.size()-1; i++){
        tmp.push_back(arr.at(i));
    }
    return tmp;
}

bool cmp_arr(vector<int> arrA, vector<int> arrB){
    if(arrA.size() != arrB.size()) return false;
    for(int i=0; i<arrA.size(); i++){
        if(arrA.at(i) != arrB.at(i)) return false; // 원소 하나라도 다르면 false
    }
    return true; // 같으면 true 반환
}

void test_print(vector<int> arr){
    for(int i=0; i<arr.size(); i++) cout << arr.at(i) << " ";
    cout << endl;
}

bool solution(vector<int> arrA, vector<int> arrB) {
    bool answer = true;
    vector<int> rotatedArrA = arrA;

    for(int i=0; i<rotatedArrA.size(); i++){
        if(cmp_arr(rotatedArrA, arrB)) {
            answer = true;
            break;
        } else {
            rotatedArrA = rotate(rotatedArrA);
            answer = false;
        }
    }

    return answer;
}

int main(){return 0;}