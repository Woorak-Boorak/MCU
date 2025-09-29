/*
 * Servo_Init.c
 *
 * Created: 2025-09-20 오후 1:29:04
 *  Author: kym11
 */ 

#include <avr/io.h>
#include "Servo_Init.h"
#define ICR1_TOP 39999   // 20ms 주기 (50Hz)

void Servo_Init(void) {
	// PB1(OC1A), PB2(OC1B) 핀을 출력으로 설정
	DDRB |= (1 << DDB1) | (1 << DDB2);

	// TCCR1A: 비반전(non-inverting) PWM 모드 설정 (COM1A1/COM1B1)
	//         Fast PWM, TOP=ICR1 모드 설정 (WGM11)
	TCCR1A = (1 << COM1A1) | (1 << COM1B0) | (1 << COM1B1) | (1 << WGM11);

	// TCCR1B: Fast PWM, TOP=ICR1 모드 설정 (WGM13, WGM12)
	//         8분주(Prescaler 8) 설정 (CS11)
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	
	// ICR1: PWM 주기를 20ms로 설정 (TOP 값)
	ICR1 = ICR1_TOP;
}