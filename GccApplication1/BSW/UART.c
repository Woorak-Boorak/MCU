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

void UART_TransmitADC(uint16_t data){
    char buffer[6]; // 1024는 4자리 숫자 + NULL 문자('\0')를 위해 넉넉하게 6칸 할당
    // itoa(변환할 숫자, 저장할 버퍼, 진수(10진수));
    itoa(data, buffer, 10);
    // 변환된 문자열을 끝까지 한 글자씩 전송
    for (int i = 0; buffer[i] != '\0'; i++)
    {
	    UART_Transmit(buffer[i]);
    }
    UART_Transmit('\n');
    UART_Transmit('\r');
}

//문자열 송신 함수
void UART_SendString(const char* str){ // cosnt -> str 포인터 내부 값을 수정할 수 없음.
	while(*str){
		//문자열 끝인 NULL 까지 주소를 증가 (NULL 은 False 취급)
		UART_Transmit(*str++);
	}
	UART_Transmit('\n');
	UART_Transmit('\r');
}