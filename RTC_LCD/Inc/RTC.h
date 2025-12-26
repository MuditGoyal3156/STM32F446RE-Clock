/*
 * RTC.h
 *
 *  Created on: Dec 26, 2025
 *      Author: mudit
 */

#ifndef RTC_H_
#define RTC_H_

/* I2C address */
#define DS1307_ADDR    0x68

/* Register addresses */
#define DS1307_SEC_REG     0x00
#define DS1307_MIN_REG     0x01
#define DS1307_HOUR_REG    0x02
#define DS1307_DAY_REG     0x03
#define DS1307_DATE_REG    0x04
#define DS1307_MONTH_REG   0x05
#define DS1307_YEAR_REG    0x06
#define DS1307_CTRL_REG    0x07


typedef struct
{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} DS1307_Time_t;


void DS1307_Init(void);
void DS1307_SetTime(DS1307_Time_t *time);
void DS1307_GetTime(DS1307_Time_t *time);

#endif /* RTC_H_ */
