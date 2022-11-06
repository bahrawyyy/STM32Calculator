/*
 * Lcd.c
 *
 *  Created on: Sep 12, 2022
 *      Author: 10
 */
#include "../../MCAL/Dio/Dio.h"
#include "Lcd.h"
#include<util/delay.h>
#include <string.h>


static void Trigger_Enable(void);  //ProtoType of static is defined in source file itself(Private declaration)
static void Set_Cursor_Pos(uint8 row,uint8 column);

void Lcd_Init(){

	Lcd_sendCmd(fourbit_mode);  /* Go into 4-bit operating mode*/
	Lcd_sendCmd(fourbit_mode11);	/* Go into 4-bit operating mode*/
	Lcd_sendCmd(D4_D7);  /* 2 Line, 5*7 matrix in 4-bit mode */
	Lcd_sendCmd(CursorOFF);  /* Display on cursor off */
	Lcd_sendCmd(IncrCursor);  /* Increment cursor (shift cursor to right) */
	Lcd_sendCmd(CLR_Display);  /* Clear display screen */

}

/*
 * RS = 0 // To send command
 * RW = 0 //To write on the LCD
 *  4-bit mode
 * Send higher nibble(1/2 Byte)
 * Send Trigger Enable
 * Send Lower nibble
 * Send Trigger Enable
 * delay
 *
 *
 *	Ex. 0x28 0b 0010 1000  //Read bit by bit and see if it is low or high
 */


void Lcd_sendCmd(unsigned char cmd){
	Dio_write(RS, LOW);
	Dio_write(RW, LOW);
	// if(GET_BIT(cmd,7)){Dio_Write(D7,HIGH);}else{Dio_write(D7,LOW);}
	// We use ternary operator instead
	(GET_BIT(cmd,7)) ? Dio_write(D7,HIGH) : Dio_write(D7,LOW);
	(GET_BIT(cmd,6)) ? Dio_write(D6,HIGH) : Dio_write(D6,LOW);
	(GET_BIT(cmd,5)) ? Dio_write(D5,HIGH) : Dio_write(D5,LOW);
	(GET_BIT(cmd,4)) ? Dio_write(D4,HIGH) : Dio_write(D4,LOW);
	//Trigger Enable
	Trigger_Enable();
	(GET_BIT(cmd,3)) ? Dio_write(D7,HIGH) : Dio_write(D7,LOW);
	(GET_BIT(cmd,2)) ? Dio_write(D6,HIGH) : Dio_write(D6,LOW);
	(GET_BIT(cmd,1)) ? Dio_write(D5,HIGH) : Dio_write(D5,LOW);
	(GET_BIT(cmd,0)) ? Dio_write(D4,HIGH) : Dio_write(D4,LOW);
	//Trigger Enable
	Trigger_Enable();
}
void Lcd_sendChar(unsigned char data){
	Dio_write(RS, HIGH);
	Dio_write(RW, LOW);
	(GET_BIT(data,7)) ? Dio_write(D7,HIGH) : Dio_write(D7,LOW);
	(GET_BIT(data,6)) ? Dio_write(D6,HIGH) : Dio_write(D6,LOW);
	(GET_BIT(data,5)) ? Dio_write(D5,HIGH) : Dio_write(D5,LOW);
	(GET_BIT(data,4)) ? Dio_write(D4,HIGH) : Dio_write(D4,LOW);
	//Trigger Enable
	Trigger_Enable();
	(GET_BIT(data,3)) ? Dio_write(D7,HIGH) : Dio_write(D7,LOW);
	(GET_BIT(data,2)) ? Dio_write(D6,HIGH) : Dio_write(D6,LOW);
	(GET_BIT(data,1)) ? Dio_write(D5,HIGH) : Dio_write(D5,LOW);
	(GET_BIT(data,0)) ? Dio_write(D4,HIGH) : Dio_write(D4,LOW);
	//Trigger Enable
	Trigger_Enable();
}
void Lcd_sendString(char *data){   //I changed the argument type passed to char
									//Cuz I get a warning
	Dio_write(RS, HIGH);
	Dio_write(RW, LOW);

	int i=0;
	for(i=0 ; i<strlen(data) ;i++){
		(GET_BIT(*(data+i),7)) ? Dio_write(D7,HIGH) : Dio_write(D7,LOW);
		(GET_BIT(*(data+i),6)) ? Dio_write(D6,HIGH) : Dio_write(D6,LOW);
		(GET_BIT(*(data+i),5)) ? Dio_write(D5,HIGH) : Dio_write(D5,LOW);
		(GET_BIT(*(data+i),4)) ? Dio_write(D4,HIGH) : Dio_write(D4,LOW);
		Trigger_Enable();
		(GET_BIT(*(data+i),3)) ? Dio_write(D7,HIGH) : Dio_write(D7,LOW);
		(GET_BIT(*(data+i),2)) ? Dio_write(D6,HIGH) : Dio_write(D6,LOW);
		(GET_BIT(*(data+i),1)) ? Dio_write(D5,HIGH) : Dio_write(D5,LOW);
		(GET_BIT(*(data+i),0)) ? Dio_write(D4,HIGH) : Dio_write(D4,LOW);
		Trigger_Enable();
	}
}

