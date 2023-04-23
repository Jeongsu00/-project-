#define F_CPU 16000000L
#include <avr/io.h> // include the AVR IO library
#include <util/delay.h> // include the delay library

#define LED1 PB0

int main(void)
{
	DDRB |= (1 << LED1);
	
	while (1) {
		PORTB |= (1 << LED1);
		_delay_ms(100);
		PORTB &= ~(1 << LED1);
		_delay_ms(100);
		
	}
	return 0;
}