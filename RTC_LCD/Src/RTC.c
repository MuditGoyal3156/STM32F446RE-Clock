/*
 * RTC.c
 *
 *  Created on: Dec 26, 2025
 *      Author: mudit
 */

#include "I2C.h"
#include "RTC.h"

static uint8_t dec_to_bcd(uint8_t val)
{
    return ((val / 10) << 4) | (val % 10);
}

static uint8_t bcd_to_dec(uint8_t val)
{
    return ((val >> 4) * 10) + (val & 0x0F);
}


static void DS1307_Write(uint8_t reg, uint8_t data)
{
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = data;
    I2C1_SendData(buf, 2, DS1307_ADDR);
}

static uint8_t DS1307_Read(uint8_t reg)
{
    uint8_t data;

    /* Send register address */
    I2C1_SendData(&reg, 1, DS1307_ADDR);

    /* Read data */
    I2C1_ReadData(&data, 1, DS1307_ADDR);

    return data;
}



void DS1307_Init(void)
{
    uint8_t sec;

    /* Clear CH (Clock Halt) bit */
    sec = DS1307_Read(0x00);
    sec &= ~(1 << 7);
    DS1307_Write(0x00, sec);

    /* Disable square wave output */
    DS1307_Write(0x07, 0x00);
}

void DS1307_SetTime(DS1307_Time_t *t)
{
    DS1307_Write(0x00, dec_to_bcd(t->sec));
    DS1307_Write(0x01, dec_to_bcd(t->min));
    DS1307_Write(0x02, dec_to_bcd(t->hour)); // 24-hour
    DS1307_Write(0x03, dec_to_bcd(t->day));
    DS1307_Write(0x04, dec_to_bcd(t->date));
    DS1307_Write(0x05, dec_to_bcd(t->month));
    DS1307_Write(0x06, dec_to_bcd(t->year));
}

void DS1307_GetTime(DS1307_Time_t *t)
{
    t->sec   = bcd_to_dec(DS1307_Read(0x00) & 0x7F);
    t->min   = bcd_to_dec(DS1307_Read(0x01));
    t->hour  = bcd_to_dec(DS1307_Read(0x02) & 0x3F);
    t->day   = bcd_to_dec(DS1307_Read(0x03));
    t->date  = bcd_to_dec(DS1307_Read(0x04));
    t->month = bcd_to_dec(DS1307_Read(0x05));
    t->year  = bcd_to_dec(DS1307_Read(0x06));
}
