#include <xc.h>
#include "../Include/serial7seg.h"
#include "../Include/misc.h"

/**
 * @brief Initialize the SPI controller used to communicate with the display.
 *
 * @param none
 *
 * @retval none
 */
void segInit(void)
{
    SSTRISCLR = SSPINMASK;  // Set SS pin as output
    SSLATCLR = SSPINMASK;   // Deselect the device
    SPICON = SPI_CONF;      // Set the configuration settings
    SPIBRG = SPI_BAUD;      // Set the baud rate
}

/**
 * @brief Transmit a single byte over SPI, and return the received byte.
 *
 * @param data A single byte of data to be transmitted
 *
 * @return The byte recieved from the slave
 *
 * @note Slave Select line is controlled outside of this function
 */
uint8_t writeSPIByte(uint8_t data)
{
    // Place transmit data in the buffer
    SPIBUF = data;

    // Wait until all data is sent
    while(!SPISTATBITS.SPIRBF) { }

    // Return the received data
    return SPIBUF;
}

/**
 * @brief Send a display packet that updates all four digits on the screen
 *
 * @param num1 Binary or Ascii character for digit 1
 * @param num2 Binary or Ascii character for digit 2
 * @param num3 Binary or Ascii character for digit 3
 * @param num4 Binary or Ascii character for digit 4
 *
 * @retval none
 */
void segWriteDisplay(uint8_t num1, uint8_t num2, uint8_t num3, uint8_t num4)
{
    // Pull slave select low
    SSLATSET = SSPINMASK;
    
    // Send data packet
    writeSPIByte(num1);
    writeSPIByte(num2);
    writeSPIByte(num3);
    writeSPIByte(num4);
    
    // Pull slave select high
    SSLATCLR = SSPINMASK;
}

/**
 * #brief Send a special command
 * 
 * @param cmd The special command to send
 * @param data The data byte for the command
 *
 * @retval none
 */
void segWriteCmd(uint8_t cmd, uint8_t data)
{
    // Pull slave select low
    SSLATSET = SSPINMASK;
    
    // Send data packet
    writeSPIByte(cmd);
    writeSPIByte(data);
    
    // Pull slave select high
    SSLATCLR = SSPINMASK;
}