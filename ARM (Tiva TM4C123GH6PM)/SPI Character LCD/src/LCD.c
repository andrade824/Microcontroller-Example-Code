#include <string.h>
#include "../inc/LCD.h"
#include "../inc/utility.h"

/**
 * @brief 	Initialize the LCD to wrap at 16 chars,
 * 			cursor off, and clear the screen.
 *
 * @param 	none
 *
 * @retval 	none
 */
void LCDInit(void)
{
	// Wait for LCD to power up
	SysTickDelay(ST_MS * 20);

	LCD_DISPLAY_MODE(0x30);
	LCD_CURSOR_MODE(0x32);
	LCD_CLEAR();
}

/**
 * @brief 	Sends a string of characters to the LCD
 *
 * @param 	string The string to display
 *
 * @retval 	none
 */
void LCDDisplayString(char * string)
{
	int i = 0;
	int length = strlen(string);

	for(; i < length; ++i)
		SPISendBytes(1, string[i]);
}
