/*
 * Vehicle_Control.h
 *
 * Created: 2025-09-22 오후 3:37:16
 *  Author: kym11
 */ 

#include "Vehicle_Control.h"

void Speed_Control(int16_t speed){
	
}

void Steering_Control(uint16_t steer){
	
}

void Light_Control(uint16_t light){
	if(light <= BRIGHT) PORTB |= (1<<5);
	else PORTB &= ~(1<<5);
}
