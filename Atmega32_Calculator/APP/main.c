/*
 * main.c
 *
 *  Created on: May 4, 2023
 *      Author: Abdallah
 */

#define F_CPU 16000000UL

#include "../HAL/Lcd/Lcd.h"
#include <util/delay.h>
#include "../HAL/KPD/KPD_interface.h"
#include <string.h>


int i=0,j=0,firstOperand=0,secondOperand=0,entryToSecond=0;
u8 operation = 0;


u8 input[30] = {'\0'}; // Initialize input array
u8 indexz = 0;


int exponent(int base,int exp){
    int result = 1;
     while (exp != 0) {
        result = base * result;
        --exp;
    }
    return result;
}


int main()
{
	DIO_ES_tInit();
	Lcd_ES_tInit();

	u8 Value;



	Lcd_ES_tsendString("Atmega32");
	LCD_ES_tGoTo(1, 0);
	Lcd_ES_tsendString("Calculator !");
	_delay_ms(500);
	lcd_ES_tclear();

	while (1)
	{
		KPD_ES_tGetKeyPressed(&Value);
		if (Value != KPD_U8_NOT_PRESSED)
		{
			input[indexz] = Value; // Store input in array
			Lcd_ES_tsendChar(input[indexz]);
			indexz++; // Increment index

			switch (input[indexz - 1])
			{
			case '+':
			case '*':
			case '-':
			case '/':
				operation = input[indexz - 1];
				for (i = indexz - 2, j = 0; i >= 0; i--, j++)
				{
					firstOperand += ((input[i] - '0') * exponent(10, j));
				}
				entryToSecond = indexz;
				break;
			case '=':
				for (i = indexz - 2, j = 0; i >= entryToSecond; i--, j++)
				{
					secondOperand += ((input[i] - '0') * exponent(10, j));
				}
				LCD_ES_tGoTo(1, 0);
				switch (operation)
				{
				case '+':
					Lcd_ES_tdisplayNum(firstOperand + secondOperand);
					break;
				case '-':
					Lcd_ES_tdisplayNum(firstOperand - secondOperand);
					break;
				case '*':
					Lcd_ES_tdisplayNum(firstOperand * secondOperand);
					break;
				case '/':
					if(secondOperand == 0){
						lcd_ES_tclear();
						LCD_ES_tGoTo(0, 0);
						Lcd_ES_tsendString("ERROR: ");
						LCD_ES_tGoTo(1, 0);
						Lcd_ES_tsendString("Division by zero");
					}else{
						Lcd_ES_tdisplayNum(firstOperand / secondOperand);
					}
					break;
				}

				// Reset variables
				firstOperand = 0;
				secondOperand = 0;
				indexz = 0;

				break;
			case 'C':
				lcd_ES_tclear();
				firstOperand = 0;
				secondOperand = 0;
				indexz = 0;
				break;
			}
		}
	}

	return 0;
}
