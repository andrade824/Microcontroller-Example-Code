/*
 * Functions needed to utilize the UART
 *
 * Created: 10/11/2014 11:45:14 AM
 *  Author: Devon Andrade
 */ 
#include "../inc/UART.h"
#include <avr/io.h>

/**
*	Initializes the UART with the specified baud rate value. Must be called before calling
*	other UART functions.
*
*	20.11 has descriptions of the registers used in this function.
*
*	@param ubrr The baud rate value to set the UART to (20.10 for a table of baud rate values)
*
*	@return none
*/
void UARTInit(uint16_t ubrr)
{
	// Set Baud rate
	UBRR0H = (uint8_t) (ubrr >> 8);	// The 8 highest bits of ubrr
	UBRR0L = (uint8_t) ubrr;		// The 8 lowest bits of ubrr
	
	// Enable transmitter
	UCSR0B = _BV(TXEN0);
	
	// By default, the UART sends 8-bits of data with one stop bit
	// So, no need for initialization
}

/**
*	Transmits one byte of data over the UART via polling
*
*	@param data The byte of data to send
*
*	@return none
*/
void UARTTransmit(uint8_t data)
{
	// Wait for the transmit buffer to become empty (20.6.1)
	while((UCSR0A & _BV(UDRE0)) == 0) { }
		
	// Put data into the buffer, the hardware will then send it
	UDR0 = data;
}