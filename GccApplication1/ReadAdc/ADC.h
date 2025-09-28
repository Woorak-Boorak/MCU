/*
 * ADC.h
 *
 * Created: 2025-09-20 오후 1:10:57
 *  Author: kym11
 */ 
#ifndef ADC_H_
#define ADC_H_

#define BREAK 0     // PC0 (ADC0) - 23번핀
#define MOTOR 1     // PC1 (ADC1) - 24번핀
#define STEER 2     // PC2 (ADC2) - 25번핀
#define BUTTON 3    // PC3 (ADC3) - 26번핀 (새로 추가)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

extern volatile uint16_t steer;
extern volatile uint16_t motor;
extern volatile uint16_t brek;
extern volatile uint16_t button_val;

void ADC_Start();

#endif /* ADC_H_ */