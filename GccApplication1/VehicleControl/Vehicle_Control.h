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
#define NUM_BUTTONS 5
#define HOTASS 1	
#define AC 2
#define SORRY 3
#define GETOUT 4
#define PROGRAMOFF 5
// 버튼 임계값
#define BTN_1_LOW 150
#define BTN_1_HIGH 230
#define BTN_2_LOW 320
#define BTN_2_HIGH 410
#define BTN_3_LOW 500
#define BTN_3_HIGH 590
#define BTN_4_LOW 710
#define BTN_4_HIGH 790
#define BTN_5_LOW 980

#include <avr/io.h>
#include <stdint.h>
#include "Vehicle_Control.h"
#include "../Servo/SERVO.h"
#include "../BSW/UART.h"
#include "../ReadAdc/ADC.h"
#include "../LCDControl/LCD.h"
#include <avr/sleep.h>

extern uint8_t mode;
extern uint8_t button_active[NUM_BUTTONS]; // 5개 버튼의 ON/OFF 상태 저장
void check_buttons(void); // 버튼 상태를 업데이트하는 함수

void Speed_Control(uint16_t speed, uint16_t brek);
void Steering_Control(uint16_t steer);
void Break_Control(uint16_t brek);
void Light_Control(uint16_t light);

#endif /* VEHICLE_CONTROL_H_ */