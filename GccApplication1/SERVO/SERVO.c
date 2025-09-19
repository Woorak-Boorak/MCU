/*
Tower Pro TM Micro Servo 9g SG90
��������1 15��(PB1)
��������2 16��(PB2)

(�⺻ ����)
���� ��ȣ �ֱ� : 50Hz = 20ms

(���� - �޽�)
0�� : �� 1ms �޽� ��(�� �ֱ⿡�� HIGH�� �ð�)
90��(�߸�) : �� 1.5ms �޽� ��
180�� : �� 2ms �޽� ��

(Ÿ�̸� �� ��Ȳ)
Ÿ�̾�0 : 

(���)
- �������ʹ� 20ms ���� ��� ���־�� ��
- �޽��� HIGH ������ ���̸� 1ms ~ 2ms ���̷� �����ϰ� �����ϴ� ��ȣ�� �������ͷ� ���
*/

#include "Servo.h"

// ������ ����� ���������� ����� ����
#define ICR1_TOP 39999   // 20ms �ֱ� (50Hz)
#define OCR_MIN  2000    // 1ms �޽� (0���� �ش�)
#define OCR_MAX  4000    // 2ms �޽� (180���� �ش�)

void Servo_Init(void) {
	// PB1(OC1A), PB2(OC1B) ���� ������� ����
	DDRB |= (1 << DDB1) | (1 << DDB2);

	// TCCR1A: �����(non-inverting) PWM ��� ���� (COM1A1/COM1B1)
	//         Fast PWM, TOP=ICR1 ��� ���� (WGM11)
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);

	// TCCR1B: Fast PWM, TOP=ICR1 ��� ���� (WGM13, WGM12)
	//         8����(Prescaler 8) ���� (CS11)
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	
	// ICR1: PWM �ֱ⸦ 20ms�� ���� (TOP ��)
	ICR1 = ICR1_TOP;
	
	// ������ ���� �ʱ� ������ 90��(�߸�)�� ����
	Servo_SetAngle(90);
}

void Servo_SetAngle(uint8_t angle) {
	// �Էµ� ����(0~180)�� OCR ��(2000~4000)���� ��� ��ȯ(mapping)
	uint16_t ocr_value = OCR_MIN + (uint16_t)(((float)angle / 180.0) * (OCR_MAX - OCR_MIN));
	
	// �� �������Ͱ� �����ϰ� �����̹Ƿ� OCR1A, OCR1B�� ���� ���� ����
	OCR1A = ocr_value;
	OCR1B = ocr_value;
}