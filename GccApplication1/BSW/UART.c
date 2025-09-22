/*
 * UART.c
 *
 * Created: 2025-09-22 오후 6:39:34
 *  Author: kym11
 */ 
#include "UART.h"

void UART_Init(uint16_t baud){
	uint16_t ubrr = (uint16_t)(F_CPU / 16 / baud - 1);
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	//보레이트 설정 레지스터
	UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1<<RXCIE0); //수신 인터럽트까지 추가
	// RX , TX ON. 이 레지스터에서 인터럽트핀도 on , off 할 수 있음.
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	// Character Size 설정
}

void UART_Transmit(char data){
	//data 를 받고 기다림. UCSR0A 레지스터에서 UDRE0이 1이 될때까지 기다림. ( UDR0이 비어질떄까지 기다림)
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}