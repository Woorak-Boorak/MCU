/*
 * ADC_Init.c
 *
 * Created: 2025-09-19
 * Author: rakggii
 */

#include "ADC_Init.h"

static volatile uint16_t adc_values[3] = {0, 0, 0};
static volatile uint8_t current_channel = 3;  // 시작: ADC3

void ADC_Init(void) {
	ADMUX = (1 << REFS0) | (current_channel & 0x07); // AVcc 기준, ADC3 선택
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1);
	sei();
	ADCSRA |= (1 << ADSC); // 첫 변환 시작
}

uint16_t ADC_GetValue(uint8_t idx) {
	// idx=0 → ADC3, idx=1 → ADC4, idx=2 → ADC5
	return adc_values[idx];
}

ISR(ADC_vect) {
	// 현재 채널 값 저장
	if(current_channel == 3) adc_values[0] = ADC;
	else if(current_channel == 4) adc_values[1] = ADC;
	else if(current_channel == 5) adc_values[2] = ADC;

	// 다음 채널로 이동
	if(current_channel == 3) current_channel = 4;
	else if(current_channel == 4) current_channel = 5;
	else current_channel = 3;

	// ADMUX 업데이트
	ADMUX = (1 << REFS0) | (current_channel & 0x07);

	// 다음 변환 시작
	ADCSRA |= (1 << ADSC);
}
