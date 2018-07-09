### 2018.07.16 코딩 스터디  
  
#### SW Expert Academy - 1952. [모의 SW 역량테스트] 수영장  
  
링크 : [swexpertacademy.com](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PpFQaAQMDFAUq&)  
  
블로그 글 : [Bloofer Blog](https://jmyang.kr/2018/07/09/swim/)  
  
**풀이 방법**  
1일권, 1달권, 3달권, 1년권의 요금제를 각 달별로 평가하여 최소의 값을 구한다. 월별 최소 요금을 먼저 입력으로 받은 월별 이용횟수와 1일권의 가격을 곱한 값과 1달권의 가격 중 최소로 준다. 그리고 3달간 월별 최소 요금을 모두 더한 값과 3달권의 가격 중 최소로 점화식을 세워 푼다. 마지막에 구해진 최소 가격은 1년권의 가격과 비교하면 된다.  
  
**사용 자료구조**  
1차원 배열.  
  
**구현 내용**  
monthPrice[i] = min(1일권 * month[i], 1달권)  
* i : 월별 인덱스  
* monthPrice[] : 매월 최소 이용요금(1일권, 1달권 중)  
* month[] : 매월 이용횟수  

totalPrice[i] = min(totalPrice[i-1] + monthPrice[i], totalPrice[i-3 + 3달권])  
* totalPrice[] : 매월 최소 이용요금(1일권, 1달권, 3달권 중)
