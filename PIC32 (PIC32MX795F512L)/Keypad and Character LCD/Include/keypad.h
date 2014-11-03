#ifndef KEYPAD_H
#define	KEYPAD_H
#include <xc.h>
#include <inttypes.h>

/**
 * Pinout for sparkfun keypad:
 * Column 0: Pin 3
 * Column 1: Pin 1
 * Column 2: Pin 5
 * Row 0: Pin 4
 * Row 1: Pin 6
 * Row 2: Pin 7
 * Row 3: Pin 2
 */

/**
 * Assumptions about pinout:
 * Columns 0-3: RB0-RB3 (change notification, analog)
 * Rows 0-3: RB4-RB7 (analog, RB6 = PGC, RB7 = PGD)
 */

// Define number of rows and columns up to 4x4
#define KP_NUM_ROWS 4
#define KP_NUM_COLS 3

// Initializes the pins for this keypad as noted above under "Assumptions about pinout".
void keypad_init_pins(void);

// Scans the keypad and outputs -1 if nothing pressed, or the scan code otherwise
int8_t keypad_scan(void);

// Receives a scancode and doesn't return until the key is released
void keypad_lockout(int scancode);

// A very simple button debounce
void keypad_debounce(void);

#endif	/* KEYPAD_H */
