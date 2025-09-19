#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "BSW/ISR.h"
#include "ReadAdc/ADC_Init.h"
#include "Servo/Servo.h"  

#define THRESHOLD 512

int main(void)
{
	ISR_Init();
	ADC_Init();
	Servo_Init();

	DDRB |= (1 << 5); // PB5 출력 (LED)

	while (1) {
		// main loop는 ISR과 task에 맡김
	}
	return 1;
}

void task_1ms() {
	// do nothing
}

void task_60ms() {
	uint16_t steer = ADC_GetSteer(); // PC3
	uint16_t motor = ADC_GetMotor(); // PC4
	uint16_t brek = ADC_GetBreak(); // PC5
	uint16_t light = ADC_GetLight();

	// LED 제어
	if (light > THRESHOLD) {
		PORTB |= (1 << 5);
		} else {
		PORTB &= ~(1 << 5);
	}

	// 서보 제어 (예: PC3 값으로 제어)
	uint8_t angle = (val3 * 180L) / 1023;  // 0~1023 → 0~180도 매핑
	Servo_SetAngle(angle);
}

void task_1000ms() {
	// do nothing
}

void task_2000ms() {
	// do nothing
}
