#include <iostream>
using namespace std;
int T, N, M;

typedef struct{
  int t, a, b;
}ARGS;
ARGS argArr[51];
int xArr[51];
long long fArr[51];

unsigned long long get_f(int n, int x){
  // f() 함수를 구하는 식
  if(n == 0) return 1;
  else if(n == 1) return x % 998244353;
  else {
    if(argArr[n].t == 1) return (get_f(argArr[n].a, x) + get_f(argArr[n].b, x)) % 998244353;
    else if(argArr[n].t == 2) return (argArr[n].a * get_f(argArr[n].b, x)) % 998244353;
    else return ( (get_f(argArr[n].a, x) % 998244353) * (get_f(argArr[n].b, x) % 998244353) ) % 998244353;
  }
}

void init(){
  for (int i = 0; i <= N; i++) {
    fArr[i] = 0;
    argArr[i].t = 0;
    argArr[i].a = 0;
    argArr[i].b = 0;
  }
}

int main(){
  cin >> T;
  for (int j = 0; j < T; j++) {
    cin >> N;
    init();
    for (int i = 2; i <= N; i++) {
      ARGS tmpArg;
      cin >> tmpArg.t >> tmpArg.a >> tmpArg.b;
      argArr[i].t = tmpArg.t;
      argArr[i].a = tmpArg.a;
      argArr[i].b = tmpArg.b;
    }
    cin >> M;
    cout << '#' << j + 1 << ' ';
    for (int i = 0; i < M; i++) {
      int x;
      cin >> x;
      xArr[i] = x;
      fArr[0] = 1;
      fArr[1] = x;
      for (int k = 2; k <= N; k++) {
        if(argArr[k].t == 1) fArr[k] = fArr[argArr[k].a] + fArr[argArr[k].b];
        else if(argArr[k].t == 2) fArr[k] = argArr[k].a * fArr[argArr[k].b];
        else if(argArr[k].t == 3) fArr[k] = fArr[argArr[k].a] * fArr[argArr[k].b];
        fArr[k] %= 998244353;
      }
      cout << fArr[N] << " ";
    }
    cout << endl;
  }

  return 0;
}
