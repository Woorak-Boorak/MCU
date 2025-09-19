/*
 * ADC_Init.h
 *
 * Created: 2025-09-19
 * Author: kym11
 */

#ifndef ADC_INIT_H_
#define ADC_INIT_H_

#include <avr/io.h>
#include <avr/interrupt.h>

// 외부에서 사용할 함수
void ADC_Init(void);
uint16_t ADC_GetValue(void);

#endif /* ADC_INIT_H_ */