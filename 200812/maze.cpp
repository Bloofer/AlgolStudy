#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <queue>
using namespace std;

int arr[5][5][5] = {0, };
int dx[6] = {0, 0, 1, 0, 0, -1};
int dy[6] = {0, 1, 0, 0, -1, 0};
int dz[6] = {1, 0, 0, -1, 0, 0};
int minVal = INT_MAX;
bool dfsVisit[5] = {0, };

typedef struct{
  int x, y, z;
  int len;
}Q_ELEM;

int get_min(int a, int b){
  return a < b ? a : b;
}

void turn_right(vector< vector<int> > &vec){
  vector< vector<int> > tmpVec = vec;

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      vec[j][4-i] = tmpVec[i][j];
    }
  }
}

bool available(int x, int y, int z){
  return x < 5 && y < 5 && z < 5;
}

void bfs_maze(vector< vector< vector<int> > > &tmpArr){
  queue<Q_ELEM> bfsQ;
  bool visit[5][5][5] = {0, };

  Q_ELEM elem;
  elem.x = elem.y = elem.z = elem.len = 0;
  bfsQ.push(elem);

  while(!bfsQ.empty()){
    Q_ELEM topElem = bfsQ.front();
    bfsQ.pop();

    if(topElem.x == 4 && topElem.y == 4 && topElem.z == 4){
      minVal = get_min(minVal, topElem.len);
    }

    for (int i = 0; i < 6; i++) {
      int nextX = topElem.x + dx[i];
      int nextY = topElem.y + dy[i];
      int nextZ = topElem.z + dz[i];
      if(available(nextX, nextY, nextZ) && tmpArr[nextX][nextY][nextZ] != 0 && !visit[nextX][nextY][nextZ]){
        Q_ELEM pushElem;
        pushElem.x = nextX;
        pushElem.y = nextY;
        pushElem.z = nextZ;
        pushElem.len = topElem.len+1;
        bfsQ.push(pushElem);
        visit[nextX][nextY][nextZ] = true;
      }
    }
  }
}

void replace_vec(int a, vector< vector<int> > &vec, vector< vector< vector<int> > > &tmpArr){
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      tmpArr[a][i][j] = vec[i][j];
    }
  }
}

void get_vec(int a, vector< vector<int> > &vec, vector< vector< vector<int> > > &tmpArr){
  for (int i = 0; i < 5; i++) {
    vector<int> tmpV;
    for (int j = 0; j < 5; j++) {
      tmpV.push_back(tmpArr[a][i][j]);
    }
    vec.push_back(tmpV);
  }
}

void start_maze(vector< vector< vector<int> > > &tmpArr){
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      vector< vector<int> > tmpV;
      get_vec(i, tmpV, tmpArr);
      turn_right(tmpV);
      for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
          for (int k = 0; k < 5; k++) {
            cout << tmpArr[i][j][k] << " ";
          }
          cout << endl;
        }
        cout << endl;
      }
      int s;
      cin >> s;
      replace_vec(i, tmpV, tmpArr);
      bfs_maze(tmpArr);
    }
  }
}

void dfs_layer(string s){
  if(s.size() == 5){
    cout << s << endl;
    vector< vector< vector<int> > > tmpArr;
    for (int i = 0; i < 5; i++) {
      vector< vector<int> > tmp2dVec;
      for (int j = 0; j < 5; j++) {
        vector<int> tmp1dVec;
        for (int k = 0; k < 5; k++) {
          tmp1dVec.push_back(arr[s.at(i) - '1'][j][k]);
        }
        tmp2dVec.push_back(tmp1dVec);
      }
      tmpArr.push_back(tmp2dVec);
    }


    start_maze(tmpArr);
  } else {
    for (int i = 0; i < 5; i++) {
      if(!dfsVisit[i]) {
        string nextC(1, i + '1');
        dfsVisit[i] = true;
        dfs_layer(s + nextC);
        dfsVisit[i] = false;
      }
    }
  }
}

int main(){
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 5; k++) {
        cin >> arr[i][j][k];
      }
    }
  }

  dfs_layer("");

  // for (int i = 0; i < 5; i++) {
  //   for (int j = 0; j < 4; j++) {
  //     vector< vector<int> > tmpV;
  //     get_vec(i, tmpV);
  //     turn_right(tmpV);
  //     replace_vec(i, tmpV);
  //     bfs_maze();
  //   }
  // }

  if(minVal == INT_MAX) cout << -1 << endl;
  else cout << minVal << endl;

  return 0;
}
