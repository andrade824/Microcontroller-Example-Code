#ifndef NESCONTROLLER_H_
#define NESCONTROLLER_H_

#include <stdint.h>

/**
 * GPIO MAP:
 *
 * PD0 = NES_CLK
 * PD1 = NES_LATCH
 * PD2 = NES_DATA
 */

// Port registers for all of the NES pins
#define NESPORT GPIO_PORTD_DATA_R
#define NESPORT_DIR GPIO_PORTD_DIR_R
#define NESPORT_DEN GPIO_PORTD_DEN_R

// Pin Masks
#define NES_CLK 1
#define NES_LATCH 2
#define NES_DATA 4

// Pin numbers, used for shifting values together
#define NES_CLK_S 0
#define NES_LATCH_S 1
#define NES_DATA_S 2

#define ALL_NES_PINS (NES_CLK | NES_LATCH | NES_DATA)

typedef struct NesData_t
{
	uint8_t A : 1;
	uint8_t B : 1;
	uint8_t Select : 1;
	uint8_t Start : 1;
	uint8_t Up : 1;
	uint8_t Down : 1;
	uint8_t Left : 1;
	uint8_t Right : 1;
} NesData;

// Initialize the pins needed to gather controller input
void InitController(void);

// Gather input and return it as a NesData structure
NesData GetInput(void);

#endif /* NESCONTROLLER_H_ */
