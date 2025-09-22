#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "BSW/ISR.h"
#include "BSW/UART.h"
#include "BSW/ADC_Init.h"
#include "BSW/Servo_Init.h"
#include "BSW/GPIO_Init.h"
#include "ReadAdc/ADC.h"
#include "Servo/SERVO.h"
#include "BSW/Sonic_Init.h"
#include "ReadSonic/Sonic.h"
#include "VehicleControl/Vehicle_Control.h"


int main(void)
{
	ISR_Init();
	UART_Init(9600);
	ADC_Init();
	Servo_Init();
	GPIO_Init();
	Sonic_Init();
	while (1) 
	{
	}
	return 1;
}

void task_5ms() {
	ADC_Start();
}

void task_20ms(){
	Servo_SetAngle();
}

void task_60ms() {
	//Read_Sonic();
}

void task_1000ms() {
	UART_Transmit('a');
	Light_Control(light);
}
