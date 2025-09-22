/*
 * UART.h
 *
 * Created: 2025-09-22 오후 6:39:23
 *  Author: kym11
 */ 


#ifndef UART_H_
#define UART_H_

#include "../ReadSonic/Sonic.h"
#include <avr/io.h>
#include "stdlib.h"

void UART_Init(uint16_t baud);
void UART_Transmit(char data);
void UART_TransmitADC(uint16_t data);

#endif /* UART_H_ */