#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(vector<int> heights) {
    vector<int> answer;
    for(int i=heights.size()-1; i>=0; i--){
        for(int j=i-1; j>=0; j--){
            if(heights.at(j) > heights.at(i)) {
                answer.push_back(j+1);
                break;
            } else {
                if(j==0) answer.push_back(0);
            }
        }
    }
    answer.push_back(0);
    reverse(answer.begin(), answer.end());

    return answer;
}