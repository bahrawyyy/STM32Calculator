/*
 * Dio.h
 *
 *  Created on: Sep 8, 2022
 *      Author: 10
 */

#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_

#include <avr/io.h>
#include "../../STD_Types.h"
#include "../../Bit_Math.h"

#include "Dio_Types.h"
#include "Dio_Cfg.h"

void Dio_init(void);
void Dio_write(channel_type channel , Dio_Status_Type state);
Dio_Status_Type Dio_read(channel_type channel);
void Dio_writePort(Dio_Port_Type port , unsigned char level);


#endif /* MCAL_DIO_DIO_H_ */
