#include "../inc/config.h"
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include "../inc/UART.h"

int main(void)
{
	const char const * string = "The UART Works!\n\r";
	
	UARTInit(UBRR);
	int length = strlen(string);
	
	while(1)
	{
		for(int i = 0; i < length; i++)
			UARTTransmit(string[i]);
	}
}