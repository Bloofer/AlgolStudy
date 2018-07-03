### 2018.07.02 코딩 스터디  
  
#### SW Expert Academy - 4013. [모의 SW 역량테스트] 특이한 자석  
  
링크 : [swexpertacademy.com](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeV9sKkcoDFAVH&)  
  
블로그 글 : [Bloofer Blog](https://jmyang.kr/2018/07/03/magnet/)  
  
**풀이 방법**  
인접한 자석들의 인력(서로 극이 다른 지) 작용 여부를 확인하여, 자석의 회전이 미치는 영향의 범위를 계산. 해당 범위에 대한 회전을 하나의 인풋 마다 변경시키고, 다시 새로운 인풋값을 받아 바퀴 회전 및 과정 반복. 최종적으로 모든 인풋에 대한 회전을 수행한 자석들에 대해 바퀴의 평가값을 계산한다.  

**사용 자료구조**  
Circular List 구현  
극을 나타내는 'pole' (N - 0, S - 1) 원소 가지는 노드들의 링크드 리스트  
  
**구현 함수**  
start alg() - 알고리즘 메인 함수  
start rotate() - 입력 값으로부터 자석 바퀴 회전  
get range() - 현재 자석의 인접한 형태보고 회전의 영향 미칠 범위 계산  
evaluate() - 회전된 바퀴의 평가값 계산  
