# ATmega328p로 L298N을 이용하여 stepping motor 돌리기

[아래의 코드를 사용하면 영상과 같이 된다. (링크공개 영상)](https://youtu.be/AbVaCdjIxz4)

사용한 모터 : [유니폴라 스테핑 모터](https://www.devicemart.co.kr/goods/view?no=1357347)  
하지만 [L298N](https://www.devicemart.co.kr/goods/view?no=1278835)은 바이폴라 드라이버.  
유티폴라 모터를 바이폴라 형식으로 돌릴 수 있어 가능하였음.  

ENA, ENB는 ATmega328p에 연결하지 않고 +에 연결하였음. (핀을 줄이기 위함)  
ATmega328p 핀에 연결하여도 괜찮음.  
스테핑모터를 같은 포트에 연결하고 싶었지만 PORTD의 일부는 UART통신, PORTC의 일부는 i2c통신을 사용하고 있으므로 나누어 사용함   

아래는 main.c의 코드와 동일함.  


``` C
﻿#define F_CPU 16000000L
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
```
