#include "../Include/keypad.h"
#include "../Include/misc.h"

/**
 * Assumptions about pinout:
 * Columns 0-3: RB0-RB3 (change notification, analog)
 * Rows 0-3: RB4-RB7 (analog)
 */

// Lookup table for keypad scan codes -> keypad values
const char scancodes[] = { '0', 'F', 'E', 'D', '7', '8', '9', 'C',
                           '4', '5', '6', 'B', '1', '2', '3', 'A' };

/**
 * @brief Initializes the pins for this keypad as noted above under
 *        "Assumptions about pinout".
 *
 * @param none
 *
 * @retval none
 */
void keypad_init_pins(void)
{
    // Set columns as inputs and rows as outputs
    TRISBSET = 0x000F;
    TRISBCLR = 0x00F0;

    // Set rows as open-drain
    ODCBSET = 0x00F0;

    // Turn on pull-ups on column pins
    CNPUESET = 0x003C;

    // Disable analog inputs (aka, turn these into digital pins)
    AD1PCFGSET = 0x00FF;
}

/**
 * @brief Scans the keypad and outputs the scan code, or -1 if nothing pressed
 *
 * @param none
 *
 * @return -1 if nothing pressed, or the scan code otherwise.
 *
 * @note The scan code is in the pattern that the bottom left of the keypad
 *       is zero, and it increments going to the right until the last column
 *       then it restarts at the first column, and one row up. As follows:
 *
 *       C D E F
 *       8 9 A B
 *       4 5 6 7
 *       0 1 2 3
 */
int8_t keypad_scan(void)
{
    int retval = -1;
    int row, col;
    
    // Loop through each row and energize it (pull to ground)
    for(row = 0; row < KP_NUM_ROWS && retval < 0; ++row)
    {
        PORTBSET = 0x00F0;
        PORTBCLR = 16 << row;
        for(col = 0; col < KP_NUM_COLS && retval < 0; ++col)
        {
            // Check if current column is low, if so, it's pressed!
            if(!(PORTB & (1 << col)))
                retval = col + (row << 2);
        }
    }

    // Provide a simple delay to let the button bounce without harm
    keypad_debounce();

    return retval;
}

/**
 * @brief Receives a scancode and continually checks the column bit until the
 *        key is released.
 * @param scancode the key to keep checking
 *
 * @retval none Returns when the key is released
 */
void keypad_lockout(int scancode)
{
    PORTBSET = 0x00F0;
    PORTBCLR = 16 << (scancode >> 2);

    // Keep looping until key is unpressed (bit is zero)
    while(!(PORTB & (1 << (scancode & 0x03)))) { }

    // Provide a simple delay to let the button bounce without harm
    keypad_debounce();
}

/**
 * @brief Provides a simple button debounce
 *
 * @param none
 *
 * @retval none
 */
void keypad_debounce(void)
{
    // Delay 10ms
    delayTicks(10 * CT_MS_TICKS);
}