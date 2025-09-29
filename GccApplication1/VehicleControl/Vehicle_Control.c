/*
 * Vehicle_Control.c
 *
 * Created: 2025-09-22 오후 3:37:16
 * Author: kym11
 */

#include "Vehicle_Control.h"
// uart_sendstring 함수를 사용하기 위해 헤더 파일을 인클루드해야 합니다.
// 만약 uart.h 와 같은 파일에 있다면 아래와 같이 추가해주세요.
// #include "uart.h"

// [수정] 중복 선언된 변수 제거
int previous_mode = 0xFF; 
uint8_t mode = 0;
uint8_t button_active[NUM_BUTTONS] = {0}; // 버튼 상태 저장 배열 (모두 OFF로 시작)
static uint8_t last_detected_button = 0;   // 중복 입력을 막기 위한 변수

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
    
    // 버튼 상태에 '변화'가 생겼을 때 (눌렸거나, 떼어졌을 때)
    if (current_button != last_detected_button) {
        
        // 버튼이 '눌렸을' 때만 동작 (떼는 순간은 무시)
        if (current_button != 0) {
            // 해당 버튼의 상태를 토글 (ON -> OFF, OFF -> ON)
            button_active[current_button - 1] = !button_active[current_button - 1];

            // --- UART 메시지 전송 로직 추가 ---
            switch (current_button) {
                case 1:
					if (button_active[0]) UART_SendString("엉뜨를 켰습니다");
					else UART_SendString("엉뜨를 껐습니다\r\n");
					break;
                case 2:
					if (button_active[1]) UART_SendString("에어컨을 켰습니다");
					else UART_SendString("에어컨을 껐습니다\r\n");
                break;
                case 3:
					if (button_active[2]) UART_SendString("비상등을 켰습니다");
					else UART_SendString("비상등을 껐습니다\r\n");
                break;
                case 4:
					if (button_active[3]) UART_SendString("상향등을 켰습니다");
					else UART_SendString("상향등을 껐습니다\r\n");
                break;
                case 5:
					if (button_active[4]) {
						UART_SendString("프로그램을 종료하겠습니다\r\n");
					    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
					    sleep_enable();
					    sleep_cpu();
					}
					else UART_SendString("BTN5 : OFF\r\n");
                break;
			}
        }
        
        // [수정] last_detected_button 업데이트 위치를 바깥으로 이동
        // 버튼을 누르거나 뗄 때 모두 상태가 갱신되어야 다음 입력을 정확히 감지할 수 있습니다.
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