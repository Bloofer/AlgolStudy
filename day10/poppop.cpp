#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int arr[301][301]; // 지뢰찾기 지도 *:1 .:0
int map[301][301]; // 각 셀의 인접 지뢰수가 계산된 지도 (지뢰=-1)
int N; // 지도의 크기 N * N
int click[301][301]; // 지도가 클릭되었는지 확인하는 맵 (1:클릭됨, 0:클릭안됨)
int clicks;
int dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1}; // ↖ ↑ ↗ → ↘ ↓ ↙ ← 순서 
int dy[8] = {-1, -1, -1, 0, 1, 1, 1, 0}; //0 1 2 3 4 5 6 7 왼쪽 상단부터 시계방향 

bool is_range(int x, int y){
    // x, y가 지도 좌표에 해당되는지 확인하는 함수
    if( x<0 || x>N-1 || y<0 || y>N-1 ) return false;
    else return true;
}

void click_zeros(){
    // 지도에서 0들을 BFS로 연쇄적으로 클릭하는 함수
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(click[i][j] || (map[i][j]!=0)) continue; // 클릭되었거나, 0이 아니면 스킵
            
            queue< pair<int,int> > zeroQ; // 0의 파핑이 연쇄되는 큐
            zeroQ.push(pair<int, int>(i, j));
            //click[i][j] = 1;
            clicks++;
            while(!zeroQ.empty()){
                pair<int, int> idxP = zeroQ.front();
                zeroQ.pop();
                int x = idxP.first;
                int y = idxP.second;

                if(map[x][y]==-1 || click[x][y]) continue;
                if(map[x][y]>0) {
                    click[x][y] = 1;
                    continue;
                } else click[x][y] = 1;

                for(int p=0; p<8; p++){
                    if(is_range(x+dx[p], y+dy[p])) zeroQ.push(pair<int, int>(x+dx[p], y+dy[p]));
                }
            }
        }
    }    
}

void eval_map(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(arr[i][j]) map[i][j] = -1;
            else {
                int mine = 0;
                //cout << "(" << i << ", " << j << ") : ";
                for(int p=0; p<8; p++){
                    if(is_range(i+dx[p], j+dy[p])) {
                        //cout << "(" << i+dx[p] << ", " << j+dy[p] << ") ";
                        mine += arr[ i+dx[p] ][ j+dy[p] ];
                        }
                }
                //cout << endl;
                map[i][j] = mine;
            }
        }
    }
}

void init(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            click[i][j] = 0;
            map[i][j] = 0;
        }
    }
}

//void read_file(string fileName){
void read_file(){
    //ifstream iFile(fileName.c_str());
    
    int T;
    //iFile >> T;
    cin >> T;
    for(int i=0; i<T; i++){
        //iFile >> N;
        cin >> N;
        init();
        clicks = 0;
        for(int j=0; j<N; j++){
            for(int k=0; k<N; k++){
                char c;
                //iFile >> c;
                cin >> c;
                if(c=='*') arr[j][k] = 1;
                else arr[j][k] = 0;
            }
        }
        eval_map();
        click_zeros();

        int unclicked = 0;
        
        for(int j=0; j<N; j++){
            for(int k=0; k<N; k++){
                if(!click[j][k] && map[j][k]>0) unclicked++;
            }
        }
        /* for(int j=0; j<N; j++){
            for(int k=0; k<N; k++) cout << arr[j][k] << " ";
            cout << endl;
        }
        for(int j=0; j<N; j++){
            for(int k=0; k<N; k++) cout << map[j][k] << " ";
            cout << endl;
        } */
        cout << "#" << i+1 << " " << clicks+unclicked << endl;
    }

}

int main(int argc, char** argv){
    //read_file(argv[1]);
    read_file();
    return 0;
}