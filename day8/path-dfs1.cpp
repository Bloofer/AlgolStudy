#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

multimap<string, string> pathMap; // (dept -> dest)의 여러개의 키를 가지는 경로맵
vector<string> pathVec; // 경로벡터
typedef multimap<string,string>::iterator mmit;
int ticketNum; // 항공권 수

bool cmp_str(vector<string> &v1, vector<string> &v2){
    if(v1[0] < v2[0]) return true;
    else if(v1[0] == v2[0]){
        if(v1[1] < v2[1]) return true;
        else return false;
    }
    else return false;
}

void dfs(vector<string> v, string dept){
    pair<mmit, mmit> ret;
    ret = pathMap.equal_range(dept);

    if(ret.first==ret.second){
        // 해당 dept 맵의 값의 아무것도 없는 경우
        return;
    }

    v.push_back(dept);
    if(v.size()==ticketNum+1) {
        pathVec = v;
        //pathVec.push_back(ret.first->second);
        return;
    }
    for(mmit it=ret.first; it!=ret.second; ++it){
        dfs(v, it->second); // TODO: 여기서 방문된 노드 중복 방문하지 않도록 고쳐야 함
    }

}

vector<string> solution(vector<vector<string>> tickets) {
    // 0. 멀티맵 생성전 알파벳 순으로 정렬해놓기 & 항공권 수 세팅
    sort(tickets.begin(), tickets.end(), cmp_str);
    ticketNum = tickets.size();

    // 1. 경로맵 생성
    for(auto t:tickets){
        pathMap.insert(pair<string, string>(t[0], t[1]));
    }

    // 2. DFS 탐사 시작
    dfs(vector<string>(), "ICN");

    return pathVec;
}