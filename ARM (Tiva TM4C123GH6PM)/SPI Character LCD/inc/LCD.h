/*
 * LCD.h
 *
 *  Created on: May 2, 2014
 *      Author: Devon
 *
 *  This file provides functions and macros to make the Digilent
 *  PmodCLS easier to use.
 */

#ifndef LCD_H
#define LCD_H
#include "spi.h"

/**** ALL NUMBERS HAVE TO BE IN ASCII BECAUSE FUCK DIGILENT (Thanks Obama!) ****/

// Set the cursor position
#define LCD_SET_CURSOR(row,col) SPISendBytes(6, 0x1B, '[', row, ';', col, 'H')

// Save the cursor position
#define LCD_SAVE_CURSOR() SPISendBytes(3, 0x1B, '[', 's')

// Restore the cursor position
#define LCD_RESTORE_CURSOR() SPISendBytes(3, 0x1B, '[', 'u')

// Clear display and home cursor
#define LCD_CLEAR() SPISendBytes(3, 0x1B, '[', 'j')

// Erase within line.
// 0 = current position to end of line
// 1 = start of line to current position
// 2 = entire line
#define LCD_ERASE_IN_LINE(where) SPISendBytes(4, 0x1B, '[', where, 'K')

// Erase number of chars in line start at current position
#define LCD_ERASE_CHARS(num) SPISendBytes(4, 0x1B, '[', num, 'N')

// Scroll left a number of columns
#define LCD_SCROLL_LEFT(num) SPISendBytes(4, 0x1B, '[', num, '@')

// Scroll right a number of columns
#define LCD_SCROLL_RIGHT(num) SPISendBytes(4, 0x1B, '[', num, 'A')

// Resets the screen. Equivalent to power cycling the LCD
#define LCD_RESET() SPISendBytes(3, 0x1B, '[', '*')

// Set display mode. 0 = Wrap line at 16 chars, 1 = wrap at 40 chars
#define LCD_DISPLAY_MODE(choice) SPISendBytes(4, 0x1B, '[', choice, 'h')

// Set cursor mode. 0 = cursor off, 1 = cursor on, blink off, 2 = cursor on, blink on
#define LCD_CURSOR_MODE(choice) SPISendBytes(4, 0x1B, '[', choice, 'c')

// Initialize the LCD
void LCDInit(void);

// Sends a string of characters to the LCD
void LCDDisplayString(char * string);

#endif /* LCD_H_ */
