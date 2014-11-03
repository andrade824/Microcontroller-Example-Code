#ifndef MISC_H
#define	MISC_H
#include <inttypes.h>

// System clock as defined by the PLL Settings
// SYSCLK = ((8MHz / 2) * FPLLMUL) / FPLLODIV
#define SYSCLK 80000000

// Definitions for CoreTimer Ticks in micro or milliseconds
#define CT_US_TICKS SYSCLK / 2000000
#define CT_MS_TICKS SYSCLK / 2000

// Delays the desired amount of CoreTimer ticks
void delayTicks(uint32_t ticks);

#endif	/* MISC_H */

