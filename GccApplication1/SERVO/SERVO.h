#ifndef SERVO_H_
#define SERVO_H_

#include <avr/io.h>

/**
 * @brief Timer1을 Fast PWM 모드로 초기화하여 서보모터를 구동할 준비를 합니다.
 */
void Servo_Init(void);

/**
 * @brief 서보모터의 각도를 설정합니다.
 * @param angle 목표 각도 (0 ~ 180)
 */
void Servo_SetAngle(uint8_t angle);

#endif /* SERVO_H_ */