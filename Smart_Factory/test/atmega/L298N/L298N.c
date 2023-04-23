#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define STEPPING_A_DDR DDRD
#define STEPPING_A PORTD
#define STEPPING_B_DDR DDRC
#define STEPPING_B PORTC

#define STEPPING_A_IN1 PD2
#define STEPPING_A_IN2 PD3
#define STEPPING_A_IN3 PD4
#define STEPPING_A_IN4 PD5

#define STEPPING_B_IN1 PC0
#define STEPPING_B_IN2 PC1
#define STEPPING_B_IN3 PC2
#define STEPPING_B_IN4 PC3

#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED1 PB0
#define LED2 PB1

#define motor_time 20000

void init_stepper()
{
	// 타이머/카운터 2번을 고속 PWM 모드로 설정
	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	TCCR2A |= (1 << COM2A1);		// 비반전 모드
	TCCR2B |= (1 << CS22);			// 분주비 64
	
	
	// stepping motor
	STEPPING_A_DDR |= (1 << STEPPING_A_IN1) | (1 << STEPPING_A_IN2 ) | (1 << STEPPING_A_IN3) | (1 << STEPPING_A_IN4);
	STEPPING_B_DDR |= (1 << STEPPING_B_IN1) | (1 << STEPPING_B_IN2 ) | (1 << STEPPING_B_IN3) | (1 << STEPPING_B_IN4);
	
	// led
	LED_DDR |= (1 << LED1) | (1 << LED2);	// led 상태등 표시 PB0
}

void loop_stepper()
{
	STEPPING_A &= ~((1 << STEPPING_A_IN1) | (1 << STEPPING_A_IN4));		// low
	STEPPING_A |= (1 << STEPPING_A_IN2) | (1 << STEPPING_A_IN3);		// high
	STEPPING_B &= ~((1 << STEPPING_B_IN1) | (1 << STEPPING_B_IN4));
	STEPPING_B |= (1 << STEPPING_B_IN2) | (1 << STEPPING_B_IN3);
	_delay_us(motor_time);

	STEPPING_A &= ~((1 << STEPPING_A_IN1) | (1 << STEPPING_A_IN3));
	STEPPING_A |= (1 << STEPPING_A_IN2) | (1 << STEPPING_A_IN4);
	STEPPING_B &= ~((1 << STEPPING_B_IN1) | (1 << STEPPING_B_IN3));
	STEPPING_B |= (1 << STEPPING_B_IN2) | (1 << STEPPING_B_IN4);
	_delay_us(motor_time);
	
	STEPPING_A &= ~((1 << STEPPING_A_IN2) | (1 << STEPPING_A_IN3));
	STEPPING_A |= (1 << STEPPING_A_IN1) | (1 << STEPPING_A_IN4);
	STEPPING_B &= ~((1 << STEPPING_B_IN2) | (1 << STEPPING_B_IN3));
	STEPPING_B |= (1 << STEPPING_B_IN1) | (1 << STEPPING_B_IN4);
	_delay_us(motor_time);

	STEPPING_A &= ~((1 << STEPPING_A_IN2) | (1 << STEPPING_A_IN4));
	STEPPING_A |= (1 << STEPPING_A_IN1) | (1 << STEPPING_A_IN3);
	STEPPING_B &= ~((1 << STEPPING_B_IN2) | (1 << STEPPING_B_IN4));
	STEPPING_B |= (1 << STEPPING_B_IN1) | (1 << STEPPING_B_IN3);
	_delay_us(motor_time);
}

int main(void)
{
	init_stepper();
	


	while (1)
	{
		LED_PORT |= (1 << LED1);
		loop_stepper();
		LED_PORT &= ~(1 << LED1);
		loop_stepper();
	}
	
	return 0;
}