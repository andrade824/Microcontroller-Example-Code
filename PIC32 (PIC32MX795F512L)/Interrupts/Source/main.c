#include <xc.h>
#include "../Include/config.h"
#include "../Include/misc.h"
#include "plib.h"

int main(void)
{
    // Init GPIO
    TRISECLR = 0x0007;
    LATE = 0xFFFF;

    // Init Timers
    T2CON = 0x8070;
    PR2 = 39062;
    T3CON = 0x8070;
    PR3 = 4882;
     
    // Init Interrupts
    IPC2bits.T2IP = 7;
    IPC3bits.T3IP = 1;
    INTEnableSystemMultiVectoredInt(); 
    IEC0bits.T2IE = 1;
    IEC0bits.T3IE = 1;

    while(1) { }

    return 0;
}
