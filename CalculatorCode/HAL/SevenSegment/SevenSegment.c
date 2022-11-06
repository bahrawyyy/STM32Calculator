/*
 * SevenSegment.c
 *
 *  Created on: Sep 14, 2022
 *      Author: 10
 */


#include "SevenSegment.h"
#include "../../MCAL/Dio/Dio_Types.h"


void SevenSegment(unsigned char num){
	switch(num){
	case 0:
			Dio_write(PORTC_0,HIGH);
			Dio_write(PORTC_1,HIGH);
			Dio_write(PORTC_2,HIGH);
			Dio_write(PORTC_3,HIGH);
			Dio_write(PORTC_4,HIGH);
			Dio_write(PORTC_5,HIGH);
			break;
	case 1:
			Dio_write(PORTC_1,HIGH);
			Dio_write(PORTC_2,HIGH);
			break;
	case 2:
			Dio_write(PORTC_0,HIGH);
			Dio_write(PORTC_1,HIGH);
			Dio_write(PORTC_3,HIGH);
			Dio_write(PORTC_4,HIGH);
			Dio_write(PORTC_6,HIGH);
			break;
	case 3:
			Dio_write(PORTC_0,HIGH);
			Dio_write(PORTC_1,HIGH);
			Dio_write(PORTC_2,HIGH);
			Dio_write(PORTC_3,HIGH);
			Dio_write(PORTC_6,HIGH);
			break;
	case 4:
			Dio_write(PORTC_1,HIGH);
			Dio_write(PORTC_2,HIGH);
			Dio_write(PORTC_5,HIGH);
			Dio_write(PORTC_6,HIGH);
			break;
	case 5:
			Dio_write(PORTC_0,HIGH);
			Dio_write(PORTC_2,HIGH);
			Dio_write(PORTC_3,HIGH);
			Dio_write(PORTC_5,HIGH);
			Dio_write(PORTC_6,HIGH);
			break;
	case 6:
			Dio_write(PORTC_0,HIGH);
			Dio_write(PORTC_2,HIGH);
			Dio_write(PORTC_3,HIGH);
			Dio_write(PORTC_4,HIGH);
			Dio_write(PORTC_5,HIGH);
			Dio_write(PORTC_6,HIGH);
			break;
	case 7:
			Dio_write(PORTC_0,HIGH);
			Dio_write(PORTC_1,HIGH);
			Dio_write(PORTC_2,HIGH);
			break;
	case 8:
			Dio_write(PORTC_0,HIGH);
			Dio_write(PORTC_1,HIGH);
			Dio_write(PORTC_2,HIGH);
			Dio_write(PORTC_3,HIGH);
			Dio_write(PORTC_4,HIGH);
			Dio_write(PORTC_5,HIGH);
			Dio_write(PORTC_6,HIGH);
			break;
	case 9:
			Dio_write(PORTC_0,HIGH);
			Dio_write(PORTC_1,HIGH);
			Dio_write(PORTC_2,HIGH);
			Dio_write(PORTC_3,HIGH);
			Dio_write(PORTC_5,HIGH);
			Dio_write(PORTC_6,HIGH);
			break;
	default:
			Dio_write(PORTC_0,HIGH);
	}
}


void SevenSegmentWithIndex(unsigned char num,unsigned char id){

}
