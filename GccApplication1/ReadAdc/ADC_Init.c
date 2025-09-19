/*
 * ADC_Init.c
 *
 * Created: 2025-09-19
 * Author: rakggii
 */

#include "ADC_Init.h"

static volatile uint16_t adc_value = 0;

void ADC_Init(void) {
	ADMUX = (1 << REFS0) | (5 & 0x07); // AVcc 기준전압, ADC5 선택
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1);
	ADCSRA |= (1 << ADSC); // 첫 변환 시작
}

uint16_t ADC_GetValue(void) {
	return adc_value;
}

ISR(ADC_vect) {
	adc_value = ADC;          // 결과 저장
	ADCSRA |= (1 << ADSC);    // 다음 변환 시작
}
