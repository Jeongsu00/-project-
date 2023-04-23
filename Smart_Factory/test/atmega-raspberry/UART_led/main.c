#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UART.h"

#define LED_PIN1 PB0
#define LED_PIN2 PB1

int main(int argc, char *argv[])
{
	int index = 0;
	char buffer[20] = "";
	
	unsigned char data;
	UART_INIT(); // UART 통신 초기화
	
	DDRB |= (1 << LED_PIN1) | (1 << LED_PIN2); // set PB0, PB1 as output
	
	while (1) {
		PORTB |= (1 << LED_PIN1);		// 신호 확인용. PB0 high
		data = UART_receive(); // 데이터 수신
		buffer[index] = data;
		
		if(strcmp(buffer, "h") == 0) {
			PORTB |= (1 << LED_PIN2);	// PB1 high
			UART_transmit(data);	// 수신된 문자를 에코 백
			index = 0;
		}
		
		else if(strcmp(buffer, "l") == 0) {
			PORTB &= ~(1 << LED_PIN2);;	// PB2 low
			UART_transmit(data);
			index = 0;
		}
		
		else{
			UART_transmit(data);
			index = 0;
		}
		PORTB &= ~0x01;	
	}

	return 0;
}