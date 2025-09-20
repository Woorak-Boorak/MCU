/*
 * ADC.h
 *
 * Created: 2025-09-20 오후 1:10:57
 *  Author: kym11
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#ifndef ADC_H_
#define ADC_H_

void ADC_Start();

uint16_t ADC_GetSteer();

uint16_t ADC_GetMotor();

uint16_t ADC_GetBreak();

uint16_t ADC_GetLight();



#endif /* ADC_H_ */