#include <string>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

bool has_greater(queue< pair<int, int> > q, pair<int, int> p){
    int qsize = q.size();
    for(int i=0; i<qsize; i++){
        pair<int, int> tmp = q.front();
        q.pop();
        if(p.second < tmp.second) return true;
    }
    return false;
}

int solution(vector<int> priorities, int location) {
    queue< pair<int, int> > spooler; // 전체 대기큐 <고유번호(인덱스), 우선순위>

    // 1. 전체 우선순위 큐에 삽입
    for(int i=0; i<priorities.size(); i++){
        spooler.push(pair<int, int>(i, priorities.at(i)));
    }

    vector<int> ansVec;
    int answer = 0;
    // 2. 큐가 빌때까지 while문 돌면서 조건에 따라 큐에서 원소 하나하나 뺌
    while(!spooler.empty()){
        pair<int, int> tmp = spooler.front();
        spooler.pop();
        // 2.1. 더 높은 우선순위가 있는 지 lookup
        // - 있으면 큐 뒤에 푸쉬
        if(has_greater(spooler, tmp)) spooler.push(tmp); 
        // - 없으면 빼고 그대로 진행
        else {
            ansVec.push_back(tmp.first);
            if(location == tmp.first) answer = ansVec.size();
        }
    }

    return answer;
}

int main(){return 0;}