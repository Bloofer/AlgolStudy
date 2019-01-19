#include <string>
#include <vector>

using namespace std;

int calculate_sup(pair<int, int> p, int d){
    // 새롭게 계산하는 값은 supplies - (기준일(d) - dates) (이전 인덱스만큼 기다리게 하므로 맨 뒤 기준으로 인덱스 빼기)
    return p.second - (d - p.first);
}

pair<int, int> get_best(vector< pair<int, int> > &v, int baseDate){
    // 현재날짜를 기준으로 가장 이득이 되는 순서의 값 가져오기 
    pair<int, int> bstP; // 가장 이득이 되는 순서의 값

    bstP = v.front();
    for(int i=1; i<v.size(); i++){
        if(calculate_sup(v.at(i), baseDate) > calculate_sup(bstP, baseDate)) bstP = v.at(i);
        // 더 이득이 되는 배급일 찾으면 업데이트
    }

    return bstP;
}

int solution(int stock, vector<int> dates, vector<int> supplies, int k) {

    int cur = 0; // 현재 진행 날짜(인덱스)
    int pos = 0; // dates/supplies 배열 인덱스 TODO: 인덱스 대신 날짜 숫자로 바꾸기?

    vector< pair<int, int> > wdw; // 배급 일내 배열 저장 (dates, supplies)

    while(cur < k){
        // k일 지나기전까지 반복
        cur += stock;

        // 최근 dates 배열 중 최대 계산
        // pos ~ dates[i]가 cur보다 작은 최대 값
        wdw.clear();
        for(int i=pos; i<dates.size(); i++){
            if(dates.at(i) > cur) break; // 배급량이 떨어질때까지의 저정량만 보기 위해
            wdw.push_back(pair<int, int>(dates.at(i), supplies.at(i)));
        }        

        pair<int, int> p = get_best(wdw, pos);
        // 현재 기준 배급량 떨어질때까지 가장 최선의 배급 선택
        // 날짜 / 배급량 페어
        stock = p.second;

        // 계산 후 pos 업데이트

    }


    int answer = 0;
    return answer;
}