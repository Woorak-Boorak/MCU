/*
 * ADC.c
 *
 * Created: 2025-09-20 오후 1:11:39
 *  Author: kym11
 */ 
#include "ADC.h"

#define LIGHT 2
#define STEER 3
#define MOTOR 4
#define BREAK 5

static volatile uint16_t steer;
static volatile uint16_t motor;
static volatile uint16_t brek;
static volatile uint16_t light;
static volatile uint8_t current_channel = STEER;  // 시작: ADC3

void ADC_Start(){
	ADCSRA |= (1 << ADSC);
}

uint16_t ADC_GetSteer() {
	return steer;
}

uint16_t ADC_GetMotor() {
	return motor;
}

uint16_t ADC_GetBreak() {
	return brek;
}

uint16_t ADC_GetLight() {
	return light;
}

ISR(ADC_vect) {
	// 현재 채널 값 저장
	if(current_channel == STEER) steer = ADC;
	else if(current_channel == MOTOR) motor = ADC;
	else if(current_channel == BREAK) brek = ADC;
	else if(current_channel == LIGHT) light = ADC;

	// 다음 채널로 이동
	if(current_channel == STEER) current_channel = MOTOR;
	else if(current_channel == MOTOR) current_channel = BREAK;
	else if(current_channel == BREAK) current_channel = LIGHT;
	else current_channel = STEER;

	// ADMUX 업데이트
	ADMUX = (1 << REFS0) | (current_channel & 0x07);
}
