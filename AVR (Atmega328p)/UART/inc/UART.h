
/*
 * Functions needed to utilize the UART
 *
 * Created: 10/11/2014 11:45:05 AM
 *  Author: Devon Andrade
 */ 
#ifndef UART_H
#define UART_H

#include "../inc/config.h"
#include <inttypes.h>	// gives us uint8_t, uint16_t, etc.

#define BAUD 9600					// Desired baud rate
#define UBRR F_CPU / 16/ BAUD - 1	// Calculated UBRR (baud rate value)

// Initializes the UART with the specified baud rate value
void UARTInit(uint16_t ubrr);

// Transmits one byte of data over the UART via polling
void UARTTransmit(uint8_t data);

#endif