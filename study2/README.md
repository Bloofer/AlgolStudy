### 2018.07.09 코딩 스터디  
  
#### SW Expert Academy - 4012. [모의 SW 역량테스트] 요리사  
  
링크 : [swexpertacademy.com](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeUtVakTMDFAVH)  
  
블로그 글 : [Bloofer Blog](https://jmyang.kr/2018/07/12/chef/)  
  
**풀이 방법**  
일단, 주어진 N개의 식재료에 대해서 각각 두개의 요리로 N/2개씩 나누는 방법을 고려한다. N개의 식재료 중 N/2개를 선택하는 모든 조합의 경우의 수를 고려하기 위해, DFS와 Back Tracking 알고리즘을 사용한다. 각각의 조합의 경우에서 나누어진 식재료들의 시너지의 합을 구하고, 매 수행시마다 각 요리의 시너지의 차의 최소값을 선택한다.   

**사용 알고리즘**  
DFS & Back Tracking - N개의 식재료 중 N/2개를 선택하는 방법에 대해서, N/2개를 먼저 선택하면 나머지 N/2개는 따로 선택할 필요가 없이 정해진다. 정해진 모든 조합의 경우의 수로 각 요리의 시너지의 차를 계산하고, 최소값을 갱신한다.  

**구현 함수**  
start alg() - 알고리즘 메인 함수  
recursion() - 재귀 실행 및 시너지 값 평가 함수  
