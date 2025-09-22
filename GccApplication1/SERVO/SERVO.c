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
#include "../ReadAdc/ADC.h"

// ������ ����� ���������� ����� ����
#define ICR1_TOP 39999   // 20ms �ֱ� (50Hz)
#define OCR_MIN  1000    // 1ms �޽� (0���� �ش�)
#define OCR_MAX  5000    // 2ms �޽� (180���� �ش�)

void Servo_SetAngle() {
	uint8_t angle = (steer * 180L) / 1023;  // 0~1023 �� 0~180�� ����
	// �Էµ� ����(0~180)�� OCR ��(2000~4000)���� ��� ��ȯ(mapping)
	uint16_t ocr_value = OCR_MIN + (uint16_t)(((float)angle / 180.0) * (OCR_MAX - OCR_MIN));
	
	// �� �������Ͱ� �����ϰ� �����̹Ƿ� OCR1A, OCR1B�� ���� ���� ����
	OCR1A = ocr_value;
}