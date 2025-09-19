/*
 * ADC_Init.c
 *
 * Created: 2025-09-19
 * Author: rakggii
 */

#include "ADC_Init.h"
#define STEER 3
#define MOTOR 4
#define BREAK 5


static volatile uint16_t steer;
static volatile uint16_t motor;
static volatile uint16_t brek;
static volatile uint16_t light;
static volatile uint8_t current_channel = STEER;  // 시작: ADC3

void ADC_Init(void) {
	ADMUX = (1 << REFS0) | (current_channel & 0x07); // AVcc 기준, ADC3 선택
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1);
	ADCSRA |= (1 << ADSC); // 첫 변환 시작
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
	if(current_channel == STEER) stear = ADC;
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

	// 다음 변환 시작
	ADCSRA |= (1 << ADSC);
}
