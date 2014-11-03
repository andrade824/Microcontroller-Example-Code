#include "inc/tm4c123gh6pm.h"
#include "inc/hw_gpio.h"
#include "NesController.h"
#include "utility.h"

/**
 * @brief	Initialize the pins needed to gather controller input
 *
 * @param 	none
 *
 * @retval	none
 */
void InitController(void)
{
	// Set CLK and LATCH as outputs, DATA as input
	NESPORT_DIR |= (NES_CLK | NES_LATCH);
	NESPORT_DIR &= ~(NES_DATA);

	// Initializing CLK and LATCH pins as low
	NESPORT &= ~(NES_CLK | NES_LATCH);

	// Enable NESPORT pins as digital pins
	NESPORT_DEN |= ALL_NES_PINS;
}

//
/**
 * @brief	Gather input and return it as an 8-bit integer
 *
 * @param 	none
 *
 * @retval	The nes controller input.
 *
 * 			1 = Button pressed
 * 			0 = Button not pressed
 */
NesData GetInput(void)
{
	int i = 1;
	uint8_t temp_data;	// Data grabbed from the controller
	NesData data;	// Final parsed controller data

	NESPORT &= ~ALL_NES_PINS;

	// Toggle latch pin
	NESPORT |= NES_LATCH;
	SysTickDelay(12 * ST_US);
	NESPORT &= ~NES_LATCH;

	// Grab A button data
	temp_data = (NESPORT & NES_DATA) >> NES_DATA_S;

	// Grab rest of data from controller
	for(; i < 8; i++)
	{
		NESPORT |= NES_CLK;
		SysTickDelay(6 * ST_US);
		NESPORT &= ~NES_CLK;
		temp_data |= ((NESPORT & NES_DATA) >> NES_DATA_S) << i;
		SysTickDelay(6 * ST_US);
	}

	// Parse controller input and create NesData structure
	data.A = temp_data & 1;
	data.B = (temp_data >> 1) & 1;
	data.Select= (temp_data >> 2) & 1;
	data.Start = (temp_data >> 3) & 1;
	data.Up = (temp_data >> 4) & 1;
	data.Down = (temp_data >> 5) & 1;
	data.Left = (temp_data >> 6) & 1;
	data.Right = (temp_data >> 7) & 1;

	return data;

}
