#include <xc.h>
#include "../Include/misc.h"

/**
 * @brief Delays the desired number of CoreTimer ticks
 *
 * @param delay how many CoreTimer ticks to delay
 *
 * @retval none
 * 
 * @note Use the CT_US_TICKS and CT_MS_TICKS defines to calculate correct number
 *       of ticks for microsecond and millisecond delays. For instance, to delay
 *       30ms, you would pass in CT_MS_TICKS * 30.
 */
void delayTicks(uint32_t ticks)
{
    // Disable interrupts, so they don't disrupt the delay
    asm volatile("di");

    // Reset timer
    _CP0_SET_COUNT(0);

    // Wait until timer has counted correct number of ticks
    while(_CP0_GET_COUNT() <= ticks) { }

    // Re-enable interrupts
    asm volatile("ei");
}