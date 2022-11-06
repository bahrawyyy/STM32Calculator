#include "MCAL/Dio/Dio.h"
#include "HAL/Lcd/Lcd.h"
#include "HAL/Keypad/Keypad.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "MCAL/EXT_INTERRUPTS/EXT_INTERRUPTS.h"

static void DealWithResult(int result);
uint8 checkPassword(uint8 Pass[]);

// To operate on 2-digit numbers ex. 12+25=  -->Thus array of 6
uint8 Process[6] = {KP_RELEASED,KP_RELEASED,KP_RELEASED,KP_RELEASED,KP_RELEASED,KP_RELEASED};
uint8 count = 0;
uint16 result;
uint8 Key_Pressed = KP_RELEASED;
uint8 Password[8];
uint8 pas = 0;

void EXT_init_Interrupt0(){
	SET_BIT(GICR,INT0);   //Enable EXT_interrupt 0
	//Configure interrupt for both edges
	SET_BIT(MCUCR,ISC00);
	CLR_BIT(MCUCR,ISC01);
}

ISR(INT0_vect){
	Dio_write(PORTD_4,HIGH);
	_delay_ms(800);
	Dio_write(PORTD_4,LOW);
}

int main(void)
{
	Dio_init();
	SREG |= (1<<7); //Enable global interrupt
	EXTI_init();
	label : Lcd_Init();   //To return to this point

	/* Entering Password */

	Lcd_sendString_xy("password",1,1);   //Password --> 1234
	do {
		Password[pas] = KP_getPressedButton();
	} while (Password[pas] == KP_RELEASED);
		Lcd_sendChar(Password[pas]);
	pas++;
	_delay_ms(300);
	do {
		Password[pas] = KP_getPressedButton();
	} while (Password[pas] == KP_RELEASED);
	Lcd_sendChar(Password[pas]);
	pas++;
	_delay_ms(300);
	do {
		Password[pas] = KP_getPressedButton();
	} while (Password[pas] == KP_RELEASED);
	Lcd_sendChar(Password[pas]);
	pas++;
	_delay_ms(300);
	do {
		Password[pas] = KP_getPressedButton();
	} while (Password[pas] == KP_RELEASED);
	Lcd_sendChar(Password[pas]);
	pas++;
	_delay_ms(300);
	do {
		Key_Pressed = KP_getPressedButton();
		} while (Key_Pressed == KP_RELEASED);
			if (Key_Pressed == 'A') {
				if((Password[0]=='1')&(Password[1]=='2')&(Password[2]=='3')&(Password[3]=='4')){
					Lcd_sendCmd(CLR_Display);
					Lcd_sendString_xy("Welcome",1,1);
					_delay_ms(500);

while(1){
	Lcd_sendCmd(Force2ndline);
		/* Receiving the first digit of the first number */
		do {
			Process[count] = KP_getPressedButton();
		} while (Process[count] == KP_RELEASED);
		if (Process[count] == 'A' || Process[count] == '='
				|| Process[count] == '+' || Process[count] == '-'
				|| Process[count] == '*' || Process[count] == '/') {
			Lcd_sendCmd(CLR_Display);
			goto label ;
		} else {
			Lcd_sendChar(Process[count]);
		}
		count++;
		_delay_ms(300);
		/* Receiving the second digit of the first number */
		do {
			Process[count] = KP_getPressedButton();
		} while (Process[count] == KP_RELEASED);
		if (Process[count] == 'A' || Process[count] == '='
				|| Process[count] == '+' || Process[count] == '-'
				|| Process[count] == '*' || Process[count] == '/') {
			Lcd_sendCmd(CLR_Display);
			goto label ;
		} else {
			Lcd_sendChar(Process[count]);
		}
		count++;
		_delay_ms(300);
		/* Receiving the operation */
		do {
			Process[count] = KP_getPressedButton();

		} while (Process[count] == KP_RELEASED);

		if (Process[count] == 'A' || Process[count] == '=') {
			Lcd_sendCmd(CLR_Display);
			goto label ;
		} else {
			Lcd_sendChar(Process[count]);
		}
		count++;
		_delay_ms(300);
		/* Receiving the first digit of the second number */
		do {
			Process[count] = KP_getPressedButton();
		} while (Process[count] == KP_RELEASED);
		if (Process[count] == 'A' || Process[count] == '='
				|| Process[count] == '+' || Process[count] == '-'
				|| Process[count] == '*' || Process[count] == '/') {
			Lcd_sendCmd(CLR_Display);
			goto label ;
		} else {
			Lcd_sendChar(Process[count]);
		}
		count++;
		_delay_ms(300);
		/* Receiving the second digit of the second number */
		do {
			Process[count] = KP_getPressedButton();
		} while (Process[count] == KP_RELEASED);
		if (Process[count] == 'A' || Process[count] == '='
				|| Process[count] == '+' || Process[count] == '-'
				|| Process[count] == '*' || Process[count] == '/') {
			Lcd_sendCmd(CLR_Display);
			goto label ;
		} else {
			Lcd_sendChar(Process[count]);
		}
		count++;
		_delay_ms(300);
		/* Receiving the = sign ,then performing operation */
		do {
			Process[count] = KP_getPressedButton();

		} while (Process[count] == KP_RELEASED);

		if (Process[count] == '=') {
			Lcd_sendChar(Process[count]);
			switch(Process[count-3]){
			case '+':
				//Why -48 ?? Because the difference between ASCII of '0' and 0 is 48
				result = (Process[count - 4] - 48)
						+ ((Process[count - 5] - 48) * 10)
						+ ((Process[count - 2] - 48) * 10)
						+ (Process[count - 1] - 48);
				//The result is int so, we want to convert it to be displayed on LCD
				DealWithResult(result);
				break;
			case '-':
				result = ((Process[count - 4] - 48)
						+ ((Process[count - 5] - 48) * 10))
						- (((Process[count - 2] - 48) * 10)
						+ (Process[count - 1] - 48));
				DealWithResult(result);
				break;
			case '*':
				result = ((Process[count - 4] - 48)
						+ ((Process[count - 5] - 48) * 10))
						* (((Process[count - 2] - 48) * 10)
						+ (Process[count - 1] - 48));
				DealWithResult(result);
				break;
			case '/':
				result = ((Process[count - 4] - 48)
						+ ((Process[count - 5] - 48) * 10))
						/ (((Process[count - 2] - 48) * 10)
						+ (Process[count - 1] - 48));
				DealWithResult(result);
				break;
			default:
				break;
			}
	}else{
		Lcd_sendCmd(CLR_Display);
		goto label ;
	}
		_delay_ms(2000);
}
				}
}else{
		Lcd_sendCmd(CLR_Display);
		Lcd_sendString("Wrong Password");
		_delay_ms(2000);
}
}
static void DealWithResult(int result){
		if (result >= 100 && result < 1000) {
			Lcd_sendChar((result / 100) + 48);
			Lcd_sendChar(((result / 10) % 10) + 48);
			Lcd_sendChar((result % 10) + 48);
		} else if (result >= 10 && result < 100) {
			Lcd_sendChar((result / 10) + 48);
			Lcd_sendChar((result % 10) + 48);
		} else if (result < 10) {
			Lcd_sendChar(result + 48);
		}
}
uint8 checkPassword(uint8 Pass[]){
	if((Pass[0]==1)&(Pass[1]==2)&(Pass[2]==3)&(Pass[3]==4)){
		return 1;
	}else{
		return 0;
	}
}


