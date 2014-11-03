/*
 * spi.h
 *
 *  Created on: May 2, 2014
 *      Author: Devon
 *
 *  This file contains functions for sending data over SPI
 */
#ifndef SPI_H
#define SPI_H
#include <stdint.h>

// Initialize the SPI0 module
void SPIInit(uint8_t div);

// Transmit a byte over SPI
void SPISendBytes(uint8_t num, ...);

// Reads a byte over SPI
uint8_t SPIReceiveByte(void);

#endif
