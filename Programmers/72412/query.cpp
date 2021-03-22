#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

vector<int> chkVec[3][2][2][2];

vector<int> solution(vector<string> info, vector<string> query) {
  vector<int> answer;
  int pl, job, pos, sf, score;
  string type;
  // 1. 개발언어/직군/경력/소울푸드를 기준으로 인원 나누어 점수 벡터에 삽입
  for (int p = 0; p < info.size(); p++) {
    istringstream iss(info[p]);
    getline(iss, type, ' ');
    if(type == "cpp") pl = 0; else if(type == "java") pl = 1; else pl = 2;
    getline(iss, type, ' ');
    if(type == "backend") job = 0; else job = 1;
    getline(iss, type, ' ');
    if(type == "junior") pos = 0; else pos = 1;
    getline(iss, type, ' ');
    if(type == "chicken") sf = 0; else sf = 1;
    getline(iss, type, ' ');
    score = stoi(type);
    chkVec[pl][job][pos][sf].push_back(score);
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        for (int l = 0; l < 2; l++) {
          // 2. 체크 벡터 chkVec[3][2][2][2] 인원들의 점수를 정렬
          sort(chkVec[i][j][k][l].begin(), chkVec[i][j][k][l].end());
        }
      }
    }
  }

  for (int p = 0; p < query.size(); p++) {
    istringstream iss(query[p]);
    getline(iss, type, ' ');
    if(type == "-") pl = -1; else if(type == "cpp") pl = 0; else if(type == "java") pl = 1; else pl = 2;
    getline(iss, type, ' '); getline(iss, type, ' ');
    if(type == "-") job = -1; else if(type == "backend") job = 0; else job = 1;
    getline(iss, type, ' '); getline(iss, type, ' ');
    if(type == "-") pos = -1; else if(type == "junior") pos = 0; else pos = 1;
    getline(iss, type, ' '); getline(iss, type, ' ');
    if(type == "-") sf = -1; else if(type == "chicken") sf = 0; else sf = 1;
    getline(iss, type, ' ');
    if(type == "-") score = -1; else score = stoi(type);
    int cnt = 0;
    for (int i = 0; i < 3; i++) {
      if(pl != -1 && pl != i) continue;
      for (int j = 0; j < 2; j++) {
        if(job != -1 && job != j) continue;
        for (int k = 0; k < 2; k++) {
          if(pos != -1 && pos != k) continue;
          for (int l = 0; l < 2; l++) {
            if(sf != -1 && sf != l) continue;
            // 3. lower_bound() 함수로 점수구간 이진 탐색, 쿼리 조건의 점수위치 iterator 찾아 갯수 계수
            auto low = lower_bound(chkVec[i][j][k][l].begin(), chkVec[i][j][k][l].end(), score);
            for (; low != chkVec[i][j][k][l].end(); ++low) cnt++;
          }
        }
      }
    }
    answer.push_back(cnt);
  }

  return answer;
}
