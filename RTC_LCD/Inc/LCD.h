/*
 * LCD.h
 *
 *  Created on: Dec 26, 2025
 *      Author: mudit
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include "Addresses.h"
/*
 * LCD Commands
 */

#define LCDON				0x0CU
#define Clear				0x01U
#define Return_Home			0x83U
#define Four_Bit			0x81U
#define Increment_Cursor	0x06U
#define R1_C1				0x80U
#define R2_C1				0xC1U
#define Four_bit_2_line		0x28U
#define R1_C0				0xC0U


#define LCD_ADDR   	  	  0x27    // I2C address
#define LCD_CMD_1     	  0x0CU
#define LCD_CMD_0     	  0x08U
#define LCD_DATA_1     	  0x0DU
#define LCD_DATA_0 		  0x09U


/*
❖	LCD16x2 Command write function
	●	Send command to the data port
	●	Make RS pin low
	●	Make RW pin low
	●	Give High to Low pulse at Enable (E) minimum of 450ns.
	●	When we give Enable pulse, LCD latch the data present at D0 to D7 & execute a command as RS is command reg.
❖	LCD16x2 Data write function
	●	Send command to the data port
	●	Make RS pin high
	●	Make RW pin low
	●	Give High to Low pulse at Enable (E) minimum of 450 ns
	●	When we give Enable pulse, LCD latch the data present at D0 to D7 & display it on the 5x8 matrix as RS is data reg.
❖	Initialize LCD for function to send display data to LCD
	●	Function Set (8-bit/4-bit, 1 line/2-line, 5×7 matrix)
	●	Display ON, Cursor OFF
	●	Clear Display
	●	Cursor at first line, first position
 */

/*
 * Function Prototypes
 */
void LCD_Init(void);
void LCD_Command(uint8_t Command);
void LCD_Send_Data(uint8_t len,uint8_t* data);
void LCD_Set_Cursor(uint8_t row, uint8_t col);
#endif /* LCD_H_ */
