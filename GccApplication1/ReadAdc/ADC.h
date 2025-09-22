/*
 * ADC.h
 *
 * Created: 2025-09-20 오후 1:10:57
 *  Author: kym11
 */ 
#ifndef ADC_H_
#define ADC_H_

#define LIGHT 2
#define STEER 3
#define MOTOR 4
#define BREAK 5

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

extern volatile uint16_t steer;
extern volatile uint16_t motor;
extern volatile uint16_t brek;
extern volatile uint16_t light;

void ADC_Start();

#endif /* ADC_H_ */