#include <stdint.h>
#include <stdarg.h>
#include "inc/tm4c123gh6pm.h"

/**
 * @brief 	Used to initialize SPI0. Pins:
 * 			PA2 = SSI0Clk (SCLK)
 * 			PA3 = SSI0Fss (Slave select)
 * 			PA4 = SSI0Rx (MISO)
 * 			PA5 = SSI0Tx (MOSI)
 *
 * @param 	div The divider value for the SPI Master clock.
 * 				This can be anywhere from 2 to 254.
 *
 * @retval 	none
 */
void SPIInit(uint8_t div)
{
	int i = 0;
	SYSCTL_RCGCSSI_R |= 0x1;	// Turn clock onto SPI0
	i += 1;						// Wait three clock cycles

	// GPIO Initialization (SPI0 on PA[5:2])
	SYSCTL_RCGCGPIO_R |= 0x00000001;	// Activate clock for Port A
	i += 1;								// Three clock cycle delay for clock to start
	GPIO_PORTA_AFSEL_R |= 0x3C;			// Yes, we want an alternate function on PA[5:2]
	GPIO_PORTA_PCTL_R |= 0x222200;		// The alternate function is SPI0
	GPIO_PORTA_DEN_R |= 0x3C;			// Enable digital IO on PA[5:2]

	// SPI Initialization
	SSI0_CR1_R &= ~(0x2);				// Disable SSI while configuring
	SSI0_CR1_R &= ~(0x4);				// Master mode operation
	SSI0_CPSR_R = div;					// Set clock divider
	SSI0_CR0_R |= 0x7;					// CPOL=0, CPHA=0, 8-bit data
	SSI0_CR1_R |= 0x2;					// Enable SSI while configuring
}

/**
 * @brief 	Transmits byte(s) over SPI0
 *
 * @param 	num The number of bytes to transmit
 * @param	... A variable number of bytes (how many must be specified
 * 				as parameter 1).
 * @retval 	none
 */
void SPISendBytes(uint8_t num, ...)
{
	int i = 0;
	va_list args;

	// Loop through the list of bytes to send and send them
	va_start(args, num);
	for(; i < num; ++i)
	{
		// Put the data into the data register and start transmitting
		SSI0_DR_R = va_arg(args, uint8_t);

		// Wait for the module to stop transmitting (checking busy bit)
		while(SSI0_SR_R & 0x10) { }
	}
	va_end(args);
}

/**
 * @brief 	Reads a byte over SPI
 *
 * @param 	none
 *
 * @retval 	The byte returned by SPI
 */
uint8_t SPIReceiveByte(void)
{
	// Send a dummy byte so we can recieve stuff
	SSI0_DR_R = 0x0;

	// Wait for the module to stop transmitting (checking busy bit)
	while(SSI0_SR_R & 0x10) { }

	// Return the received byte
	return (uint8_t) SSI0_DR_R;
}
