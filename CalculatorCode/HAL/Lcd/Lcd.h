/*
 * Lcd.h
 *
 *  Created on: Sep 12, 2022
 *      Author: 10
 */

#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#define fourbit_mode 0x33
#define fourbit_mode11 0x32
#define CLR_Display 0x01
#define D4_D7 0x28
#define CursorOFF 0x0c
#define IncrCursor 0x06
#define Force1stline 0x80
#define Force2ndline 0xC0
#define ShiftLeft 0x18
#define ShiftRight 0x1C


#include "Lcd_Config.h"



void Lcd_Init();
void Lcd_sendCmd(unsigned char cmd);
void Lcd_sendChar(unsigned char data);
void Lcd_sendChar_xy(unsigned char data,unsigned char row,unsigned char col);

void Lcd_sendString(char *data);
void Lcd_sendString_xy(char *data,unsigned char row,unsigned char col);

void Lcd_displayNum(uint16 num);
void Lcd_displayNum_xy(uint16 num,unsigned char row,unsigned char col);



#endif /* HAL_LCD_LCD_H_ */
