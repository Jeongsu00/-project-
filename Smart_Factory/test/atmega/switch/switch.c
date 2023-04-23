#define F_CPU 16000000L
#include <avr/io.h> // include the AVR IO library
#include <util/delay.h> // include the delay library

#define switch1 PB2
#define LED1 PB0
#define LED2 PB1

int main(void)
{
	// 상태등 켜기
	DDRB |= (1 << LED1) | (1 << LED2);
	DDRB &= ~(1 << switch1);
	
	PORTB |= (1 << LED1);
	PORTB |= (1 << LED2);
	
	while (1){
		if (!(PINB & (1 << switch1))) {
			// 스위치를 누르면 LED OFF
			PORTB &= ~(1 << LED2);
		}
		else {
			PORTB |= (1 << LED2);
		}
	}

	return 0;
}