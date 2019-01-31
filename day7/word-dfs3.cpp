#include <string>
#include <vector>
#include <climits>
#include <iostream>
using namespace std;

vector< vector<int> > wordMap; // 인접한 단어들끼리의 단어차이를 나타내는 맵. 알파벳 차이가 한개이면 1, 그 이상이면 0
vector<string> wordVec;

int minPath = INT_MAX; // 최소값을 업데이트하면서 찾는다.
bool visited[50]; // 인접 단어 배열 탐사시 사용

bool chk_one_alphabet(string s1, string s2){
// 두 단어의 알파벳 차이가 하나이면 true, 아니면 false 반환
    int diff = 0;
    for(int i=0; i<s1.size(); i++){
        if(s1.at(i) != s2.at(i)) diff++;
    }
    return (diff <= 1);
}

void make_map(vector<string> words){
// wordMap 만드는 함수
    for(int i=0; i<words.size(); i++){
        vector<int> tmp;
        for(int j=0; j<words.size(); j++){
            if(chk_one_alphabet(words[i], words[j])) tmp.push_back(1);
            else tmp.push_back(0);
        }
        wordMap.push_back(tmp);
    }
}

int min_val(int a, int b){
    return a < b ? a : b;
}

void dfs(int cur, int length, string target){
// wordMap 탐사하며 가장 짧은 경로 찾아 업데이트 하는 함수
// cur : 현재 탐사중인 단어 번호
    
    // Base Case
    if(wordVec[cur] == target){
        minPath = min_val(minPath, length);
        return;
    }

    // Recursive Case
    for(int i=0; i<wordMap.size(); i++){
        if(i == cur) continue;
        if(wordMap[cur][i]) {
            if(!visited[i]){
                visited[i] = true;
                dfs(i, length+1, target);
                visited[i] = false;
            }
        }
    }
}

int solution(string begin, string target, vector<string> words) {
    // 1. 이차원 배열인 wordMap을 만들고 인접한 단어들끼리의 알파벳 하나 차이를 나타내는지 확인한다.
    make_map(words);
    wordVec = words;

    // 2. 만들어진 wordMap을 이용해 DFS 탐사하고 개 중에 경로의 길이가 가장 짧은 것을 찾는다.
    for(int i=0; i<words.size(); i++){
        if(chk_one_alphabet(begin, words[i])) {
            visited[i] = true;
            dfs(i, 1, target);
            visited[i] = false;
        }
    }

    if(minPath==INT_MAX) return 0;
    else return minPath;
}