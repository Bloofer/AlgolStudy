### 2018.07.23 코딩 스터디  
  
#### SW Expert Academy - 4008. [모의 SW 역량테스트] 숫자 만들기  
  
링크 : [swexpertacademy.com](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeRZV6kBUDFAVH&categoryId=AWIeRZV6kBUDFAVH&categoryType=CODE&&&)  
  
블로그 글 : [Bloofer Blog](https://jmyang.kr/2018/07/23/number/)  
  
**풀이 방법**  
주어진 N개의 숫자 사이에 N-1개의 4종류 사칙연산자 삽입하는 모든 경우의 수 중에서 가장 최대가 되는 조합과 가장 최소가 되는 조합을 찾아 그 차를 구하는 문제이다. 이 문제는 4종류의 사칙연산자의 배치에 따라 계산결과가 달라지는데 연산자 우선순위를 고려하지 않으므로, 좌측부터 연산자를 하나하나씩 넣으면서 탐사하는 DFS 방식으로 쉽게 풀 수 있다.  
  
**구현 내용**  
dfs(int remain[4], int now, int N) : DFS로 숫자와 연산자의 배치방법을 모두 탐사하여 그 중의 최대/최소값을 구하는 함수  
* remain[4] : 인풋으로 주어진 각 연산자의 갯수. 탐사시마다 하나의 계산을 적용할 때 사용된 연산자의 갯수에서 감소시킴.  
* now : 지금까지 계산된 수.  
* N : 지금까지 계산된 인덱스 번호.  
  
