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

void ADC_Start();

uint16_t ADC_GetSteer();

uint16_t ADC_GetMotor();

uint16_t ADC_GetBreak();

uint16_t ADC_GetLight();


#endif /* ADC_INIT_H_ */