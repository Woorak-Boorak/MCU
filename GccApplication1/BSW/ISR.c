/*
 * ISR.c
 *
 * Created: 2025-09-19 오후 6:13:19
 *  Author: kym11
 */ 

#include "ISR.h"
int ms_count = 0;

void ISR_Init(void){
	TCCR1B |= (1<<WGM12);
	//CTC모드 ON (dataSheet 109p 참고)
	TCCR1B |= (1<<CS11) | (1<<CS10);
	//prescaler 설정
	OCR1A = 255;
	//TOP 설정
	TIMSK1 |= (1<<OCIE1A);
	sei();
}

ISR(TIMER1_COMPA_vect){
	ms_count++;
	if(ms_count%1==0){
		task_1ms();
	}
	else
	{
		//do nothing
	}
	
	if(ms_count%60==0){
		task_60ms();
	}
	else
	{
		//do nothing
	}

	if(ms_count%500==0){
		task_1000ms();
	}
	else
	{
		//do nothing
	}
	
	if(ms_count%1000==0){
		task_2000ms();
	}
	else
	{
		//do nothing
	}
}


