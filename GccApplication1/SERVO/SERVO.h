#ifndef SERVO_H_
#define SERVO_H_

#include <avr/io.h>

/**
 * @brief Timer1�� Fast PWM ���� �ʱ�ȭ�Ͽ� �������͸� ������ �غ� �մϴ�.
 */
void Servo_Init(void);

/**
 * @brief ���������� ������ �����մϴ�.
 * @param angle ��ǥ ���� (0 ~ 180)
 */
void Servo_SetAngle(uint8_t angle);

#endif /* SERVO_H_ */