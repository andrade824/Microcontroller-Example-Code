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

// The CMPA values to move the servo to certain positions
#define PWM_LEFT 6031
#define PWM_CENTER 5781
#define PWM_RIGHT 5531

int main(void)
{
	int i = 0;

	// Initialize PLL to 20MHz
	INITIALIZE_PLL();

	// GPIO Initialization (M0PWM0 on PB6)
	SYSCTL_RCGCGPIO_R |= 0x00000002;	// Activate clock for Port B
	i += 1;								// Three clock cycle delay for clock to start
	GPIO_PORTB_DIR_R = 0x40;			// PB6 output
	GPIO_PORTB_AFSEL_R = 0x40;			// Yes, we want an alternate function on PB6
	GPIO_PORTB_PCTL_R = 0x4000000;		// The alternate function is M0PWM0 (alternate 4)
	GPIO_PORTB_DEN_R = 0x40;			// Enable digital IO on PB6

	// PWM Initialization
	SYSCTL_RCGCPWM_R |= 0x1;			// Activate clock for PWM Module 0
	i += 1;								// Three clock cycle delay
	SYSCTL_RCC_R |= 0x1E0000;			// Use PWM Clock divider of 64 (SYSCLK / 64)
	PWM0_0_CTL_R = 0;					// Disable PWM while configuring
	PWM0_0_GENA_R = 0x8C;				// High on load, invert on CompA down
	PWM0_0_LOAD_R = 6250;				// Period of 50Hz (20ms) when SYSCLK=20MHz
	PWM0_0_CMPA_R = 5937;				// Default to pulse width of 1ms
	PWM0_0_CTL_R = 0x1;					// Turn on PWM0 in Count-down mode
	PWM0_ENABLE_R = 0x1;				// Enable PWM output for M0PWM0

	// Main While Loop
	while(1)
	{
		PWM0_0_CMPA_R = PWM_LEFT;
		SysTickDelay(500 * ST_MS);

		PWM0_0_CMPA_R = PWM_CENTER;
		SysTickDelay(500 * ST_MS);

		PWM0_0_CMPA_R = PWM_RIGHT;
		SysTickDelay(500 * ST_MS);

		PWM0_0_CMPA_R = PWM_CENTER;
		SysTickDelay(500 * ST_MS);
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
