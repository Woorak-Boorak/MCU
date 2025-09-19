#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "BSW/ISR.h"
#include "ReadAdc/ADC_Init.h"

#define THRESHOLD 512

int main(void)
{
	ISR_Init();
	ADC_Init();

	DDRB |= (1 << 5); // PB5 출력 (LED)

	while (1) {
		// main loop는 ISR과 task에 맡김
	}
	return 1;
}

void task_1ms() {
	// do nothing
}

void task_60ms() {
	uint16_t val3 = ADC_GetValue(0); // ADC3 (PC3)
	uint16_t val4 = ADC_GetValue(1); // ADC4 (PC4)
	uint16_t val5 = ADC_GetValue(2); // ADC5 (PC5)

	if (val3 > THRESHOLD || val4 > THRESHOLD || val5 > THRESHOLD) {
		PORTB |= (1 << 5);   // 하나라도 넘으면 LED ON
		} else {
		PORTB &= ~(1 << 5);  // 다 이하면 LED OFF
	}
}

void task_1000ms() {
	// do nothing
}

void task_2000ms() {
	// do nothing
}