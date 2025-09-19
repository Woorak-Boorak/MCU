/*
 * ISR.c
 *
 * Created: 2025-09-19 오후 6:13:19
 *  Author: kym11
 */ 

#include "ISR.h"
int ms_count = 0;

void ISR_Init(void){
<<<<<<< HEAD
	TCCR2B |= (1<<WGM21);
=======
	TCCR2A |= (1<<WGM21);
>>>>>>> 86b27bc (3ADC)
	//CTC모드 ON (dataSheet 109p 참고)
	TCCR2B |= (1<<CS22);
	//prescaler 설정
	OCR2A = 249;
	//TOP 설정
	TIMSK2 |= (1<<OCIE2A);
	sei();
}

ISR(TIMER2_COMPA_vect){
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

	if(ms_count%1000==0){
		task_1000ms();
	}
	else
	{
		//do nothing
	}
	
	if(ms_count%2000==0){
		task_2000ms();
	}
	else
	{
		//do nothing
	}
}


