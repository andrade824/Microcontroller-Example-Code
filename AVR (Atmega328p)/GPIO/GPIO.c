/*
 * AVRTest.c
 *
 * Created: 10/5/2014 3:17:26 AM
 *  Author: Devon
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Initialize PB5 to output
	// _BV is the "Bit Value" macro that just takes the pin number and gives the binary representation (e.g. 1 << 5 = 0x20)
	PORTB &= ~(_BV(PORTB5));	// Clear PB5, so it drives low by default (need to do this before switching it to an output)
	DDRB |= _BV(PORTB5);		// Set PB5 as an output
	
    while(1)
    {
		PINB |= _BV(PORTB5);	// Toggle PB5 by writing a one to the PIN register (14.2.2)
		_delay_ms(50);			// Delay half a second
    }
}