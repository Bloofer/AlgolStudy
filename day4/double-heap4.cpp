#include <string>
#include <vector>
#include <deque>
#include <iostream>
using namespace std;

void test_print_dq(deque<int> &d){
    for(int i=0; i<d.size(); i++){
        cout << d[i] << " ";
    }
    cout << endl;
}

vector<int> solution(vector<string> operations) {

    deque<int> doubleQ; // 앞으로는 최대, 뒤로는 최소값을 가지는 이중 우선순위 큐

    for(int i=0; i<operations.size(); i++){
        test_print_dq(doubleQ);
        if(operations.at(i).substr(0,1) == "I"){
            int val = stoi(operations.at(i).substr(2));
            cout << val << endl;
            if(doubleQ.size() == 0){
                // 비어있으면 그냥 넣음
                doubleQ.push_back(val);
            } else if(doubleQ.size() == 1){  
                // 원소 하나 있는 경우, 안에 있는 게 더 크면 뒤로, 작으면 앞으로              
                if(doubleQ.front() > val) doubleQ.push_back(val);
                else doubleQ.push_front(val);
            } else {
                // 두개 이상부터는 중위수(median)를 기준으로 중위수보다 크면 앞에서부터 넣고, 작으면 뒤에서부터 넣는다.
                // 여기서 삽입시, 정렬된 형태를 유지하기 위해 크기를 비교해가며 앞에는 자기보다 큰, 뒤에는 자기보다 작은 원소가 되도록 스왑한다.
                if(doubleQ.at(doubleQ.size()/2) > val) {
                    // 중위수보다 큰 경우, 앞에서 부터 삽입
                    doubleQ.push_front(val);
                    for(int j=0; j<doubleQ.size()-1; j++){
                        if(doubleQ[j] < doubleQ[j+1]) swap(doubleQ[j], doubleQ[j+1]);
                        else break;
                    }
                } else {
                    // 중위수보다 작은 경우, 뒤에서부터 삽입
                    doubleQ.push_back(val);
                    for(int j=doubleQ.size()-1; j>0; j++){
                        if(doubleQ[j] > doubleQ[j-1]) swap(doubleQ[j], doubleQ[j-1]);
                        else break;
                    }
                }
            }

        } else if(operations.at(i) == "D 1"){
            // 최대값 제거
            cout << "max out" << endl;
            if(doubleQ.empty()) break;
            doubleQ.pop_front();
        } else if(operations.at(i) == "D -1"){
            // 최소값 제거
            cout << "min out" << endl;
            if(doubleQ.empty()) break;
            doubleQ.pop_back();
        }
    }

    vector<int> answer;
    if(doubleQ.size() == 0) answer = {0,0};
    else if(doubleQ.size() == 0) answer = {doubleQ.front(),doubleQ.front()};
    else answer = {doubleQ.front(),doubleQ.back()};
    
    return answer;
}

int main(){
    vector<string> v = {"I -45", "I 653", "D 1", "I -642", "I 45", "I 97", "D 1", "D -1", "I 333"};
    solution(v);
    return 0;
}