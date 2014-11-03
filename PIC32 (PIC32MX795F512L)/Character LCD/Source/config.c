#include "../Include/config.h"

/**
 * @brief   Configures the oscillator with the specified multiplier,
 *          output divider, and peripheral bus divider.
 *
 *          SYSCLK = ((8MHz / 2) * MUL) / ODIV
 *          PBCLK = SYSCLK / PBDIV
 *
 * @param mult PLL Multiplier option
 * @param odiv PLL Output divider option
 * @param pbdiv PLL Peripheral Bus divider option
 * 
 * @retval none
 */
void ConfigureOscillator(uint8_t mult, uint8_t odiv, uint8_t pbdiv)
{
    SYSKEY = 0x0;           // Make sure OSCCON is locked
    SYSKEY = 0xAA996655;    // Write Key1 to SYSKEY
    SYSKEY = 0x556699AA;    // Write Key2 to SYSKEY

    OSCCONbits.PLLMULT = mult;
    OSCCONbits.PBDIV = odiv;
    OSCCONbits.PLLODIV = pbdiv;

    // Relock the SYSKEY
    SYSKEY = 0x0;           // Write any value other than Key1 or Key2
}

/**
 * @brief Delays the desired amount of microseconds
 *
 * @param delay how many microseconds to delay
 *
 * @retval none
 */
void delayMicro(uint32_t delay)
{
    // Disable interrupts, so they don't disrupt the delay
    asm("di");

    // Reset timer
    _CP0_SET_COUNT(0);
    
    // Calculate number of CoreTimer ticks needed
    int ticks = (SYSCLK / 2000000) * delay;

    // Wait until timer has counted correct number of ticks
    while(_CP0_GET_COUNT() <= ticks) { }

    // Re-enable interrupts
    asm("ei");
}

/**
 * @brief Delays the desired amount of milliseconds
 *
 * @param delay how many milliseconds to delay
 *
 * @retval none
 */
void delayMilli(uint32_t delay)
{
    // Disable interrupts, so they don't disrupt the delay
    asm("di");
    
    // Reset timer
    _CP0_SET_COUNT(0);

    // Calculate number of CoreTimer ticks needed
    int ticks = (SYSCLK / 2000) * delay;

    // Wait until timer has counted correct number of ticks
    while(_CP0_GET_COUNT() <= ticks) { }
    
    // Re-enable interrupts
    asm("ei");
}