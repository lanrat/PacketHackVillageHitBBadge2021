#ifndef UART_H
#define UART_H

#include <stdlib.h>

void uart_send(unsigned char d)
{
	while ((UCSRA & 0X20) == 0)
	{
	}
	UDR = d;
}

unsigned char uart_rec(void)
{
	if ((UCSRA & 0X80) == 0x80)
		return UDR;
	else
		return 0;
}

void init_uart(void)
{
	UCSRA |= (1 << U2X);
	UCSRB |= (1 << TXEN) | (1 << RXEN);
	UBRRL = 12;
}

void uart_string(char *data)
{
	while (*data)
	{
		uart_send(*data);
		*data++;
	}
}

void uart_transmit(int value)
{
	char buffer[5] = {0};
	itoa(value, buffer, 10);
	uart_string(buffer);
	uart_send(32);
}

#endif
