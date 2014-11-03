#include <xc.h>
#include "../Include/misc.h"
#include "../Include/LCD.h"

/**
 * Assumptions about Pin-out for selected port:
 * Rx0-Rx7: Data Lines 0-7 (Rx0 = DB0, Rx1 = DB1, etc.)
 * Rx8: R/S (Register Select)
 * Rx9: R/W (Read/Write)
 * Rx10: E (Enable)
 */

/**
 * @brief Initialize the pins and LCD.
 *        Default Settings:
 *        - 8-Bit operation, with 2 lines display
 *        - Auto-move cursor to the right after a data write
 *        - Turn on display with blinking cursor
 *
 * @retval none
 */
void LCDInitialize(void)
{
    // Wait 20ms for LCD to power up
    delayTicks(20 * CT_MS_TICKS);

    // Set every LCD pin as an output
    LCDTRISCLR = 0x07FF;

    // Send Set Interface length (8-bit, 2 lines)
    LCDSendCommand(0x38);

    // Clear and home display
    LCDSendCommand(0x01);

    // Auto-move cursor to the right after displaying character
    LCDSendCommand(0x06);

    // Turn on display, hide cursor
    LCDSendCommand(0x0C);
}

/**
 * @brief Sends a single character to the display.
 *
 * @param character the ascii code of the character to display
 *
 * @retval none
 */
void LCDSendChar(char character)
{
    // Make sure the LCD is ready to process a command
    LCDPollBusyFlag();

    // Clear all lines, then set the data lines and R/S
    LCDPORTCLR = 0xFFFF;
    LCDPORTSET = 0x0100 | character;

    // Strobe enable line
    LCDPORTSET = 0x0400;
    delayTicks(1 * CT_US_TICKS);
    LCDPORTCLR = 0x0400;
}

/**
 * @brief Sends a full string of null-terminated text
 *
 * @param str A null-terminated string of characters
 *
 * @retval none
 */
void LCDSendString(char * str)
{
    while(*str)
        LCDSendChar(*str++);
}

/**
 * @brief Sends a command to the display
 *
 * @param cmd The command to send (8-bits of the data lines)
 *
 * @retval none
 */
void LCDSendCommand(uint8_t cmd)
{
    // Make sure the LCD is ready to process a command
    LCDPollBusyFlag();
    
    // Clear all lines, then set the data lines
    LCDPORTCLR = 0xFFFF;
    LCDPORTSET = cmd;
    
    // Strobe enable line
    LCDPORTSET = 0x0400;
    delayTicks(1 * CT_US_TICKS);
    LCDPORTCLR = 0x0400;
}

/**
 * @brief Polls the busy flag and returns when the busy flag is low
 *
 * @retval none
 */
void LCDPollBusyFlag(void)
{
    // R/S = 0, R/W = 1, and DB7 as input
    LCDTRISSET = 0x0080;
    LCDPORT = 0x0200;

    // Poll DB7 until it's cleared
    do
    {
        // Strobe enable line
        LCDPORTCLR = 0x0400;
        delayTicks(1 * CT_US_TICKS);
        LCDPORTSET = 0x0400;
    } while(LCDPORT & 0x0080);

    // Reset DB7 as output and set enable low
    LCDTRISCLR = 0x0080;
    LCDPORTCLR = 0x0400;
}
