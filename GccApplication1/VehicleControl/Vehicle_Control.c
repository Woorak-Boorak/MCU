/*
 * Vehicle_Control.c
 *
 * Created: 2025-09-22 오후 3:37:16
 * Author: kym11
 */

#include "Vehicle_Control.h"
#include "../BSW/UART.h"
#include "../ReadAdc/ADC.h"
#include "../LCDControl/LCD.h"
#include "../MotorControl/Motor_Control.h"
#include <avr/sleep.h>

int previous_mode = 0xFF; 
Mode mode = MODE_NONE;
uint8_t button_active[NUM_BUTTONS] = {0};

void Speed_Control(uint16_t speed, uint16_t brek){
     if(mode != previous_mode) {
         switch(mode){
             case MODE_NONE:
                 lcd_clear();
                 break;
             case MODE_EMERGENCY_LEFT:
                 lcd_EMERGENCY_LEFT();
                 break;
             case MODE_EMERGENCY_RIGHT:
                 lcd_EMERGENCY_RIGHT();
                 break;
             case MODE_EMERGENCY_CENTER:
                 lcd_EMERGENCY_CENTER();
                 break;
             default:
                 break;
         }
         previous_mode = (int)mode;
     }

     if (mode == MODE_EMERGENCY_CENTER) {
         Motor_Speed(0, 0);
     } else {
         Motor_Speed(speed, brek);
     }
}

void Steering_Control(uint16_t steer){
    switch(mode){
        case MODE_NONE:
            Servo_SetAngle(steer);
            break;
        case MODE_EMERGENCY_LEFT:
            Servo_SetAngle(GORIGHT);
            break;
        case MODE_EMERGENCY_RIGHT:
            Servo_SetAngle(GOLEFT);
            break;
        case MODE_EMERGENCY_CENTER:
            Servo_SetAngle(steer);
            break;
        default:
            break;
    }
}