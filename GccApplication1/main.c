#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "BSW/ISR.h"
#include "BSW/ADC_Init.h"
#include "BSW/Servo_Init.h"
#include "BSW/GPIO_Init.h"
#include "ReadAdc/ADC.h"
#include "Servo/SERVO.h"

//성준 추가
#include "BSW/Ultrasonic.h"
#define DISTANCE_TH 6


int main(void)
{
	ISR_Init();
	ADC_Init();
	Servo_Init();
	GPIO_Init();
	
	// 성준 추가
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
	
	// 성준 추가
	static uint8_t sensor_index = 0;
	
	Ultrasonic_Trigger(sensor_index);
	sensor_index = (sensor_index + 1) % NUM_SENSORS; // NUM_SENSORS = 3
}

void task_1000ms() {

	// 성준 추가 : 1000ms 마다 cm값 업데이트
	static uint16_t distance_cm[NUM_SENSORS] = {0};
	
	for (int i = 0; i < NUM_SENSORS; i++) {
		// g_is_measured와 g_pulse_duration은 ultrasonic.h를 통해 접근
		if (g_is_measured[i] == 1) {
			cli();
			// 타이머 1의 Prescaler가 8이므로 1틱 = 0.5us
			distance_cm[i] = (uint16_t)((unsigned long)g_pulse_duration[i] * 5 / 58 / 10);
			g_is_measured[i] = 0;
			sei();
		}
	}
	
	// 0번 센서가 임계값보다 안쪽으로 들어오면 불 남. 인덱스 바꿔가면서 조정 가능
	if(distance_cm[0] > 0 && distance_cm[0] < DISTANCE_TH)
		PORTB |= (1 << PORTB5);
	else
		PORTB &= ~(1 << PORTB5);
	
}

void task_2000ms() {
	// do nothing
}