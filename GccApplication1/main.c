#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "BSW/ISR.h"
#include "ReadAdc/ADC_Init.h"

#define THRESHOLD 512   // �Ӱ谪 (0~1023 ����)

int main(void)
{
	ISR_Init();
	ADC_Init();

	DDRB |= (1 << 5); // PB5 ��� ���� (LED ��)

	while (1)
	{
		// ���� ������ ISR�� task�� �ñ�
	}
	return 1;
}

void task_1ms() {
	// do nothing
}

void task_60ms() {
	uint16_t val = ADC_GetValue();

	if (val > THRESHOLD) {
		PORTB |= (1 << 5);   // �Ӱ谪 �ʰ� �� PB5 HIGH
		} else {
		PORTB &= ~(1 << 5);  // �Ӱ谪 ���� �� PB5 LOW
	}
}

void task_1000ms() {
	// do nothing
}

void task_2000ms() {
	// do nothing
}



