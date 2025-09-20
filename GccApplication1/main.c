#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "BSW/ISR.h"
#include "BSW/ADC_Init.h"
#include "BSW/Servo_Init.h"
#include "BSW/GPIO_Init.h"
#include "ReadAdc/ADC.h"
#include "Servo/SERVO.h"

//���� �߰�
#include "BSW/Ultrasonic.h"
#define DISTANCE_TH 6


int main(void)
{
	ISR_Init();
	ADC_Init();
	Servo_Init();
	GPIO_Init();
	
	// ���� �߰�
	Ultrasonic_Init();
	
	while (1) 
	{
	}
	return 1;
}

void task_1ms() {
	ADC_Start();
}

void task_60ms() {
	Servo_SetAngle();
	
	// ���� �߰�
	static uint8_t sensor_index = 0;
	
	Ultrasonic_Trigger(sensor_index);
	sensor_index = (sensor_index + 1) % NUM_SENSORS; // NUM_SENSORS = 3
}

void task_1000ms() {

	// ���� �߰� : 1000ms ���� cm�� ������Ʈ
	static uint16_t distance_cm[NUM_SENSORS] = {0};
	
	for (int i = 0; i < NUM_SENSORS; i++) {
		// g_is_measured�� g_pulse_duration�� ultrasonic.h�� ���� ����
		if (g_is_measured[i] == 1) {
			cli();
			// Ÿ�̸� 1�� Prescaler�� 8�̹Ƿ� 1ƽ = 0.5us
			distance_cm[i] = (uint16_t)((unsigned long)g_pulse_duration[i] * 5 / 58 / 10);
			g_is_measured[i] = 0;
			sei();
		}
	}
	
	// 0�� ������ �Ӱ谪���� �������� ������ �� ��. �ε��� �ٲ㰡�鼭 ���� ����
	if(distance_cm[0] > 0 && distance_cm[0] < DISTANCE_TH)
		PORTB |= (1 << PORTB5);
	else
		PORTB &= ~(1 << PORTB5);
	
}

void task_2000ms() {
	// do nothing
}