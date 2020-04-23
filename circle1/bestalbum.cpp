#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

bool cmp (pair<string, int> i, pair<string, int> j) { return (i.second > j.second); }

bool cmp2 (pair<int, int> i, pair<int, int> j) {
    if(i.second == j.second) return (i.first < j.first);
    else return (i.second > j.second);
}

void test_print_vec(vector< pair<int, int> > vp){
    for(int i=0; i<vp.size(); i++){
        cout << vp.at(i).first << " " << vp.at(i).second << endl;
    }
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    // 1. 장르별 플레이 수 계수
    map<string, int> gMap;
    for(int i=0; i<genres.size(); i++){
        gMap[genres.at(i)] += plays.at(i);
    }

    // 2. 장르별 플레이 수 내림차순으로 정렬
    vector< pair<string, int> > gCnt; // 장르별 재생횟수의 총합
    for(map<string, int>::iterator it=gMap.begin(); it!=gMap.end(); ++it){
        gCnt.push_back(pair<string, int>(it->first, it->second));
    }
    sort(gCnt.begin(), gCnt.end(), cmp);

    // 3. 장르 별 맵-벡터 새롭게 만들고 ( 장르별 맵 < 플레이 리스트 벡터 (인덱스, 플레이수) > )
    map< string, vector< pair<int, int> > > mapVec;
    for(int i=0; i<genres.size(); i++){
        mapVec[genres.at(i)].push_back(pair<int, int>(i, plays.at(i)));
    }

    // 4. 장르 별 벡터 정렬하기(높은 플레이수 기준, 플레이수 같으면 인덱스 작은 것 선택)
    for(map<string, vector< pair<int, int> > >::iterator it=mapVec.begin(); it!=mapVec.end(); ++it){
        sort(it->second.begin(), it->second.end(), cmp2);
    }

    // 5. 2에서 정렬된 장르 이름 3의 맵-벡터에 찾아서 2개씩 뽑아내기
    vector<int> answer;
    for(int i=0; i<gCnt.size(); i++){
        if (mapVec[gCnt.at(i).first].size() == 1) {
            // 장르별 플레이리스트가 한 개만 있는 경우
            answer.push_back(mapVec[gCnt.at(i).first].front().first);
        } else if (mapVec[gCnt.at(i).first].size() > 1) {
            // 장르별 플레이리스트가 여러 개 있는 경우
            answer.push_back(mapVec[gCnt.at(i).first].at(0).first);
            answer.push_back(mapVec[gCnt.at(i).first].at(1).first);
        }
    }

    return answer;
}

int main(){return 0;}
