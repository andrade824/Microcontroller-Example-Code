/**
 * @brief This is a proof of concept project that scans a keypad (up to 4x4)
 *        and displays the value on an LCD.
 *
 * @note Assumptions about keypad:
 *       Set number of rows and columns in keypad.h (up to 4x4).
 * 
 *       Unfortunately, RB6 and RB7 are also programming pins. Will have to
 *       unplug the jumpers when programming, and plug them back in afterwards.
 *
 *       Keypad pin-out:
 *       Columns 0-3: RB0-RB3 (all change notification, all analog)
 *       Rows 0-3: RB4-RB7 (all analog, RB6 = PGC, RB7 = PGD)
 *
 * @note Assumptions about LCD:
 *       Modify defines in LCD.h to fit what port you're using.
 *
 *       LCD pin-out for selected port:
 *       Rx0-Rx7: Data Lines 0-7 (Rx0 = DB0, Rx1 = DB1, etc.)
 *       Rx8: R/S (Register Select)
 *       Rx9: R/W (Read/Write)
 *       Rx10: E (Enable)
 */
#include <xc.h>
#include <inttypes.h>
#include "../Include/config.h"
#include "../Include/misc.h"
#include "../Include/LCD.h"
#include "../Include/keypad.h"

// Grab the scancodes from keypad.c
extern const char scancodes[];

int main(void)
{
    int8_t key = -1;   // currently pressed key
    
    // Initialize LCD and Keypad
    LCDInitialize();
    keypad_init_pins();

    // Write default LCD messages
    LCDSendString("Key Press: Off");
    mLCDSetCursor(1, 0);
    LCDSendString("Key Value: ");

    while(1)
    {
        // Scan for a key
        key = keypad_scan();

        // If a key is pressed, display it
        if(key >= 0)
        {
            // Display that a key was pressed
            mLCDSetCursor(0, 12);
            LCDSendString("n ");
            mLCDSetCursor(1, 11);
            LCDSendChar(scancodes[key]);

            // Wait until key is unpressed
            keypad_lockout(key);

            // Display that it was unpressed
            mLCDSetCursor(0, 12);
            LCDSendString("ff");
            mLCDSetCursor(1, 11);
            LCDSendChar(' ');
        }
    }

    return 0;
}