#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int T;
int map[10000];
char cmd[10000];
char C[4] = {'D', 'S', 'L', 'R'};

void bfs(int x, int y){
  queue<int> bfsQ;
  bfsQ.push(x);
  bool visit[10000] = {0, };

  while(!bfsQ.empty()){
    int b = bfsQ.front();
    bfsQ.pop();
    if(b == y) return;
    int nx[] = {b*2%10000, b-1, b%1000*10+b/1000, b/10+b%10*1000};
    if (nx[1] < 0) nx[1] = 9999;
    for (int i=0; i<4; i++) {
      if (visit[nx[i]]) continue;
      visit[nx[i]] = true;
      map[nx[i]] = b;
      cmd[nx[i]] = C[i];
      bfsQ.push(nx[i]);
    }
  }
}

int main(){
  cin >> T;
  int x, y;
  for (int i = 0; i < T; i++) {
    cin >> x >> y;
    bfs(x, y);
    vector<char> v;
    while(map[y] != x){
      v.push_back(cmd[y]);
      y = map[y];
    }
    v.push_back(cmd[y]);
    reverse(v.begin(), v.end());
    for(auto vv:v) cout << vv;
    cout << endl;
  }

  return 0;
}
