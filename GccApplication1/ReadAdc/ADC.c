/*
 * ADC.c
 *
 * Created: 2025-09-20 오후 1:11:39
 *  Author: kym11
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADC.h"
#include "../Common/defs.h"
#include "../BSW/UART.h"
#include <avr/sleep.h>

volatile uint16_t steer;
volatile uint16_t motor;
volatile uint16_t brek;
volatile uint16_t button_val;
volatile uint8_t current_channel = STEER;
static uint8_t button_active[NUM_BUTTONS] = {0};

static uint8_t get_button_from_adc(uint16_t adc_val) {
	if (adc_val > BTN_5_LOW) return BUTTON_PROGRAMOFF;
	if (adc_val >= BTN_4_LOW && adc_val <= BTN_4_HIGH) return BUTTON_GETOUT;
	if (adc_val >= BTN_3_LOW && adc_val <= BTN_3_HIGH) return BUTTON_SORRY;
	if (adc_val >= BTN_2_LOW && adc_val <= BTN_2_HIGH) return BUTTON_AC;
	if (adc_val >= BTN_1_LOW && adc_val <= BTN_1_HIGH) return BUTTON_HOTASS;
	return 0;
}

static void check_buttons(void) {
	static uint8_t last_detected_button = 0;
	uint8_t current_button = get_button_from_adc(button_val);
	if (current_button != last_detected_button) {
		if (current_button != 0) {
			uint8_t idx = current_button - 1;
			button_active[idx] = !button_active[idx];
			switch (current_button) {
				case BUTTON_HOTASS:
					if (button_active[idx]) UART_SendString("엉뜨를 켰습니다");
					else UART_SendString("엉뜨를 껐습니다\r\n");
					break;
				case BUTTON_AC:
					if (button_active[idx]) UART_SendString("에어컨을 켰습니다");
					else UART_SendString("에어컨을 껐습니다\r\n");
					break;
				case BUTTON_SORRY:
					if (button_active[idx]) UART_SendString("비상등을 켰습니다");
					else UART_SendString("비상등을 껐습니다\r\n");
					break;
				case BUTTON_GETOUT:
					if (button_active[idx]) UART_SendString("상향등을 켰습니다");
					else UART_SendString("상향등을 껐습니다\r\n");
					break;
				case BUTTON_PROGRAMOFF:
					if (button_active[idx]) {
						UART_SendString("프로그램을 종료하겠습니다\r\n");
						set_sleep_mode(SLEEP_MODE_PWR_DOWN);
						sleep_enable();
						sleep_cpu();
					}
					break;
				default:
					break;
			}
		}
		last_detected_button = current_button;
	}
}

void ADC_Start(void){
	ADCSRA |= (1 << ADSC);
}

ISR(ADC_vect) {
	if(current_channel == STEER) steer = ADC;
	else if(current_channel == MOTOR) motor = ADC;
	else if(current_channel == BREAK) brek = ADC;
	else if(current_channel == BUTTON) {
		button_val = ADC;
		check_buttons();
	}

	if(current_channel == STEER) current_channel = MOTOR;
	else if(current_channel == MOTOR) current_channel = BREAK;
	else if(current_channel == BREAK) current_channel = BUTTON;
	else current_channel = STEER;
	
	ADMUX = (1 << REFS0) | (current_channel & 0x07);
}
