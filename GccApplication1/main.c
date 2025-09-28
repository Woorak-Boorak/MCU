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
#include <stdlib.h>

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
	Steering_Control(steer);
	Motor_Speed(motor, brek);
}

void task_60ms() {
	Read_Sonic();
	ModeUdate();
	check_buttons();
}

void task_1000ms() {
	UART_Transmit('\n');
	UART_Transmit('\r');
	UART_Transmit('\n');
	UART_Transmit('\r');//구분선
	
	UART_TransmitADC(motor);
	UART_TransmitADC(steer);
	UART_TransmitADC(brek);
	//UART_TransmitADC(distance_cm[0]);
	//UART_TransmitADC(distance_cm[1]);
	//UART_TransmitADC(distance_cm[2]);
	UART_TransmitADC(mode);	
	
	//버튼 디버깅용
	UART_Transmit('\n');
	UART_Transmit('\r');
	UART_TransmitADC(button_val);
	
	for (int i = 0; i < NUM_BUTTONS; i++) {
		UART_Transmit('B');
		UART_Transmit('0' + (5 - i)); // B1, B2...
		UART_Transmit(':');
		UART_Transmit(' ');

		if (button_active[4 - i]) {
			UART_Transmit('O');
			UART_Transmit('N');
			} else {
			UART_Transmit('O');
			UART_Transmit('F');
			UART_Transmit('F');
		}
		UART_Transmit('\n');
		UART_Transmit('\r');
	}
	UART_Transmit('\n'); 
	UART_Transmit('\r');//구분선
}
