#include <iostream>
#include <queue>
using namespace std;

int path1[100], path2[100];
int N; // 길의 총 개수

bool bfs(){
    queue<int> pathQ;
    bool visit[100] = {0, };
    bool found = false;
    pathQ.push(0);

    while(!pathQ.empty()){
        // 큐가 빌때까지 탐사하지 않은 지역을 큐에 넣으며 이동한다.
        int cur = pathQ.front();
        pathQ.pop();
        if(cur == 99) {
            found = true;
            break;
        }
        visit[cur] = true;

        // path1/2[] 배열에 들어있으면서 방문되지 않은 노드를 큐에 삽입
        if(path1[cur] != -1) if(!visit[path1[cur]]) pathQ.push(path1[cur]);
        if(path2[cur] != -1) if(!visit[path2[cur]]) pathQ.push(path2[cur]);
    }

    return found;
}

void init(){
    for(int i=0; i<100; i++){
        path1[i] = path2[i] = -1;
    }
}

void test_print(){
    for(int i=0; i<100; i++){
        cout << path1[i] << " ";
        if((i+1)%10 == 0) cout << endl;
    }

    for(int i=0; i<100; i++){
        cout << path2[i] << " ";
        if((i+1)%10 == 0) cout << endl;
    }
}

int main(){

    int testNum, x, y;
    for(int i=0; i<10; i++){
        cin >> testNum >> N;
        init();

        for(int j=0; j<N; j++){
            cin >> x >> y;
            if(path1[x] == -1) path1[x] = y;
            else path2[x] = y;
        }
        //test_print();        
        cout << "#" << testNum << " " << bfs() << endl;
    }

    return 0;
}