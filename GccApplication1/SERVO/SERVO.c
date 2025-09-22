/*
Tower Pro TM Micro Servo 9g SG90
서보모터1 15핀(PB1)
서보모터2 16핀(PB2)

(기본 스펙)
제어 신호 주기 : 50Hz = 20ms

(각도 - 펄스)
0도 : 약 1ms 펄스 폭(한 주기에서 HIGH인 시간)
90도(중립) : 약 1.5ms 펄스 폭
180도 : 약 2ms 펄스 폭

(타이머 현 상황)
타미어0 : 

(결론)
- 서보모터는 20ms 마다 제어를 해주어야 함
- 펄스의 HIGH 구간의 길이를 1ms ~ 2ms 사이로 정밀하게 조절하는 신호를 서보모터로 출력
*/

#include "Servo.h"
#include "../ReadAdc/ADC.h"

// 위에서 계산한 설정값들을 상수로 정의
#define ICR1_TOP 39999   // 20ms 주기 (50Hz)
#define OCR_MIN  1000    // 1ms 펄스 (0도에 해당)
#define OCR_MAX  5000    // 2ms 펄스 (180도에 해당)

void Servo_SetAngle() {
	uint8_t angle = (steer * 180L) / 1023;  // 0~1023 → 0~180도 매핑
	// 입력된 각도(0~180)를 OCR 값(2000~4000)으로 비례 변환(mapping)
	uint16_t ocr_value = OCR_MIN + (uint16_t)(((float)angle / 180.0) * (OCR_MAX - OCR_MIN));
	
	// 두 서보모터가 동일하게 움직이므로 OCR1A, OCR1B에 같은 값을 설정
	OCR1A = ocr_value;
}