#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_gpio.h"

// Initializes the PLL
void Init_PLL(uint8_t div);

int main(void)
{
	// Input and output variables
	uint8_t In = 0;
	uint8_t Out = 0;

	// Initialize PLL to 80MHz
	Init_PLL(4);

	// GPIO Initialization
	SYSCTL_RCGCGPIO_R |= 0x00000020;	// Activate clock for Port F
	__asm("nop; nop; nop;");			// Three clock cycle delay for clock to start
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;	// Unlock GPIO Port F
	GPIO_PORTF_CR_R = 0x01;				// Allow changes to PF0
	GPIO_PORTF_DIR_R = 0x0E;			// PF4,0 in | PF3-1 out
	GPIO_PORTF_PUR_R = 0x11;			// Enable pull-up on switches
	GPIO_PORTF_DEN_R = 0x1F;			// Enable digital IO on PF4-0

	// Main While Loop
	while(1)
	{
		In = GPIO_PORTF_DATA_R & 0x10;	// Read Sw1
		In >>= 2;
		Out = GPIO_PORTF_DATA_R;
		Out = Out & 0xFB;
		GPIO_PORTF_DATA_R = Out | In;
	}
}

/**
 * @brief 	Used to enable the PLL and set the system clock.
 * 			Use Table 5-6 (page 224) in datasheet to calculate
 * 			the "div" value (assume that SYSDIV2LSB is the LSB of
 * 			the value you pass in). E.g., a div of "4" would be an
 * 			80MHz clock.
 *
 * @param 	div The divider value for the PLL
 *
 * @retval 	none
 */
void Init_PLL(uint8_t div)
{
	SYSCTL_RCC2_R |= 0x80000000;	// Use RCC2 register
	SYSCTL_RCC2_R |= 0x00000800;	// BYPASS2, PLL Bypass
	SYSCTL_RCC_R = (SYSCTL_RCC_R & ~0x7C0) + 0x540;	// Use 16MHz crystal
	SYSCTL_RCC2_R &= ~0x70;			// Configure for MOSC
	SYSCTL_RCC2_R &= ~0x2000;		// Activate PLL by clearing PWRDN
	SYSCTL_RCC2_R |= 0x40000000;	// Use 400MHz PLL
	SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~0x1FC00000) + (div << 22);

	// Wait for the PLL to lock by polling PLLRIS bit
	while((SYSCTL_RIS_R & 0x40) == 0);

	// Enable the PLL by clearing BYPASS
	SYSCTL_RCC2_R &= ~0x800;
}
