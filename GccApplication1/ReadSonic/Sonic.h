/*
 * Sonic.h
 *
 * Created: 2025-09-22 오전 11:19:28
 *  Author: kym11
 */ 
#ifndef SONIC_H_
#define SONIC_H_
#define F_CPU 16000000L
#define DISTANCE_TH 6
#define NUM_SENSORS 3
#include <util/delay.h>
#include <avr/interrupt.h>

extern volatile uint16_t distance_cm[NUM_SENSORS];

void Sonic_Trigger();
void GetDistance();

#endif /* SONIC_H_ */