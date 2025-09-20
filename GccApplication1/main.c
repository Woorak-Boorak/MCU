#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "BSW/ISR.h"
#include "BSW/ADC_Init.h"
#include "BSW/Servo_Init.h"
#include "BSW/GPIO_Init.h"
#include "ReadAdc/ADC.h"
#include "Servo/SERVO.h"


int main(void)
{
	ISR_Init();
	ADC_Init();
	Servo_Init();
	GPIO_Init();
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
}

void task_1000ms() {
	// do nothing
}

void task_2000ms() {
	// do nothing
}