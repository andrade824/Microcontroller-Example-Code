#include <xc.h>
#include <sys/attribs.h>

void __ISR(_TIMER_2_VECTOR, ipl7) Timer2Vector(void)
{
    IFS0bits.T2IF = 0;
    LATEINV = 0x0001;
}

void __ISR(_TIMER_3_VECTOR, ipl1) Timer3Vector(void)
{

    IFS0bits.T3IF = 0;
    LATEINV = 0x0002;
}