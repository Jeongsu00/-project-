#define F_CPU 16000000L
#define TERMINATOR '$'
#include <avr/io.h>        // include the AVR IO library
#include <util/delay.h>    // include the delay library
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include "UART/Uart.h"
#include "Pca9685/Pca9685.h" // include the PCA9685 library

#define STEPPING_A_DDR DDRD
#define STEPPING_A PORTD

#define STEPPING_A_IN1 PD2
#define STEPPING_A_IN2 PD3
#define STEPPING_A_IN3 PD4
#define STEPPING_A_IN4 PD5

#define motor_time 20000


// 스테핑모터 초기화
void INIT_STEPPER();
// 스테핑모터 돌리기
void loop_stepper();

void INIT_STEPPER()
{
	// 타이머/카운터 2번을 고속 PWM 모드로 설정
	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	TCCR2A |= (1 << COM2A1);		// 비반전 모드
	TCCR2B |= (1 << CS22);			// 분주비 64
	
	
	// stepping motor
	STEPPING_A_DDR |= (1 << STEPPING_A_IN1) | (1 << STEPPING_A_IN2 ) | (1 << STEPPING_A_IN3) | (1 << STEPPING_A_IN4);
}

void loop_stepper()
{
	STEPPING_A &= ~((1 << STEPPING_A_IN1) | (1 << STEPPING_A_IN4));		// low
	STEPPING_A |= (1 << STEPPING_A_IN2) | (1 << STEPPING_A_IN3);		// high
	_delay_us(motor_time);

	STEPPING_A &= ~((1 << STEPPING_A_IN1) | (1 << STEPPING_A_IN3));
	STEPPING_A |= (1 << STEPPING_A_IN2) | (1 << STEPPING_A_IN4);
	_delay_us(motor_time);
	
	STEPPING_A &= ~((1 << STEPPING_A_IN2) | (1 << STEPPING_A_IN3));
	STEPPING_A |= (1 << STEPPING_A_IN1) | (1 << STEPPING_A_IN4);
	_delay_us(motor_time);

	STEPPING_A &= ~((1 << STEPPING_A_IN2) | (1 << STEPPING_A_IN4));
	STEPPING_A |= (1 << STEPPING_A_IN1) | (1 << STEPPING_A_IN3);
	_delay_us(motor_time);
}

int main(void)
{
	int index = 0;			// 수신 버퍼에 저장할 위치
	char buffer[20] = "";	// 수신 데이터 버퍼
	char data;				// 수신 데이터
	
	UART_INIT();			// UART 통신 초기화
	INIT_STEPPER();			// stepping motor 초기화
	
	pca9685_init(0x00, 50); // start PCA9685 device 0x00 at 50 Hz output
	_delay_ms(5);
	int8_t angle = 0;
	pca9685_servo(0, 0);
	pca9685_servo(1, 0);
	pca9685_servo(2, 0);
	pca9685_servo(3, 0);
	pca9685_servo(4, 0);
	pca9685_servo(8, 0);
	pca9685_servo(9, 0);
	pca9685_servo(10, 0);
	pca9685_servo(11, 0);
	pca9685_servo(12, 0);
	_delay_ms(1000);
	
	while(1)
	{
		data = UART_receive();	// 데이터 수신
		buffer[index] = data;
		
		if(strcmp(buffer, "1") == 0)
		{
		int angle2 = -15;
			for (angle = -15; angle <= 15; angle += 3) 
			{
				pca9685_servo(0, angle);
				pca9685_servo(1, angle2);
				pca9685_servo(2, angle2);
				_delay_ms(100);
			}
			for (angle = -15; angle <= 15; angle += 3)
			{
				pca9685_servo(1, angle);
				pca9685_servo(2, angle2);
				_delay_ms(100);
			}
			for (angle = -15; angle <= 15; angle += 3)
			{
				pca9685_servo(2, angle);
				_delay_ms(100);
			}
			for (angle = -15; angle <= 15; angle += 3)
			{
				pca9685_servo(8, angle);
				pca9685_servo(9, angle2);
				pca9685_servo(10, angle2);
				_delay_ms(100);
			}
			for (angle = -15; angle <= 15; angle += 3)
			{
				pca9685_servo(9, angle);
				pca9685_servo(10, angle2);
				_delay_ms(100);
			}
			for (angle = -15; angle <= 15; angle += 3)
			{
				pca9685_servo(10, angle);
				_delay_ms(100);
			}
		}
		else if(strcmp(buffer, "2") == 0)
		{
		int angle3 = 15;
			for (angle = 15; angle >= -15; angle -= 3) 
			{
				pca9685_servo(0, angle);
				pca9685_servo(1, angle3);
				pca9685_servo(2, angle3);
				_delay_ms(100);
			}
			for (angle = 15; angle >= -15; angle -= 3)
			{
				pca9685_servo(1, angle);
				pca9685_servo(2, angle3);
				_delay_ms(100);
			}
			for (angle = 15; angle >= -15; angle -= 3)
			{
				pca9685_servo(2, angle);
				_delay_ms(100);
			}
		}
		else if(strcmp(buffer, "3") == 0)
		{	
			while (1)
			{
				loop_stepper();
				
				int index = 0;			// 수신 버퍼에 저장할 위치
				char buffer[20] = "";	// 수신 데이터 버퍼
				char data;				// 수신 데이터
				
				data = UART_receive();	// 데이터 수신
				buffer[index] = data;
				
				if(strcmp(buffer, "4") == 0)
					
					break;
			}
		}
		else if(strcmp(buffer, "s") == 0){
			UART_transmit(data);
			OCR1B = (0x04) | (0x08);
			_delay_ms(200);
			PORTB = 0x00;
			index = 0;
		}
		else{
			UART_transmit(data);
			index = 0;
		}
	}
}