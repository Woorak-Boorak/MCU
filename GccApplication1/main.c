#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "BSW/ISR.h"

int main(void)
{
	ISR_Init();
	ADC_Init();
	DDRB |= (1<<5);
	/* Replace with your application code */
	while (1)
	{
	}
	return 1;
}

void task_1ms(){
	//do nothing
}

void task_60ms(){
	//do nothing
}

void task_1000ms(){
	PORTB |= (1<<5);
}

void task_2000ms(){
	PORTB &= ~(1<<5);
}

