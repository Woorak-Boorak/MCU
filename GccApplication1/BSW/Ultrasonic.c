#include "Ultrasonic.h"

// --- 모듈 내부 변수 (Module-Internal Variables) ---
// 이 파일 안에서만 사용할 변수. static 키워드로 다른 파일에서의 접근을 막는다.
static volatile uint16_t pulse_start_time[NUM_SENSORS];

// --- 전역 변수 정의 (Global Variable Definitions) ---
// .h 파일에서 extern으로 선언했던 변수들의 실체.
volatile uint16_t g_pulse_duration[NUM_SENSORS] = {0};
volatile uint8_t g_is_measured[NUM_SENSORS] = {0};


// --- 함수 구현 (Function Implementations) ---

void Ultrasonic_Init(void)
{
	// 1. TRIG 핀 (PD0, PD2, PD4)을 출력으로 설정
	DDRD |= (1 << DDD0) | (1 << DDD2) | (1 << DDD4);
	PORTD &= ~((1 << PORTD0) | (1 << PORTD2) | (1 << PORTD4));

	// 2. ECHO 핀 (PD1, PD3, PD7)을 입력으로 설정
	DDRD &= ~((1 << DDD1) | (1 << DDD3) | (1 << DDD7));

	// 3. Pin Change Interrupt 활성화
	PCICR |= (1 << PCIE2);

	// 4. ECHO 핀에 해당하는 인터럽트 마스크 설정
	PCMSK2 |= (1 << PCINT17) | (1 << PCINT19) | (1 << PCINT23); // PD1, PD3, PD7
	
	// 타이머 1 설정은 Servo_Init()에서 이미 완벽하게 되어 있으므로 여기서 할 필요가 없네.
}

void Ultrasonic_Trigger(uint8_t sensor_index)
{
	g_is_measured[sensor_index] = 0; // 측정 시작 전 플래그 초기화
	switch(sensor_index) {
		case 0: // Sensor 0 (TRIG: PD0)
		PORTD |= (1 << PORTD0);
		_delay_us(10);
		PORTD &= ~(1 << PORTD0);
		break;
		case 1: // Sensor 1 (TRIG: PD2)
		PORTD |= (1 << PORTD2);
		_delay_us(10);
		PORTD &= ~(1 << PORTD2);
		break;
		case 2: // Sensor 2 (TRIG: PD4)
		PORTD |= (1 << PORTD4);
		_delay_us(10);
		PORTD &= ~(1 << PORTD4);
		break;
	}
}


// --- 인터럽트 서비스 루틴 (ISRs) ---

ISR(PCINT2_vect)
{
	// Sensor 0 (PD1)
	if (bit_is_set(PIND, PIND1)) { // 상승 엣지
		pulse_start_time[0] = TCNT1;
		} else { // 하강 엣지
		g_pulse_duration[0] = TCNT1 - pulse_start_time[0];
		g_is_measured[0] = 1;
	}

	// Sensor 1 (PD3)
	if (bit_is_set(PIND, PIND3)) { // 상승 엣지
		pulse_start_time[1] = TCNT1;
		} else { // 하강 엣지
		g_pulse_duration[1] = TCNT1 - pulse_start_time[1];
		g_is_measured[1] = 1;
	}
	
	// Sensor 2 (PD7)
	if (bit_is_set(PIND, PIND7)) { // 상승 엣지
		pulse_start_time[2] = TCNT1;
		} else { // 하강 엣지
		g_pulse_duration[2] = TCNT1 - pulse_start_time[2];
		g_is_measured[2] = 1;
	}
}