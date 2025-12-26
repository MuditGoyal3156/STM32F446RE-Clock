/*
 * LCD.c
 *
 *  Created on: Dec 26, 2025
 *      Author: mudit
 */

#include "LCD.h"
#include "Systick.h"
#include "I2C.h"

void LCD_Init(void)
{
	systickDelayMs(100);

    LCD_Command(0x33);
    LCD_Command(0x32);
    LCD_Command(Four_bit_2_line); // 4-bit, 2-line
    LCD_Command(LCDON); // Display ON
    LCD_Command(Increment_Cursor); // Auto increment
    LCD_Command(Clear); // Clear

    systickDelayMs(2);
}
void LCD_Command(uint8_t Command)
{
	uint8_t high, low;

	// Upper nibble
	high = LCD_CMD_0 | (Command & 0xF0);
	I2C1_SendData(&high, 1, LCD_ADDR);

	high |= 0x04;                 // E = 1
	I2C1_SendData(&high, 1, LCD_ADDR);

	high &= ~0x04;                // E = 0
	I2C1_SendData(&high, 1, LCD_ADDR);

	// Lower nibble
	low = LCD_CMD_0 | ((Command << 4) & 0xF0);
	I2C1_SendData(&low, 1, LCD_ADDR);

	low |= 0x04;                  // E = 1
	I2C1_SendData(&low, 1, LCD_ADDR);

	low &= ~0x04;                 // E = 0
	I2C1_SendData(&low, 1, LCD_ADDR);

	systickDelayMs(2);
}

void LCD_Set_Cursor(uint8_t row, uint8_t col)
{
    uint8_t address;

    if (row == 0)
        address = col;
    else if (row == 1)
        address = 0x40 + col;
    else
        return;

    LCD_Command(0x80 | address);
}

void LCD_Send_Data(uint8_t len,uint8_t* data)
{
	while(len > 0)
	{
		uint8_t high, low;

		// Upper nibble
		high = LCD_DATA_0 | ((*data) & 0xF0);
		I2C1_SendData(&high, 1, LCD_ADDR);

		high |= 0x04;                 // E = 1
		I2C1_SendData(&high, 1, LCD_ADDR);

		high &= ~0x04;                // E = 0
		I2C1_SendData(&high, 1, LCD_ADDR);

		// Lower nibble
		low = LCD_DATA_0 | (((*data) << 4) & 0xF0);
		I2C1_SendData(&low, 1, LCD_ADDR);

		low |= 0x04;                  // E = 1
		I2C1_SendData(&low, 1, LCD_ADDR);

		low &= ~0x04;                 // E = 0
		I2C1_SendData(&low, 1, LCD_ADDR);

		systickDelayMs(2);

		len--;
		data++;
	}


}
