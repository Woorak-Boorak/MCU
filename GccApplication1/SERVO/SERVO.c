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

// 위에서 계산한 설정값들을 상수로 정의
#define ICR1_TOP 39999   // 20ms 주기 (50Hz)
#define OCR_MIN  2000    // 1ms 펄스 (0도에 해당)
#define OCR_MAX  4000    // 2ms 펄스 (180도에 해당)

void Servo_Init(void) {
	// PB1(OC1A), PB2(OC1B) 핀을 출력으로 설정
	DDRB |= (1 << DDB1) | (1 << DDB2);

	// TCCR1A: 비반전(non-inverting) PWM 모드 설정 (COM1A1/COM1B1)
	//         Fast PWM, TOP=ICR1 모드 설정 (WGM11)
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);

	// TCCR1B: Fast PWM, TOP=ICR1 모드 설정 (WGM13, WGM12)
	//         8분주(Prescaler 8) 설정 (CS11)
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	
	// ICR1: PWM 주기를 20ms로 설정 (TOP 값)
	ICR1 = ICR1_TOP;
	
	// 안전을 위해 초기 각도를 90도(중립)로 설정
	Servo_SetAngle(90);
}

void Servo_SetAngle(uint8_t angle) {
	// 입력된 각도(0~180)를 OCR 값(2000~4000)으로 비례 변환(mapping)
	uint16_t ocr_value = OCR_MIN + (uint16_t)(((float)angle / 180.0) * (OCR_MAX - OCR_MIN));
	
	// 두 서보모터가 동일하게 움직이므로 OCR1A, OCR1B에 같은 값을 설정
	OCR1A = ocr_value;
	OCR1B = ocr_value;
}