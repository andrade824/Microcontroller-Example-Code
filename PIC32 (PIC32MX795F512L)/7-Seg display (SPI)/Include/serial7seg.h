/* 
 * File:   serial7seg.h
 * Author: Devon
 *
 * Created on December 24, 2013, 6:10 PM
 */

#ifndef SERIAL7SEG_H
#define	SERIAL7SEG_H
#include <xc.h>
#include <inttypes.h>

// Change these registers to the SPI port you're using
#define SPICON SPI2CON
#define SPIBRG SPI2BRG
#define SPIBUF SPI2BUF
#define SPISTATBITS SPI2STATbits

// Change this to what port and pin you're using for the Slave Select
#define SSTRISCLR TRISCCLR
#define SSLATSET LATCSET
#define SSLATCLR LATCCLR
#define SSPINMASK 0x0008    // C3

/* Change these settings to modify the configuration and baud rate */
// Turns on SPI, configured for Mode 0 (idle low, sample on rising edge), master mode
#define SPI_CONF 0x8020
// Baud rate formula: Fsck = PBclk / (2 * (SPIBRG + 1))
// Example: 10000000 / (2 * (21 + 1)) = 227.273KHz
#define SPI_BAUD 21

// Initialize the SPI controller used to communicate with the display
void segInit(void);

// Transmit a single byte over SPI, and return the received byte
uint8_t writeSPIByte(uint8_t data);

// Write out four numbers to the display
void segWriteDisplay(uint8_t num1, uint8_t num2, uint8_t num3, uint8_t num4);

// Send a special command
void segWriteCmd(uint8_t cmd, uint8_t data);

#endif	/* SERIAL7SEG_H */

