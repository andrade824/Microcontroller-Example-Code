#ifndef CONFIG_H
#define	CONFIG_H
#include <xc.h>
#include <inttypes.h>

// PLL Output Divider Options
#define ODIV_1 0
#define ODIV_2 1
#define ODIV_4 2
#define ODIV_8 3
#define ODIV_16 4
#define ODIV_32 5
#define ODIV_64 6
#define ODIV_256 7

// PLL Multiplier Options
#define MUL_15 0
#define MUL_16 1
#define MUL_17 2
#define MUL_18 3
#define MUL_19 4
#define MUL_20 5
#define MUL_21 6
#define MUL_24 7

// PLL Peripheral Bus Divider Options
#define PBDIV_1 0
#define PBDIV_2 1
#define PBDIV_4 2
#define PBDIV_8 3

// Configures the oscillator with the specified multiplier, output divider, and peripheral bus divider
void ConfigureOscillator(uint8_t mult, uint8_t odiv, uint8_t pbdiv);

#endif	/* CONFIG_H */

