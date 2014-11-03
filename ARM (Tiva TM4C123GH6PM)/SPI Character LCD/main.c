#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/utility.h"
#include "inc/spi.h"
#include "inc/LCD.h"

int main(void)
{
	// Initialize SPI0 for 500KHz
	SPIInit(40);
	LCDInit();

	LCDDisplayString("Hello!");

	LCD_SET_CURSOR(0x31, 0x30);
	LCDDisplayString("Yeah");

	while(1)
	{

	}
	
	return 0;
}
