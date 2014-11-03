#include <xc.h>
#include <inttypes.h>

#include "../Include/config.h"

int main(void)
{
    // SYSCLK: 10MHz, PBCLK: 1.25MHz
    ConfigureOscillator(MUL_20, ODIV_8, PBDIV_8);

    TRISE = 0x0000;     // Set everything as output
    PORTE = 0xFFFD;     // By default, set all outputs as high (LEDS are active low)
    T1CON = 0x8030;     // TMR1 on, prescale 1:256, clk = 4882.81Hz
    PR1 = 2;            // set period register to the frequency of the clock
    
    while(1)
    {
        for (PR1 = 2; PR1 <= 1220; PR1 += 10)
        {
            PORTEINV = 0x0007;  // Toggle the three user LEDs
            TMR1 = 1;
            while(TMR1) { } // while TMR1 hasn't overflowed PR1
        }

        for (PR1 = 1220; PR1 > 100; PR1 -= 10)
        {
            PORTEINV = 0x0007;  // Toggle the three user LEDs
            TMR1 = 1;
            while(TMR1) { } // while TMR1 hasn't overflowed PR1
        }
    }

    return 0;
}