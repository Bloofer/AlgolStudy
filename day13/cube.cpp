#include <iostream>
using namespace std;

/*
전개도(옆쪽 전개) - 윗면과 아랫면 회전시 왼/오른/앞/뒷면들도 함께 회전
* 해당 전개도 기준으로 큐브 인코딩 후 아래 두 전개도는 회전방향을 참고하는데 사용함
             **************
             *W00 W01 W02 *
             *    윗 면    *
             *W10 W11 W12 *
             *            *
             *W20 W21 W22 *
*****************************************************
*G00 G01 G02 *R00 R01 R02 *B00 B01 B02 *O00 O01 O02 *
*    왼쪽면   *    앞 면    *   오른쪽면   *    뒷 면    *
*G10 G11 G12 *R10 R11 R12 *B10 B11 B12 *O10 O11 O12 *
*            *            *            *            *
*G20 G21 G22 *R20 R21 R22 *B20 B21 B22 *O20 O21 O22 *
*****************************************************
             *Y00 Y01 Y02 *
             *    아랫면   *
             *Y10 Y11 Y12 *
             *            *
             *Y20 Y21 Y22 *
             **************

전개도(아래쪽 전개) - 왼쪽/오른쪽면 회전시 위/아래/앞/뒷면들도 함께 회전
* 여기서 뒷면은 뒤집어진 상태고려
             **************
             *W00 W01 W02 *
             *    윗 면    *
             *W10 W11 W12 *
             *            *
             *W20 W21 W22 *
****************************************
*G00 G01 G02 *R00 R01 R02 *B00 B01 B02 *
*    왼쪽면   *    앞 면    *   오른쪽면   *
*G10 G11 G12 *R10 R11 R12 *B10 B11 B12 *
*            *            *            *
*G20 G21 G22 *R20 R21 R22 *B20 B21 B22 *
****************************************
             *Y00 Y01 Y02 *
             *    아랫면   *
             *Y10 Y11 Y12 *
             *            *
             *Y20 Y21 Y22 *
             **************
             *O20 O21 O22 *
             *    뒷 면    *
             *O10 O11 O12 *
             *            *
             *O00 O01 O02 *
             **************

전개도(아래쪽 전개) - 왼쪽/오른쪽면 회전시 위/아래/앞/뒷면들도 함께 회전
             **************
             *O20 O21 O22 *
             *    뒷 면    *
             *O10 O11 O12 *
             *            *
             *O00 O01 O02 *
*****************************************************
*G20 G10 G00 *W00 W01 W02 *B02 B12 B22 *Y00 Y01 Y02 *
*    왼쪽면   *    윗 면    *   오른쪽면   *    아랫면   *
*G21 G11 G01 *W10 W11 W12 *B01 B11 B21 *Y10 Y11 Y12 *
*            *            *            *            *
*G22 G12 G02 *W20 W21 W22 *B00 B10 B20 *Y20 Y21 Y22 *
*****************************************************
             *R00 R01 R02 *
             *    앞 면    *
             *R10 R11 R12 *
             *            *
             *R20 R21 R22 *
             **************
*/