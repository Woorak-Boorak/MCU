/*
 * ADC.c
 *
 * Created: 2025-09-20 오후 1:11:39
 *  Author: kym11
 */ 
#include "ADC.h"

volatile uint16_t steer;
volatile uint16_t motor;
volatile uint16_t brek;
volatile uint16_t button_val; // 'light' 변수 대신 사용
volatile uint8_t current_channel = STEER;  // 시작 채널을 STEER(ADC2)로 변경


void ADC_Start(){
	ADCSRA |= (1 << ADSC);
}

ISR(ADC_vect) {
	// 현재 채널 값 저장
	if(current_channel == STEER) steer = ADC;
	else if(current_channel == MOTOR) motor = ADC;
	else if(current_channel == BREAK) brek = ADC;
	else if(current_channel == BUTTON) button_val = ADC;

	// 다음 채널로 이동
	if(current_channel == STEER) current_channel = MOTOR;
	else if(current_channel == MOTOR) current_channel = BREAK;
	else if(current_channel == BREAK) current_channel = BUTTON;
	else current_channel = STEER;
	
	// ADMUX 업데이트
	ADMUX = (1 << REFS0) | (current_channel & 0x07);
}
