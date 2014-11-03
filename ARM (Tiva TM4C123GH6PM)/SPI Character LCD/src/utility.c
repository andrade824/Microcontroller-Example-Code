#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

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

/**
 * @brief 	Provides a delay. Use the constants ST_US
 * 			and ST_MS to create microsecond and
 * 			millisecond delays. For instance, for a 50ms
 * 			delay:
 *
 * 			SysTickDelay(ST_MS * 50);
 *
 * @param 	delay The number of cycles to delay
 *
 * @retval 	none
 */
void SysTickDelay(uint32_t delay)
{
	NVIC_ST_RELOAD_R = delay - 1;
	NVIC_ST_CURRENT_R = 0;	// Clear the current register and COUNT bit
	NVIC_ST_CTRL_R = 5;		// Turn on timer

	// Wait for timer to loop around
	while((NVIC_ST_CTRL_R & 0x10000) == 0);

	NVIC_ST_CTRL_R = 0;		// Turn off timer
}
