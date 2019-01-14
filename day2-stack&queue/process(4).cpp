#include <string>
#include <vector>
#include <iostream>
using namespace std;

typedef struct{
    int status;     // 현재 프로세스 진행률
    int speed;      // 해당 프로세스 진행속도
    bool finished;  // 해당 프로세스 완료여부
} Prog;

void process(vector<Prog> &progs){
// 한 클락씩 모든 미종료 작업에 대해서 speed 만큼 증가
    for(int i=0; i<progs.size(); i++){
        if(!progs.at(i).finished){
            progs.at(i).status += progs.at(i).speed;
        }
    }
}

bool check_progs(Prog &p1){
// 작업의 종료 조건 확인하여 종료 가능시 true 반환
    return (p1.status >= 100);
}

void update_progs(vector<Prog> &progs, bool &allFinished, vector<int> &answer){
// 작업 중 종료되는 작업 조건 확인후 업데이트(미종료->종료)
    bool check = true;
    int cnt = 0;
    for(int i=0; i<progs.size(); i++){
        if(!progs.at(i).finished){
            if(check_progs(progs.at(i))) {
                progs.at(i).finished = true;
                cnt++;
                if(i==progs.size()-1) {
                    answer.push_back(cnt);
                    allFinished = true;
                }
            }
            else {
                if(cnt>0) answer.push_back(cnt);
                return;
            }
        }
    }
}

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<Prog> progs;
    for(int i=0; i<progresses.size(); i++){
        Prog p;
        p.status = progresses.at(i);
        p.speed = speeds.at(i);
        p.finished = false;
        progs.push_back(p);
    }

    bool allFinished = false; // 모든 작업이 끝났는지를 체크하는 변수
    vector<int> answer;
    while(!allFinished){
        // 모든 작업이 종료되지 않는 동안 반복
        process(progs);
        update_progs(progs, allFinished, answer);
    }
    
    return answer;
}

int main(){return 0;}