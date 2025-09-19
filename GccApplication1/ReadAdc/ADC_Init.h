/*
 * ADC_Init.h
 *
 * Created: 2025-09-19
 * Author: rakggii
 */

#ifndef ADC_INIT_H_
#define ADC_INIT_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void ADC_Init(void);
uint16_t ADC_GetValue(uint8_t idx);  

#endif /* ADC_INIT_H_ */