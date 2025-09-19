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
	//GPIO_Init();
	DDRB |= (1 << 5); // PB5 ��� (LED)

	while (1) {
	}
	return 1;
}

void task_1ms() {
	ADC_Start();
}

void task_60ms() {
	uint16_t steer = ADC_GetSteer(); 
	uint16_t motor = ADC_GetMotor(); 
	uint16_t brek = ADC_GetBreak(); 
	uint16_t light = ADC_GetLight();
	
	// LED ����
	if (light > THRESHOLD) {
		PORTB |= (1 << 5);
		} else {
		PORTB &= ~(1 << 5);
	}

	// ���� ���� (��: PC3 ������ ����)
	uint8_t angle = (steer * 180L) / 1023;  // 0~1023 �� 0~180�� ����
	Servo_SetAngle(angle);
}

void task_1000ms() {
	// do nothing
}

void task_2000ms() {
	// do nothing
}