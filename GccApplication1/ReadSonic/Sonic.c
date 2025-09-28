/*
 * Sonic.c
 *
 * Created: 2025-09-22 오전 11:19:41
 *  Author: kym11
 */ 

#include "Sonic.h"

#define LEFT 0
#define CENTER 1
#define RIGHT 2
// --- 모듈 내부 변수 (Module-Internal Variables) ---
// 이 파일 안에서만 사용할 변수. static 키워드로 다른 파일에서의 접근을 막는다.
static volatile uint16_t pulse_start_time[NUM_SENSORS];
static volatile uint8_t last_pind_state = 0; // 이전 핀 상태를 저장할 변수 추가

// --- 전역 변수 정의 ---
volatile uint16_t g_pulse_duration[NUM_SENSORS] = {0};
volatile uint8_t g_is_measured[NUM_SENSORS] = {0};
volatile uint16_t distance_cm[NUM_SENSORS] = {0};

void Read_Sonic()
{
	//(TRIG: PD0)
	PORTD |= (1 << PORTD2);
	_delay_us(10);
	PORTD &= ~(1 << PORTD2);
	//(TRIG: PD0)
	PORTD |= (1 << PORTD4);
	_delay_us(10);
	PORTD &= ~(1 << PORTD4);
	//(TRIG: PD0)
	PORTD |= (1 << PORTD6);
	_delay_us(10);
	PORTD &= ~(1 << PORTD6);	
}

void GetDistance(int index){
	// g_is_measured와 g_pulse_duration은 ultrasonic.h를 통해 접근
	if (g_is_measured[index] == 1) {
		// 타이머 1의 Prescaler가 8이므로 1틱 = 0.5us
		distance_cm[index] = (uint16_t)((unsigned long)g_pulse_duration[index] * 5 / 58 / 10);
		if(distance_cm[index] <= 10 && distance_cm[index] >= 0){
			switch(index){
				case 0:
					mode = 1;
					break;
				case 1:
					mode = 2;
					break;
				case 2:
					mode = 3;
					break;
				default:
					//do nothing
					break;
			}
		}

		g_is_measured[index] = 0;
	}
}

void ModeUdate(){
	if(distance_cm[0] > 10 && distance_cm[1] > 10 && distance_cm[2] > 10)	mode = 0;
}

// --- 인터럽트 서비스 루틴 (ISRs) ---
ISR(PCINT2_vect)
{
	uint8_t current_pind_state = PIND; // 현재 D 포트의 핀 상태를 읽음
	uint8_t changed_bits = current_pind_state ^ last_pind_state; // 이전 상태와 비교하여 변경된 핀을 찾음

	// Sensor 0 (PD1)의 상태가 변했는지 확인
	if (changed_bits & (1 << PIND3)) {
		if (current_pind_state & (1 << PIND3)) { // 상승 엣지 (신호가 HIGH가 됨)
			pulse_start_time[0] = TCNT1;
			} else { // 하강 엣지 (신호가 LOW가 됨)
			g_pulse_duration[0] = TCNT1 - pulse_start_time[0];
			g_is_measured[0] = 1;
			GetDistance(LEFT);
		}
	}

	// Sensor 1 (PD3)의 상태가 변했는지 확인
	if (changed_bits & (1 << PIND5)) {
		if (current_pind_state & (1 << PIND5)) { // 상승 엣지
			pulse_start_time[1] = TCNT1;
			} else { // 하강 엣지
			g_pulse_duration[1] = TCNT1 - pulse_start_time[1];
			g_is_measured[1] = 1;
			GetDistance(CENTER);
		}
	}
	
	// Sensor 2 (PD7)의 상태가 변했는지 확인
	if (changed_bits & (1 << PIND7)) {
		if (current_pind_state & (1 << PIND7)) { // 상승 엣지
			pulse_start_time[2] = TCNT1;
			} else { // 하강 엣지
			g_pulse_duration[2] = TCNT1 - pulse_start_time[2];
			g_is_measured[2] = 1;
			GetDistance(RIGHT);
		}
	}
	last_pind_state = current_pind_state; // 다음 인터럽트를 위해 현재 상태를 저장
}