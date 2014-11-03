#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

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

int main(void)
{
	// Initialize PLL to 20MHz
	INITIALIZE_PLL();

	// GPIO Initialization
	SYSCTL_RCGCGPIO_R |= 0x00000020;	// Activate clock for Port F
	__asm("nop; nop; nop;");			// Three clock cycle delay for clock to start
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;	// Unlock GPIO Port F
	GPIO_PORTF_CR_R = 0x01;				// Allow changes to PF0
	GPIO_PORTF_DIR_R = 0x0E;			// PF4,0 in | PF3-1 out
	GPIO_PORTF_PUR_R = 0x11;			// Enable pull-up on switches
	GPIO_PORTF_DEN_R = 0x1F;			// Enable digital IO on PF4-0
	GPIO_PORTF_DATA_R = 0;

	// Main While Loop
	while(1)
	{
		GPIO_PORTF_DATA_R ^= 0x2;
		if(GPIO_PORTF_DATA_R & 0x10)
			SysTickDelay(500 * ST_MS);
		else
			SysTickDelay(250 * ST_MS);
	}
}

/**
 * @brief 	Used to enable the PLL and set the system clock.
 * 			To calculate the new clock, use the following:
 *
 * 			New Clock = 400MHz / (div + 1)
 *
 * 			So, div = 4 would yield an 80MHz clock.
 *
 * 			"div" value must be between 4 and 127
 *
 * @param 	div The divider value for the PLL
 *
 * @retval 	none
 */
void InitPLL(uint8_t div)
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

void SysTickDelay(uint32_t delay)
{
	NVIC_ST_RELOAD_R = delay - 1;
	NVIC_ST_CURRENT_R = 0;	// Clear the current register and COUNT bit
	NVIC_ST_CTRL_R = 5;		// Turn on timer

	// Wait for timer to loop around
	while((NVIC_ST_CTRL_R & 0x10000) == 0);

	NVIC_ST_CTRL_R = 0;		// Turn off timer
}
