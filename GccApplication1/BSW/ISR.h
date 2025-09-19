/*
 * IncFile1.h
 *
 * Created: 2025-09-19 오후 6:09:58
 *  Author: kym11
 */ 


#ifndef ISR_H_
#define ISR_H_
#include <avr/io.h>
#include <avr/interrupt.h>

extern void ISR_Init(void);
extern void task_1ms(void);
extern void task_60ms(void);
extern void task_1000ms(void);	
extern void task_2000ms(void);	

#endif /* ISR_H_ */