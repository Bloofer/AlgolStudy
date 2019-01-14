#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

typedef struct{
    int tWeight; // 트럭의 무게
    int tStatus; // 트럭의 다리 위에서의 현재 위치
} Truck;

bool check_bridge(int &weight, queue<Truck>& inQ, vector<Truck>& bridge){
    // 다리의 현재상태가 적재불가면 false, 적재가능이면 true 반환
    int totalWeight = 0;
    for(int i=0; i<bridge.size(); i++){
        totalWeight += bridge.at(i).tWeight;
    }
    totalWeight += inQ.front().tWeight;
    return (weight >= totalWeight);
}

void pop_front(vector<Truck>& v){
    if(!v.empty()){
        if(v.size()>1){
            vector<Truck> tmp;
            for(int i=1; i<v.size(); i++){
                tmp.push_back(v.at(i));
            }
            v = tmp;
        } else {
            v.pop_back();
        }
    }
}

void process(vector<Truck>& bridge){
    for(int i=0; i<bridge.size(); i++){
        bridge.at(i).tStatus++;
    }
}

void test_print_bridge(vector<Truck> &bridge){
    for(int i=0; i<bridge.size(); i++){
        cout << bridge.at(i).tStatus << " ";
    }
    cout << endl;
}

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    queue<Truck> inQ;    // 처음에 엔트리에 들어오는 트럭 큐
    vector<Truck> bridge; // 다리를 건너는 중에 있는 트럭 벡터

    for(int i=0; i<truck_weights.size(); i++){
        Truck t;
        t.tStatus = 0;
        t.tWeight = truck_weights.at(i);
        inQ.push(t);
        // 초기에 들어온 트럭 엔트리 inQ에 삽입
    }
    
    int answer = 0; // 트럭이 다리를 지나는데 걸리는 총 시간(클락)
    while(!inQ.empty() || !bridge.empty()){
        if(!bridge.empty() && (bridge.front().tStatus >= bridge_length)){
            Truck brgT = bridge.front();
            pop_front(bridge);
        }

        // 다리의 현재상태 확인하면서 트럭 다리에 삽입
        if(check_bridge(weight, inQ, bridge) && !inQ.empty()){
            // 적재가능시, 트럭 inQ에서 하나 뽑아서 다리에 넣고 클락 진행            
            Truck frtT = inQ.front();
            inQ.pop();
            bridge.push_back(frtT);
        }   // 적재불가시, 그대로 놓고 클락 진행

        process(bridge);
        answer++;
    }
    
    
    return answer;
}

int main(){return 0;}