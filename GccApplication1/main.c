#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "BSW/ISR.h"
#include "ReadAdc/ADC_Init.h"

#define THRESHOLD 512   // 임계값 (0~1023 범위)

int main(void)
{
	ISR_Init();
	ADC_Init();

	DDRB |= (1 << 5); // PB5 출력 설정 (LED 등)

	while (1)
	{
		// 메인 루프는 ISR과 task에 맡김
	}
	return 1;
}

void task_1ms() {
	// do nothing
}

void task_60ms() {
	uint16_t val = ADC_GetValue();

	if (val > THRESHOLD) {
		PORTB |= (1 << 5);   // 임계값 초과 → PB5 HIGH
		} else {
		PORTB &= ~(1 << 5);  // 임계값 이하 → PB5 LOW
	}
}

void task_1000ms() {
	// do nothing
}

void task_2000ms() {
	// do nothing
}



