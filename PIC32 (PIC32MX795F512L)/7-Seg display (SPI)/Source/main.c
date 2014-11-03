#include <xc.h>
#include <inttypes.h>
#include "../Include/config.h"
#include "../Include/serial7seg.h"
#include "../Include/misc.h"

int main(void)
{
    // Initialize the SPI Controller for use with the 7seg
    segInit();

    // Clear the screen
    //segWriteCmd(0x76, 0x00);

    // Display 0123 onto the display
    segWriteDisplay('0', '1', '2', '3');

    while(1)
    {
        delayTicks(CT_US_TICKS * 100);
        segWriteDisplay(0x08, 'A', 0x34, 0x13);
    }

    return 0;
}