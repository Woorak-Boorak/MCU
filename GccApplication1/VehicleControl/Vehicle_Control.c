/*
 * Vehicle_Control.h
 *
 * Created: 2025-09-22 오후 3:37:16
 *  Author: kym11
 */ 
int previous_mode = 0xFF;
int previous_mode;
#include "Vehicle_Control.h"

uint8_t mode = 0;

uint8_t button_active[NUM_BUTTONS] = {0}; // 버튼 상태 저장 배열 (모두 OFF로 시작)
static uint8_t last_detected_button = 0;   // 중복 입력을 막기 위한 변수

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

static uint8_t get_button_from_adc(uint16_t adc_val) {
	if (adc_val > BTN_5_LOW) return 5;
	if (adc_val >= BTN_4_LOW && adc_val <= BTN_4_HIGH) return 4;
	if (adc_val >= BTN_3_LOW && adc_val <= BTN_3_HIGH) return 3;
	if (adc_val >= BTN_2_LOW && adc_val <= BTN_2_HIGH) return 2;
	if (adc_val >= BTN_1_LOW && adc_val <= BTN_1_HIGH) return 1;
	return 0; // 아무것도 안 눌림
}

void check_buttons(void) {
	uint8_t current_button = get_button_from_adc(button_val);

	if (current_button != last_detected_button) { 
		if (current_button != 0) {
			button_active[current_button - 1] = !button_active[current_button - 1];
		}
		last_detected_button = current_button;
	}
}

void Speed_Control(uint16_t speed, uint16_t brek){
	 if(mode != previous_mode) {
		 switch(mode){
			 case NONE:
			 // mode가 NONE으로 바뀌는 순간에 딱 한 번만 화면을 지웁니다.
			 lcd_clear();
			 break;
			 case EMERGENCY_LEFT:
			 lcd_EMERGENCY_LEFT();
			 break;
			 case EMERGENCY_RIGHT:
			 lcd_EMERGENCY_RIGHT();
			 break;
			 case EMERGENCY_CENTER:
			 lcd_EMERGENCY_CENTER();
			 break;
			 default:
			 // do nothing
			 break;
		 }
		 previous_mode = mode; // 현재 모드를 이전 모드로 기록
	 }

	 // 모터 제어는 LCD 업데이트와 상관없이 항상 실행
	 if (mode == EMERGENCY_CENTER) {
		 Motor_Speed(0, 0);
		 } else {
		 Motor_Speed(speed, brek);
	 }
}

void Steering_Control(uint16_t steer){
	switch(mode){
		case NONE:
			Servo_SetAngle(steer);
			break;
		case EMERGENCY_LEFT:
			Servo_SetAngle(GORIGHT);
			break;
		case EMERGENCY_RIGHT:
			Servo_SetAngle(GOLEFT);
			break;
		case EMERGENCY_CENTER:
			Servo_SetAngle(steer);
			break;
		default:
			//do nothing
			break;
	}
}

void Light_Control(uint16_t light){
	if(light <= BRIGHT) PORTB |= (1<<5);
	else PORTB &= ~(1<<5);
}
