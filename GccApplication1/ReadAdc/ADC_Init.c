/*
 * ADC_Init.c
 *
 * Created: 2025-09-19
 * Author: rakggii
 */

#include "ADC_Init.h"

static volatile uint16_t adc_value = 0;  // 최신 변환 값 저장용

void ADC_Init(void) {
    // AVcc를 기준 전압으로 선택, ADC5 (PC5) 채널 선택
    ADMUX = (1 << REFS0) | (5 & 0x07);

    // ADC Enable, ADC Interrupt Enable, 분주비 64 (16MHz/64 = 250kHz)
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1);

    sei();  // 전역 인터럽트 허용

    ADCSRA |= (1 << ADSC);  // 첫 변환 시작
}

uint16_t ADC_GetValue(void) {
    return adc_value;   // 최신 값을 반환
}

// ADC 변환 완료 인터럽트 서비스 루틴
ISR(ADC_vect) {
    adc_value = ADC;          // 변환 결과 읽기
    ADCSRA |= (1 << ADSC);    // 다음 변환 시작 (연속 변환용)
}
