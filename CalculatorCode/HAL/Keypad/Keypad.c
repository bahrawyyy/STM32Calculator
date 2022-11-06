/*
 * Keypad.c
 *
 *  Created on: Sep 19, 2022
 *      Author: 10
 */

#include "../../MCAL/Dio/Dio.h"
#include "Keypad.h"

//Private Declaration
static uint8 KP_CheckColumns(void);


static uint8 KP_MapArr[4][4] =
	{
			{KP_BUTTON0,KP_BUTTON1,KP_BUTTON2,KP_BUTTON3},
			{KP_BUTTON4,KP_BUTTON5,KP_BUTTON6,KP_BUTTON7},
			{KP_BUTTON8,KP_BUTTON9,KP_BUTTON10,KP_BUTTON11},
			{KP_BUTTON12,KP_BUTTON13,KP_BUTTON14,KP_BUTTON15}
	};

/*
 * Function to check Columns
 *	COLS --> PC4 - PC7
 */

static uint8 KP_CheckColumns(){
	uint8 ColNumber = KP_RELEASED;
	if(Dio_read(PORTC_4) == LOW){  // Why we changed it to LOW ??
		ColNumber = 0;				//Because of pull up resistor
	}else if(Dio_read(PORTC_5) == LOW){		//It is already high so, we want to see when it will become low
		ColNumber = 1;
	}else if(Dio_read(PORTC_6) == LOW){
		ColNumber = 2;
	}else if(Dio_read(PORTC_7) == LOW){
		ColNumber = 3;
	}
	return ColNumber;
}


/*
 * Put High on each row then, check the columns
 * ROWS --> PC0 - PC3
 * COLS --> PC4 - PC7
 *
 */
uint8 KP_getPressedButton(){
	uint8 PressedButton = KP_RELEASED;  //Indication that there is no pressed button

	//Put Low on ROW 0 then, check columns (Because of pull up resistor)
	Dio_write(PORTC_0,LOW);  //It is already high so, we want to reverse th process
	Dio_write(PORTC_1,HIGH);
	Dio_write(PORTC_2,HIGH);
	Dio_write(PORTC_3,HIGH);
	//Check Columns
	uint8 ColNum = KP_CheckColumns();
	if(ColNum != KP_RELEASED){   //It means that someone has already pressed a button in this column
		PressedButton = KP_MapArr[0][ColNum];
	}

	//Put High on ROW 1 then, check columns
	Dio_write(PORTC_0,HIGH);
	Dio_write(PORTC_1,LOW);
	Dio_write(PORTC_2,HIGH);
	Dio_write(PORTC_3,HIGH);
	//Check Columns
	ColNum = KP_CheckColumns();
	if(ColNum != KP_RELEASED){
		PressedButton = KP_MapArr[1][ColNum];
	}


	//Put High on ROW 2 then, check columns
	Dio_write(PORTC_0,HIGH);
	Dio_write(PORTC_1,HIGH);
	Dio_write(PORTC_2,LOW);
	Dio_write(PORTC_3,HIGH);
	//Check Columns
	ColNum = KP_CheckColumns();
	if(ColNum != KP_RELEASED){
		PressedButton = KP_MapArr[2][ColNum];
	}


	//Put High on ROW 0 then, check columns
	Dio_write(PORTC_0,HIGH);
	Dio_write(PORTC_1,HIGH);
	Dio_write(PORTC_2,HIGH);
	Dio_write(PORTC_3,LOW);
	//Check Columns
	ColNum = KP_CheckColumns();
	if(ColNum != KP_RELEASED){
		PressedButton = KP_MapArr[3][ColNum];
	}

	return PressedButton;
}

