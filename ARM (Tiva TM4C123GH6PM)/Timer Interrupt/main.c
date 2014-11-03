#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_timer.h"
#include "inc/hw_gpio.h"

// Initializes the PLL
void Init_PLL(uint8_t div);

int main(void)
{
	// Enable clocks
	SYSCTL_RCGCTIMER_R = 0x1;	// Enable clock for wide timer 0
	SYSCTL_RCGCGPIO_R |= 0x00000020;	// Activate clock for Port F

	// Initialize PLL to 80MHz
	Init_PLL(4);

	// Timer initialization
	TIMER0_CTL_R &= ~0x1;	// Disable timer
	TIMER0_CFG_R = 0;		// 32-bit timer
	TIMER0_TAMR_R |= 0x32;	// Set it to periodic mode, counting up, interrupt enabled
	TIMER0_TAILR_R = 20000000;	// count up to 40 million (0.5sec at 80MHz) before reloading to zero
	TIMER0_TAMATCHR_R = 20000000;	// Trigger interrupt at 40mil
	TIMER0_IMR_R |= 0x10;	// Enable timer A match interrupt

	// Enable Timer0A interrupt in NVIC
	NVIC_EN0_R |= 0x80000;	// Enable Timer0A interrupt in NVIC

	TIMER0_CTL_R |= 0x1;	// Enable timer

	// GPIO Initialization
	GPIO_PORTF_DIR_R = 0x04;			// PF2 (Blue LED) as output
	GPIO_PORTF_DATA_R |= 0x04;			// Initialize it to on
	GPIO_PORTF_DEN_R = 0x04;			// Enable digital IO on PF2

	// Main While Loop
	while(1)
	{
		// Timer does everything :D
	}
}

/**
 * @brief 	Used to enable the PLL and set the system clock.
 * 			Use Table 5-6 (page 224) in datasheet to calculate
 * 			the "div" value (assume that SYSDIV2LSB is the LSB of
 * 			the value you pass in). E.g., a div of "4" would be an
 * 			80MHz clock (a div of 4 being equivalent to a SYSDIV2 of
 * 			0x02 plus a SYSDIV2LSB of 0, for 0b100 = 80MHz).
 *
 * @param 	div The divider value for the PLL
 *
 * @retval 	none
 */
void Init_PLL(uint8_t div)
{
	SYSCTL_RCC2_R |= 0x80000000;	// Use RCC2 bit
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
