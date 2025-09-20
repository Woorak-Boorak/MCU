#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define NUM_SENSORS 3

// --- 외부 공개 변수 (Global Variables) ---
// 다른 파일(main.c 등)에서 이 변수들을 사용하려면 extern 키워드가 필요.
extern volatile uint16_t g_pulse_duration[NUM_SENSORS];
extern volatile uint8_t g_is_measured[NUM_SENSORS];

// --- 외부 공개 함수 (Function Prototypes) ---
// 다른 파일에서 호출할 수 있는 함수들의 목록
void Ultrasonic_Init(void);
void Ultrasonic_Trigger(uint8_t sensor_index);

#endif /* ULTRASONIC_H_ */