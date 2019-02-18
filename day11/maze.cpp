#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

int arr[100][100];
bool able;
pair<int, int> start; // 시작 위치

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1}; // 상하좌우 이동 배열

bool valid(int x, int y){ // 좌표의 유효성 체크
    if(x<0 || y<0 || x>99 || y>99) return false;
    else return true;
}

void bfs(){
    int visit[100][100] = {0, };

    queue< pair<int, int> > posQ; // 좌표 큐, BFS 탐사에 사용할 것임
    posQ.push(start);
    
    while(!posQ.empty()){
        pair<int, int> idx = posQ.front();
        posQ.pop();
        if(visit[idx.first][idx.second]) continue;
        else visit[idx.first][idx.second] = 1;

        for(int i=0; i<4; i++){
            if(valid(idx.first+dx[i], idx.second+dy[i])){ // 배열 좌표가 유효하면서
                if(!visit[idx.first+dx[i]][idx.second+dy[i]]){ // 경로가 탐사되지 않았고
                    if(arr[idx.first+dx[i]][idx.second+dy[i]]==3){
                        // 목적지를 찾은 경우에는 탐사종료
                        able = true;
                        return;
                    } else if(arr[idx.first+dx[i]][idx.second+dy[i]]==0){
                        // 탐사가능한 경로를 찾은 경우에는 큐에 삽입
                        posQ.push(pair<int, int>(idx.first+dx[i], idx.second+dy[i]));
                    } else if(arr[idx.first+dx[i]][idx.second+dy[i]]==1){
                        // 벽이면 못탐사함
                        continue;
                    }
                }
            }
        }
    }
}

//void read_file(string fileName){
void read_file(){
    //ifstream iFile(fileName.c_str());

    int testNum;
    for(int i=0; i<10; i++){
        //iFile >> testNum;
        cin >> testNum;
        able = false;
        
        
        for(int j=0; j<100; j++){
            string arrs;     
            //iFile >> arrs;
            cin >> arrs;
            for(int k=0; k<100; k++){
                arr[j][k] = arrs.at(k)-'0';
                if(arr[j][k] == 2) start = pair<int, int>(j, k);
            }
        }

        bfs();
        cout << "#" << testNum << " " << able << endl;
    } 
}

int main(int argc, char** argv){
    //read_file(argv[1]);
    read_file();
    return 0;
}