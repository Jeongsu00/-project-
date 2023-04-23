#ifndef _UART_H_
#define _UART_H_

#include <avr/io.h>

void UART_INIT(void);
unsigned char UART_receive(void);
void UART_transmit(unsigned char data);

#endif