/*
 * Dio_Cfg.h
 *
 *  Created on: Sep 13, 2022
 *      Author: 10
 */

#ifndef MCAL_DIO_DIO_CFG_H_
#define MCAL_DIO_DIO_CFG_H_

#include "Dio_Types.h"


#define PIN_COUNT 19

typedef struct{
	Dio_Port_Type PinPort;
	Dio_Pin_Type Pin;
	Dio_Dir_Type dir;
	Dio_PULLUP_Type PullUp;
}Dio_Pin_Config;

extern Dio_Pin_Config Dio_Cfg_Pins[PIN_COUNT];

#endif /* MCAL_DIO_DIO_CFG_H_ */
