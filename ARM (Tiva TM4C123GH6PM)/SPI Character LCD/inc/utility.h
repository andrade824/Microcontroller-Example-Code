/*
 * utility.h
 *
 *  Created on: May 2, 2014
 *      Author: Devon
 *
 *  This file contains utility functions for use with the Tiva C microcontroller
 */

#ifndef UTILITY_H_
#define UTILITY_H_

// System clock (MHz)
#define SYSCLK 20000000

// Used in delay calculations
#define ST_US (SYSCLK / 1000000)
#define ST_MS (SYSCLK / 1000)

// Macro to set the system clock to the defined SYSCLK
#define INITIALIZE_PLL() InitPLL((400000000 / SYSCLK) - 1)

// Initializes the PLL
void InitPLL(uint8_t div);

// Delays using the SysTick timer
void SysTickDelay(uint32_t delay);

#endif /* UTILITY_H_ */
