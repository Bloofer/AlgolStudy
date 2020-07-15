#include <iostream>
#include <string>
using namespace std;
int T;

int main(){
  cin >> T;
  for (int i = 0; i < T; i++) {
      int cntA, cntB, cntC;
      cntA = cntB = cntC = 0;
      string s;
      cin >> s;

      for (int j = 0; j < s.size(); j++) {
        if(s[j] == 'a') cntA++;
        else if(s[j] == 'b') cntB++;
        else if(s[j] == 'c') cntC++;
      }

      int max = cntA;
      int min = cntA;
      if(max < cntB) max = cntB;
      if(max < cntC) max = cntC;
      if(min > cntB) min = cntB;
      if(min > cntC) min = cntC;

      if(max - min > 1) cout << "#" << i+1 << " " << "NO\n";
      else cout << "#" << i+1 << " " << "YES\n";
  }

  return 0;
}
