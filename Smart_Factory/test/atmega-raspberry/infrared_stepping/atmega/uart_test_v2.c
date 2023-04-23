#define F_CPU 16000000L
#define TERMINATOR '$'
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
//#include <stdbool.h>
#include "UART.h"

// 스테핑모터
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

// LED
#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED1 PB0
#define LED2 PB1

// uart
int index = 0;				// 수신 버퍼에 저장할 위치
int process_data = 0;		// 문자열 처리
char buffer[20] = "";		// 수신 데이터 버퍼
char buffer_data[20];
char data;					// 수신 데이터

#define motor_time 20000


// 스테핑모터 초기화
void INIT_STEPPER();
// 스테핑모터 돌리기
void loop_stepper();
// uart
void uart_RasToAt();

int main(void)
{
	char stepping_can_move = "none";
	int stop = 1;
	
	UART_INIT();				// UART 통신 초기화
	
	LED_DDR |= (1 << LED1) | (1 << LED2);
	
	UART_printString("====stepping motor====");
	UART_printString(stepping_can_move);
	//UART_print16bitNumber(counter);
	UART_printString("\n");
	
	while(1)
	{
		uart_RasToAt();
		
		if(process_data == 1){		// 문자열 처리
			strcpy(buffer_data, buffer);
			if((strcmp(buffer_data, "mov") != 0) && (strcmp(buffer_data, "stp") != 0)){
				UART_printString("** Unknown Command **\t: ");
				UART_printString(buffer);
				UART_printString("\n");
			}
			else if (strcmp(buffer_data, "mov") == 0) {
				UART_printString("MOVE!");
				UART_printString("\n");
				
				while(!(strcmp(buffer_data, "stp") == 0)){
					UART_printString("STOP!!");
					UART_printString("\n");
					uart_RasToAt();
					loop_stepper();
				}
			}
			index = 0;
			process_data = 0;
		}
	}
}

void uart_RasToAt(){
	data = UART_receive();	// 데이터 수신
	if (data != ""){
		if(data == TERMINATOR) {	// 종료 문자를 수신한 경우
			buffer[index] = '\0';
			process_data = 1;		// 수신 문자열 처리 지시
		}
		else{
			buffer[index] = data;	// 수신 버퍼에 저장
			index++;
		}
	}
	
}

void INIT_STEPPER()
{
	// 타이머/카운터 2번을 고속 PWM 모드로 설정
	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	TCCR2A |= (1 << COM2A1);		// 비반전 모드
	TCCR2B |= (1 << CS22);			// 분주비 64
	
	
	// stepping motor
	STEPPING_A_DDR |= (1 << STEPPING_A_IN1) | (1 << STEPPING_A_IN2 ) | (1 << STEPPING_A_IN3) | (1 << STEPPING_A_IN4);
	STEPPING_B_DDR |= (1 << STEPPING_B_IN1) | (1 << STEPPING_B_IN2 ) | (1 << STEPPING_B_IN3) | (1 << STEPPING_B_IN4);
	
	// led
	//LED_DDR |= (1 << LED1) | (1 << LED2);	// led 상태등 표시 PB0
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
