#include <xc.h>
#include <inttypes.h>
#include "../Include/config.h"
#include "../Include/LCD.h"

int main(void)
{
    // SYSCLK: 10MHz, PBCLK: 1.25MHz
    ConfigureOscillator(MUL_20, ODIV_8, PBDIV_8);

    // Initialize the LCD
    LCDInitialize();
    
    LCDSendString("Hello World");
    mLCDSetCursor(1, 0);
    LCDSendString("Look ma 2 lines!");

    TRISE = 0x0040;         // RE6 as input (user button), all else as output
    uint8_t pressed = 0;    // Button state, used as a simple debounce

    while(1)
    {
        // pressed is 0 and button (active low) is being pressed
        if(!pressed && !(PORTE & 0x0040))
        {
            mLCDScrollRight();
            pressed = 1;
        } else if (pressed && (PORTE & 0x0040))
            pressed = 0; // button has been released, so reset pressed state
    }

    return 0;
}