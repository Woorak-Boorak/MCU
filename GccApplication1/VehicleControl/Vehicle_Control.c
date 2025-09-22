/*
 * Vehicle_Control.h
 *
 * Created: 2025-09-22 오후 3:37:16
 *  Author: kym11
 */ 

#include "Vehicle_Control.h"
#include "../Servo/SERVO.h"
#include "../BSW/UART.h"
uint8_t mode = 0;

void Speed_Control(int16_t speed){
	switch(mode){
		case NONE:
			Servo_SetAngle(speed);
			break;
		case EMERGENCY_LEFT:
			Servo_SetAngle(GORIGHT);
			break;
		case EMERGENCY_RIGHT:
			Servo_SetAngle(GOLEFT);
			break;
		case EMERGENCY_CENTER:
			Servo_SetAngle(speed);
			break;
		default:
		//do nothing
		break;
	}
}

void Steering_Control(uint16_t steer){
	switch(mode){
		case NONE:
			Servo_SetAngle(steer);
			break;
		case EMERGENCY_LEFT:
			UART_Transmit('s');	
			Servo_SetAngle(GORIGHT);
			break;
		case EMERGENCY_RIGHT:
			Servo_SetAngle(GOLEFT);
			break;
		case EMERGENCY_CENTER:
			Servo_SetAngle(steer);
			break;
		default:
			//do nothing
			break;
	}
}

void Light_Control(uint16_t light){
	if(light <= BRIGHT) PORTB |= (1<<5);
	else PORTB &= ~(1<<5);
}
