#ifndef LCD_H
#define	LCD_H
#include <inttypes.h>

/**
 * Assumptions about Pin-out for selected port:
 * Rx0-Rx7: Data Lines 0-7 (Rx0 = DB0, Rx1 = DB1, etc.)
 * Rx8: R/S (Register Select)
 * Rx9: R/W (Read/Write)
 * Rx10: E (Enable)
 */

// Replace the port registers below with the port you want to use
#define LCDPORT PORTD
#define LCDPORTSET PORTDSET
#define LCDPORTCLR PORTDCLR
#define LCDTRIS TRISD
#define LCDTRISSET TRISDSET
#define LCDTRISCLR TRISDCLR

// Helper Macros for common commands
#define mLCDClear() LCDSendCommand(0x01)            // Clears screen and cursor
#define mLCDScrollRight() LCDSendCommand(0x1E)      // Scroll display one character right
#define mLCDScrollLeft() LCDSendCommand(0x18)       // Scroll display one character left
#define mLCDCursorHome() LCDSendCommand(0x02)       // Cursor moves to top left
#define mLCDCursorRight() LCDSendCommand(0x14)      // Move cursor right one
#define mLCDCursorLeft() LCDSendCommand(0x10)       // Move cursor left one
#define mLCDUnderlineCursor() LCDSendCommand(0x0E)  // Visible underline cursor
#define mLCDBlinkingCursor() LCDSendCommand(0x0F)   // Visible blinking cursor
#define mLCDHideCursor() LCDSendCommand(0x0C)       // Invisible cursor
#define mLCDHideDisplay() LCDSendCommand(0x08)      // Blank display (without clearing)
#define mLCDRestoreDisplay() LCDSendCommand(0x0C)   // Restore display (with cursor hidden)
// Set cursor to the specified row and column
#define mLCDSetCursor(row, column) LCDSendCommand(0x80 | ((row << 6) + column))

// Initialize the pins and LCD
void LCDInitialize(void);

// Send a single character
void LCDSendChar(char character);

// Send a full string
void LCDSendString(char * str);

// Clears the screen
void LCDSendCommand(uint8_t cmd);

// Polls the busy flag and returns when the busy flag is low
void LCDPollBusyFlag(void);

#endif	/* LCD_H */

