#include <iostream>
#include <climits>
#include <string>
using namespace std;

int k;
bool visit[10] = {0, };
string maxVal = "";
string minVal = "";

string get_max(string a, string b){
  return a > b ? a : b;
}

string get_min(string a, string b){
  return a < b ? a : b;
}

typedef enum{
  LT, // < : Less Than
  GT  // > : Greater Than
}SIGN;
SIGN signs[9];

bool comp(int a, int b, int idx){
  if(signs[idx] == LT) return a < b;
  else return a > b;
}

void dfs(string s){
  if(s.size() == k+1) {
    if(maxVal == "") maxVal = s;
    else maxVal = get_max(maxVal, s);
    if(minVal == "") minVal = s;
    else minVal = get_min(minVal, s);
  } else {
    for (int i = 0; i < 10; i++) {
      if(!visit[i]){
        char c = i + '0';
        if(s.size() >= 1){
          if(comp(s[s.size()-1]-'0', i, s.size()-1)){
            visit[i] = true;
            dfs(s + c);
            visit[i] = false;
          }
        } else {
          visit[i] = true;
          dfs(s + c);
          visit[i] = false;
        }
      }
    }
  }
}

int main(){
  cin >> k;
  for (int i = 0; i < k; i++) {
    char c;
    cin >> c;
    if (c == '<') signs[i] = LT;
    else if (c == '>') signs[i] = GT;
  }

  dfs("");
  cout << maxVal << endl << minVal << endl;

  return 0;
}
