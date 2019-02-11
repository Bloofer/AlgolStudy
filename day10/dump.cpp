#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> boxes;
int dumpNum;

void push_box(){
    // 1. 앞에서 밀기
    int i=0;
    while(i<99 && (boxes[i]>boxes[i+1])){
        int tmp = boxes[i];
        boxes[i] = boxes[i+1];
        boxes[i+1] = tmp;
        i++;
    }
    
    // 2. 뒤에서 밀기
    i=99;
    while(i>0 && (boxes[i]<boxes[i-1])){
        int tmp = boxes[i];
        boxes[i] = boxes[i-1];
        boxes[i-1] = tmp;
        i--;
    }
}

void start_dump(){
    // 정렬을 처음에 한번 해놓고, 덤프시킬때마다 앞뒤로 밀어 정렬을 유지시킨다.
    sort(boxes.begin(), boxes.end());

    for(int i=0; i<dumpNum; i++){
        if(boxes[99]-boxes[0] <= 1) return;
        boxes[0]++;
        boxes[99]--;
        push_box();
    }
}

void read_file(){
    for(int i=0; i<10; i++){
        cin >> dumpNum;
        for(int j=0; j<100; j++){
            int n;
            cin >> n;
            boxes.push_back(n);
        }
        start_dump();
        cout << "#" << i+1 << " " << boxes[99] - boxes[0] << endl;
        boxes.clear();
    }
}

int main(int argc, char** argv){
    read_file();
    return 0;
}