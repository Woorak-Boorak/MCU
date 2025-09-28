/*
 * Vehicle_Control.h
 *
 * Created: 2025-09-22 오후 3:37:02
 *  Author: kym11
 */ 


#ifndef VEHICLE_CONTROL_H_
#define VEHICLE_CONTROL_H_

#define BRIGHT 512
#define NONE 0
#define EMERGENCY_LEFT 1
#define EMERGENCY_CENTER 2
#define EMERGENCY_RIGHT 3
#define GOLEFT 100
#define GORIGHT 1000


#include <avr/io.h>
#include <stdint.h>

extern uint8_t mode;

#define NUM_BUTTONS 5
extern uint8_t button_active[NUM_BUTTONS]; // 5개 버튼의 ON/OFF 상태 저장
void check_buttons(void); // 버튼 상태를 업데이트하는 함수

void Speed_Control(int16_t speed);
void Steering_Control(uint16_t steer);
void Break_Control(uint16_t brek);
void Light_Control(uint16_t light);

#endif /* VEHICLE_CONTROL_H_ */