void Lcd_sendString_xy(char *data,unsigned char row,unsigned char col){
	Dio_write(RS, HIGH);
	Dio_write(RW, LOW);

		/*if(row == 1){
				Lcd_sendCmd(Force1stline);
				_delay_ms(1);
		}else if(row == 2){
				Lcd_sendCmd(Force2ndline);
				_delay_ms(10);
		}


		for(int j=1;j<=col;j++){
			Lcd_sendCmd(ShiftRight);
		}*/
		Set_Cursor_Pos(row,col);
		Lcd_sendString(data);

}

static void Trigger_Enable(void){  //We make it static cuz we won't use it anywhere but here
	Dio_write(EN,HIGH);
	_delay_us(10);
	Dio_write(EN,LOW);
	_delay_us(2000);
}

//A function to display Numbers instead of characters
void Lcd_displayNum(uint16 num)
{
	Dio_write(RS, HIGH);
	Dio_write(RW, LOW);

	 uint8 ch[10],i=0,j=0;
		   if(num == 0)
		   {
			   Lcd_sendChar('0');
		   }
		   else
		   {
			   while(num)
			   {
					ch[i] = num % 10 + '0';  //To convert int to char
					num /= 10;
					i++;
			   } //Thus number entered is reversed so, we want to display it correctly
			   for(j=i;j>0;j--)
			   {
				   Lcd_sendChar(ch[j-1]);
			   }
		   }
}

void Lcd_displayNum_xy(uint16 num,unsigned char row,unsigned char col){

	Dio_write(RS, HIGH);
	Dio_write(RW, LOW);


	if(row == 1){
		Lcd_sendCmd(Force1stline);
		_delay_ms(1);
	}else if(row == 2){
		Lcd_sendCmd(Force2ndline);
		_delay_ms(10);
	}


	for(int j=1;j<=col;j++){
		Lcd_sendCmd(ShiftRight);
	}

	Lcd_displayNum(num);

	}

void Lcd_sendChar_xy(unsigned char data,unsigned char row,unsigned char col){
	Dio_write(RS, HIGH);
	Dio_write(RW, LOW);


	if(row == 1){
		Lcd_sendCmd(Force1stline);
		_delay_ms(1);
	}else if(row == 2){
		Lcd_sendCmd(Force2ndline);
		_delay_ms(10);
	}

	for(int j=1;j<=col;j++){
		Lcd_sendCmd(ShiftRight);
	}
	Lcd_sendChar(data);
}

static void Set_Cursor_Pos(uint8 row,uint8 column){
	column--;
	switch(row){
	         case 1: Lcd_sendCmd((0x80 + column)); break;
	         case 2: Lcd_sendCmd((0xc0 + column)); break;
	         default:;
	}
}

