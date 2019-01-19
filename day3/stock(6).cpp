#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer;
    for(int i=0; i<prices.size(); i++){
        int cnt = 0;
        if(i<prices.size()-1){
            // 마지막이 아닐때 비교 진행
            for(int j=i+1; j<prices.size(); j++){
                if(prices.at(i) <= prices.at(j)) cnt++;
                else { 
                    cnt++;
                    break;
                }
            }
        }
        answer.push_back(cnt);
    }
    return answer;
}