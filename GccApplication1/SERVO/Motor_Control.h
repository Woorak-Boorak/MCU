#ifndef SERVO_H_
#define SERVO_H_

#include <avr/io.h>
#include <stdint.h>

void Servo_SetAngle(uint16_t steer);
void Motor_Speed(uint16_t speed, uint16_t brek);

#endif /* SERVO_H_ */